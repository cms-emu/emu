#include "RegEx.cc"
#include "emu/dqm/tfanalyzer/EmuTFbookkeeper.h"
#include "emu/dqm/tfanalyzer/EmuTFxmlParsing.h"
#include "emu/dqm/tfanalyzer/EmuTFfiller.h"
#include "emu/dqm/tfanalyzer/EmuTFvalidator.h"

#include <TH1.h>
#include <TCanvas.h>
#include <TH1C.h>
#include <TROOT.h>
#include <TFile.h>
#include <TApplication.h>

#include "IORawData/CSCCommissioning/src/FileReaderDDU.cc"

#include "EventFilter/CSCTFRawToDigi/src/CSCTFEvent.h"
#include "EventFilter/CSCTFRawToDigi/src/CSCSPTrailer.h"

#include <math.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <fstream>

//#define BASE "/nfshome0/cscdqm/TriDAS/emu/emuDQM/"

//To compile on lxplus:   g++ -o test EmuTFtest.cpp -I/afs/cern.ch/cms/Releases/XDAQ/XDAQ_3_4/daq/extern/xerces/linuxx86/include/ -L/afs/cern.ch/cms/Releases/XDAQ/XDAQ_3_4/daq/extern/xerces/linuxx86/lib/ -lxerces-c `root-config --cflags` `root-config --glibs` -Wall -I/afs/cern.ch/user/k/kkotov/CMSSW_0_8_0_pre2/src/ -I../../src/common/ -I../../include/
//To compile on cmsdaq03: g++ -o test EmuTFtest.cpp -I$XDAQ_ROOT/daq/extern/xerces/linuxx86/include/ -L$XDAQ_ROOT/daq/extern/xerces/linuxx86/lib/ -lxerces-c `root-config --cflags` `root-config --glibs` -Wall -I/home/daq/kotov/CMSSW_0_5_1/src/ -I../../src/common/ -I../../include/
//To compile on slice11:  g++ -o test EmuTFtest.cpp -I/home/slice/DAQKit/v3.6/TriDAS/daq/extern/xerces/linuxx86/include/ -I../../src/common/ -I../../include/ -L/home/slice/DAQKit/v3.6/TriDAS/daq/extern/xerces/linuxx86/lib/ -lxerces-c `root-config --cflags` `root-config --glibs` -Wall -I/home/slice/kotov/CMSSW_0_8_0_pre2/src/
//To compile on emudqm: g++ -o test EmuTFtest.cpp -I/home/cscdqm/DAQKit/v4.2.1/TriDAS/daq/extern/xerces/linuxx86/include/ -I../../src/common/ -I../../include/ -L/home/cscdqm/DAQKit/v4.2.1/TriDAS/daq/extern/xerces/linuxx86/lib/ -lxerces-c `root-config --cflags` `root-config --glibs` -Wall -I/home/cscdqm/CMSSW_1_3_0_pre4/src
//To compile on csc-C2D07-10: g++ -o test EmuTFtest.cpp -DBASE="\"/nfshome0/cscdqm/TriDAS/emu/emuDQM/\"" -I/nfshome0/cscdqm/DAQKit/TriDAS/daq/extern/xerces/linuxx86/include/ -I../../src/common/ -I../../include/ -L/nfshome0/cscdqm/DAQKit/TriDAS/daq/extern/xerces/linuxx86/lib/ -lxerces-c `root-config --cflags` `root-config --glibs` -Wall -I/nfshome0/cscdqm/CMSSW/src
//With central installation of XDAQ: g++ -o test EmuTFtest.cpp -DBASE="\"/nfshome0/cscdqm/TriDAS/emu/emuDQM/\"" -I/opt/xdaq/include/ -I../../src/common/ -I../../include/ -L/opt/xdaq/lib/ -lxerces-c `root-config --cflags` `root-config --glibs` -Wall -I/nfshome0/cscdqm/CMSSW/src

int main(int argc, char *argv[]){
	using namespace std;
	using namespace EmuTFxmlParsing;
	// Root specific
	extern void InitGui();
	VoidFuncPtr_t initfuncs[] = { InitGui, 0 };
	TROOT root("ROOTSYSTEM","ROOT_", initfuncs);
	int a=2;
	char *v[]={"qwe","-b"};

	TApplication app("qwe", &a, v);
	// Histograms/Canvases description
	std::map<std::string,HistAttributes>   histList   = parseHistXML  (BASE "xml/CSCTF_histograms.xml");
	std::map<std::string,CanvasAttributes> canvasList = parseCanvasXML(BASE "xml/CSCTF_canvases.xml");
	//std::map<std::string,HistAttributes>   histList   = parseHistXML  (BASE "EmuTFMonitor/xml/CSCTF_histograms_quick.xml");
	//std::map<std::string,CanvasAttributes> canvasList = parseCanvasXML(BASE "EmuTFMonitor/xml/CSCTF_canvases_quick.xml");
	std::map<std::string,CheckAttributes>  checkList  = parseCheckXML (BASE "xml/CSCTF_checks.xml");

	EmuTFfiller* filler = new EmuTFfiller(histList,canvasList);
 
        if (filler) delete filler;
        
        filler = new EmuTFfiller(histList,canvasList);

	// DDU File Reader
	FileReaderDDU reader;

	// Keep last event
	size_t last_size=0;
	const unsigned short *last_buf=0;
	// Keep track of dates
	map<string,string> history;

        int prescaling = 1;//argc - 1; // Stupid way to speed-up this process
	int nEventsTotal = 0;

	for(int arg=1; arg<argc; arg++){
		struct stat info;
		if( stat(argv[arg],&info)==0 ){
			history[argv[arg]] = ctime(&info.st_ctime);
			size_t pos = history[argv[arg]].rfind('\n');
			if( pos!=string::npos ) history[argv[arg]].erase(pos);
		}
		else continue;

		reader.open(argv[arg]);
		//reader.reject(FileReaderDDU::DDUoversize|FileReaderDDU::FFFF);
		//reader.select(FileReaderDDU::Type1);
		reader.select(0);

		// Event buffer
		size_t size=0, nevents=0;
		const unsigned short *buf=0;

		// Main cycle
		while( (size = reader.next(buf)) /*&& nevents<117500*/ ){
			filler->fill(buf,size,reader.status());
//std::map<std::string,TCanvas*> rootCanvases = filler->bookkeeper().wrapToCanvases(canvasList);
//cout<<"Cleaning up"<<endl;
//filler->bookkeeper().cleanupCanvases();
//cout<<" done"<<endl;
			if( filler->last_event_status() == EmuTFfiller::CLEAR ){
				last_size = size;
				last_buf  = buf;
			}
			nevents++;
		}
		nEventsTotal += nevents;
	}

	// Miscellaneous information
	std::ostringstream misc;
	for(map<string,string>::const_iterator file=history.begin(); file!=history.end(); file++)
		misc<<file->first<<"  ["<<file->second<<"]"<<endl;

	if( last_size && last_buf ){
		CSCTFEvent tfEvent;
		tfEvent.unpack(last_buf,last_size);
		vector<CSCSPEvent> SPs = tfEvent.SPs();
		for(vector<CSCSPEvent>::const_iterator spPtr=SPs.begin(); spPtr!=SPs.end(); spPtr++){
			unsigned short sp = spPtr->header().sector() + ( spPtr->header().endcap() ? 0 : 6 );
			misc<<"SP"<<sp<<"  boar_id=0x"<<hex<<spPtr->trailer().board_id()<<dec<<" SP readout configuration: "<<spPtr->trailer().year()<<"/"<<spPtr->trailer().month()<<"/"<<spPtr->trailer().day()<<endl;
		}
	}
	misc<<"Number of processed events = "<<nEventsTotal<<", prescaling = "<<prescaling<<endl;

	// Summary information
	std::ostringstream str;
	EmuTFvalidator validator(filler->bookkeeper());
	str<<"nErrors: "<<validator.check(checkList)<<endl;
	list<string> failed = validator.falied();
	for(list<string>::const_iterator hist=failed.begin(); hist!=failed.end(); hist++)
		str<<" Failed: "<<*hist<<endl;
	list<string> passed = validator.passed();
	//for(list<string>::const_iterator hist=passed.begin(); hist!=passed.end(); hist++)
	//	str<<" Passed: "<<*hist<<endl;
	//str<<ends;

//	map<string,string> alias;
//	alias[""] = "";

	ofstream report("report.txt");
	report<<misc.str()<<ends;
	report<<str.str()<<ends;
	report.close();

// Timing information
std::ostringstream str2;
for(int spNum=1; spNum<=12; spNum++){
	string sp="SP";
	switch ( spNum ){
		case 1: sp+="1/"; break;
		case 2: sp+="2/"; break;
		case 3: sp+="3/"; break;
		case 4: sp+="4/"; break;
		case 5: sp+="5/"; break;
		case 6: sp+="6/"; break;
		case 7: sp+="7/"; break;
		case 8: sp+="8/"; break;
		case 9: sp+="9/"; break;
		case 10:sp+="10/";break;
		case 11:sp+="11/";break;
		case 12:sp+="12/";break;
	}
	str2<<sp<<endl;

	map<string,string> neighbour;
	neighbour[sp+"F2/CSC4"] = sp+"F3/CSC7";
	neighbour[sp+"F2/CSC5"] = sp+"F3/CSC8";
	neighbour[sp+"F2/CSC6"] = sp+"F3/CSC9";
	neighbour[sp+"F2/CSC7"] = sp+"F3/CSC7";
	neighbour[sp+"F2/CSC8"] = sp+"F3/CSC8";
	neighbour[sp+"F2/CSC9"] = sp+"F3/CSC9";

	neighbour[sp+"F1/CSC4"] = sp+"F3/CSC4";
	neighbour[sp+"F1/CSC5"] = sp+"F3/CSC5";
	neighbour[sp+"F1/CSC6"] = sp+"F3/CSC6";
	neighbour[sp+"F1/CSC7"] = sp+"F3/CSC4";
	neighbour[sp+"F1/CSC8"] = sp+"F3/CSC5";
	neighbour[sp+"F1/CSC9"] = sp+"F3/CSC6";

	neighbour[sp+"F4/CSC4"] = sp+"F3/CSC4";
	neighbour[sp+"F4/CSC5"] = sp+"F3/CSC5";
	neighbour[sp+"F4/CSC6"] = sp+"F3/CSC6";
	neighbour[sp+"F4/CSC7"] = sp+"F3/CSC7";
	neighbour[sp+"F4/CSC8"] = sp+"F3/CSC8";
	neighbour[sp+"F4/CSC9"] = sp+"F3/CSC9";

	neighbour[sp+"F4/CSC1"] = sp+"F3/CSC1";
	neighbour[sp+"F4/CSC2"] = sp+"F3/CSC2";
	neighbour[sp+"F4/CSC3"] = sp+"F3/CSC3";

	neighbour[sp+"F5/CSC1"] = sp+"F4/CSC1";
	neighbour[sp+"F5/CSC2"] = sp+"F4/CSC2";
	neighbour[sp+"F5/CSC3"] = sp+"F4/CSC3";

	neighbour[sp+"F1/CSC4"] = sp+"F3/CSC4";
	neighbour[sp+"F1/CSC5"] = sp+"F3/CSC5";
	neighbour[sp+"F1/CSC6"] = sp+"F3/CSC6";

	neighbour[sp+"F2/CSC4"] = sp+"F3/CSC7";
	neighbour[sp+"F2/CSC5"] = sp+"F3/CSC8";
	neighbour[sp+"F2/CSC6"] = sp+"F3/CSC9";

	neighbour[sp+"F1/CSC7"] = sp+"F3/CSC4";
	neighbour[sp+"F1/CSC8"] = sp+"F3/CSC5";
	neighbour[sp+"F1/CSC9"] = sp+"F3/CSC6";

	neighbour[sp+"F2/CSC7"] = sp+"F3/CSC7";
	neighbour[sp+"F2/CSC8"] = sp+"F3/CSC8";
	neighbour[sp+"F2/CSC9"] = sp+"F3/CSC9";

	neighbour[sp+"F1/CSC1"] = sp+"F3/CSC1";
	neighbour[sp+"F1/CSC2"] = sp+"F3/CSC2";
	neighbour[sp+"F1/CSC3"] = sp+"F3/CSC2";

	neighbour[sp+"F2/CSC1"] = sp+"F3/CSC2";
	neighbour[sp+"F2/CSC2"] = sp+"F3/CSC2";
	neighbour[sp+"F2/CSC3"] = sp+"F3/CSC3";

	str2<<endl<<"Timing for neighbour chambers (SP"<<spNum<<"): "<<endl<<endl;
	for(int mpc=1; mpc<=5; mpc++){
		for(int csc=1; csc<10; csc++){
			if(mpc==5 && csc>3) continue;
			ostringstream label;
			label<<(sp+"F")<<mpc<<"/CSC"<<csc;
			TH2F *timing = (TH2F*)filler->bookkeeper().get("csc_timing",spNum,mpc,csc);
			if( !timing ){ std::cout<<label.str()<<"/"<<"csc_timing not booked"<<std::endl; continue; }
			for(int yBin=1; yBin<timing->GetNbinsY(); yBin++){
				if( neighbour[label.str()] != (sp+timing->GetYaxis()->GetBinLabel(yBin)) ) continue;
				double m0=0, m1=0, m2=0;
				for(int xBin=1; xBin<timing->GetNbinsX(); xBin++){
					m0 += timing->GetBinContent(xBin,yBin);
					m1 += timing->GetBinContent(xBin,yBin)*(xBin-8);
					m2 += timing->GetBinContent(xBin,yBin)*(xBin-8)*(xBin-8);
				}
				str2<<label.str()<<" - "<<neighbour[label.str()]<<(m1>0?" = +":" = ")<<m1/m0<<" RMS = "<<sqrt(m2/m0-m1*m1/m0/m0)<<" nHits = "<<m0<<endl;
			}
		}
	}

	map<string,string> overlap;
	overlap[sp+"F4/CSC4"] = sp+"F4/CSC5";
	overlap[sp+"F4/CSC5"] = sp+"F4/CSC6";
	overlap[sp+"F4/CSC6"] = sp+"F4/CSC7";
	overlap[sp+"F4/CSC7"] = sp+"F4/CSC8";
	overlap[sp+"F4/CSC8"] = sp+"F4/CSC9";

	overlap[sp+"F3/CSC4"] = sp+"F3/CSC5";
	overlap[sp+"F3/CSC5"] = sp+"F3/CSC6";
	overlap[sp+"F3/CSC6"] = sp+"F3/CSC7";
	overlap[sp+"F3/CSC7"] = sp+"F3/CSC8";
	overlap[sp+"F3/CSC8"] = sp+"F3/CSC9";

	overlap[sp+"F5/CSC1"] = sp+"F5/CSC2";
	overlap[sp+"F5/CSC2"] = sp+"F5/CSC3";

	overlap[sp+"F4/CSC1"] = sp+"F4/CSC2";
	overlap[sp+"F4/CSC2"] = sp+"F4/CSC3";

	overlap[sp+"F3/CSC1"] = sp+"F3/CSC2";
	overlap[sp+"F3/CSC2"] = sp+"F3/CSC3";

	overlap[sp+"F1/CSC1"] = sp+"F1/CSC2";
	overlap[sp+"F1/CSC2"] = sp+"F1/CSC3";
	overlap[sp+"F1/CSC3"] = sp+"F2/CSC1";
	overlap[sp+"F1/CSC4"] = sp+"F1/CSC5";
	overlap[sp+"F1/CSC5"] = sp+"F1/CSC6";
	overlap[sp+"F1/CSC6"] = sp+"F2/CSC4";
	overlap[sp+"F1/CSC7"] = sp+"F1/CSC8";
	overlap[sp+"F1/CSC8"] = sp+"F1/CSC9";

	overlap[sp+"F2/CSC1"] = sp+"F2/CSC2";
	overlap[sp+"F2/CSC2"] = sp+"F2/CSC3";
	overlap[sp+"F2/CSC4"] = sp+"F2/CSC5";
	overlap[sp+"F2/CSC5"] = sp+"F2/CSC6";
	overlap[sp+"F2/CSC7"] = sp+"F2/CSC8";
	overlap[sp+"F2/CSC8"] = sp+"F2/CSC9";

	str2<<endl<<"Timing for overlapping chambers (SP"<<spNum<<"): "<<endl<<endl;
	for(int mpc=1; mpc<=5; mpc++){
		for(int csc=1; csc<10; csc++){
			if(mpc==5 && csc>3) continue;
			ostringstream label;
			label<<(sp+"F")<<mpc<<"/CSC"<<csc;
			TH2F *timing = (TH2F*)filler->bookkeeper().get("csc_timing",spNum,mpc,csc);
			if( !timing ){ std::cout<<label.str()<<"/"<<"csc_timing not booked"<<std::endl; continue; }
			for(int yBin=1; yBin<=timing->GetNbinsY(); yBin++){
				if( overlap[label.str()] != (sp+timing->GetYaxis()->GetBinLabel(yBin)) ) continue;
				double m0=0, m1=0, m2=0;
				for(int xBin=1; xBin<timing->GetNbinsX(); xBin++){
					m0 += timing->GetBinContent(xBin,yBin);
					m1 += timing->GetBinContent(xBin,yBin)*(xBin-8);
					m2 += timing->GetBinContent(xBin,yBin)*(xBin-8)*(xBin-8);

				}
				str2<<label.str()<<" - "<<overlap[label.str()]<<(m1>0?" = +":" = ")<<m1/m0<<" RMS = "<<sqrt(m2/m0-m1*m1/m0/m0)<<" nHits = "<<m0<<endl;
			}

		}
	}
	str2<<endl;
}

	ofstream report2("timing.txt");
	report2<<str2.str()<<ends;
	report2.close();

        TFile file("qqq.root","RECREATE");
	std::set<std::string> canvases = filler->bookkeeper().getListOfAvailableCanvases();
	std::set<std::string>::const_iterator cnv = canvases.begin();
	while( cnv != canvases.end() ){
		TCanvas *canvas = filler->bookkeeper().getCanvas(*cnv);
                canvas->Write();
		cnv++;
        }

	// Write summary information
	string sum = str.str(), tim = str2.str(), mis = misc.str();
	TH1C summary("summary","Summary",sum.length(),0,1);
	TH1C timing ("timing", "timing", tim.length(),0,1);
	TH1C miscellaneous("miscellaneous","miscellaneous",mis.length(),0,1);
	for(unsigned int i=0;i<sum.length();i++) summary.SetBinContent(i+1,sum[i]);
	for(unsigned int i=0;i<tim.length();i++) timing. SetBinContent(i+1,tim[i]);
	for(unsigned int i=0;i<mis.length();i++) miscellaneous.SetBinContent(i+1,mis[i]);
	cout<<"Summary ["<<summary.GetNbinsX()<<"="<<sum.length()<<"]:"<<endl<<(summary.GetArray()+1)<<endl;
	summary.Write();
	timing.Write();
	miscellaneous.Write();
	file.Close();
        if (filler!=NULL) delete filler;
	app.Terminate();
	return 0;
}
