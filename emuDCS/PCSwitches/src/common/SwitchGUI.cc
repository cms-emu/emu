#include "SwitchGUI.h"
#include "XMLParser.h" 

// provides factory method for instantion of HellWorld application
//
XDAQ_INSTANTIATOR_IMPL(SwitchGUI)
//
using namespace cgicc;
using namespace std;

emu::pcsw::Switch *S;

SwitchGUI::SwitchGUI(xdaq::ApplicationStub * s)throw (xdaq::exception::Exception): xdaq::Application(s) {
  xgi::bind(this,&SwitchGUI::Default, "Default");
  xgi::bind(this,&SwitchGUI::MainPage, "MainPage");
  xgi::bind(this,&SwitchGUI::GotoMain, "GotoMain");
  xgi::bind(this,&SwitchGUI::GotoMacGUI,"GotoMacGUI");
  xgi::bind(this,&SwitchGUI::Maintenance, "Maintenance");
  xgi::bind(this,&SwitchGUI::BackupSwitch, "BackupSwitch");
  xgi::bind(this,&SwitchGUI::ResetSwitch, "ResetSwitch");
  xgi::bind(this,&SwitchGUI::PowerSwitch, "PowerSwitch");
  xgi::bind(this,&SwitchGUI::ResetCounters, "ResetCounters");
  xgi::bind(this,&SwitchGUI::MacGUI, "MacGUI");
  xgi::bind(this,&SwitchGUI::CLRcounters,"CLRcounters");
  xgi::bind(this,&SwitchGUI::ProblemsGUI,"ProblemsGUI");

  xoap::bind(this,&SwitchGUI::FixCrates,"FixCrates", XDAQ_NS_URI);

  this->getApplicationInfoSpace()->fireItemAvailable("xmlFileName", &xmlFileName_);
  this->getApplicationInfoSpace()->fireItemAvailable("backupDirectory", &backupDir_);
  this->getApplicationInfoSpace()->fireItemAvailable("switchTelnet", &switchTelnet_);
  this->getApplicationInfoSpace()->fireItemAvailable("upsTelnet", &upsTelnet_);
  this->getApplicationInfoSpace()->fireItemAvailable("shutdownPort", &shutdownPort_);

}

void SwitchGUI::Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  *out << "<meta HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=/" <<getApplicationDescriptor()->getURN()<<"/"<<"MainPage"<<"\">" <<endl;
}

void SwitchGUI::MainPage(xgi::Input * in, xgi::Output * out ) {
  emu::pcsw::XMLParser switchparser;
  switchparser.parseFile(xmlFileName_);
  S = switchparser.GetSwitch();

  // fill statistic
  S->initialize();
  S->fill_pc_statistics();
  S->fill_switch_statistics(switchTelnet_);
  S->fill_switch_macs(switchTelnet_);
  S->fill_ping(switchTelnet_);

  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  std::string myUrn = getApplicationDescriptor()->getURN().c_str();
  xgi::Utils::getPageHeader(out,"SwitchGUI",myUrn,"","");

  /*
  *out << "xmlFileName_ = " <<  (std::string) xmlFileName_ << "<br>" << std::endl;
  *out << "switchTelnet_ = " <<  (std::string) switchTelnet_ << "<br>" << std::endl;
  *out << "shutdownPort_ = " << (std::string) shutdownPort_ << "<br>" << std::endl;
  *out << "backupDir_ = " << (std::string) backupDir_ << "<br>" << std::endl;
  */

  *out  << S->html_ping() << std::endl;

  *out << cgicc::table();
  *out << cgicc::tr();
  *out << cgicc::td();
  std::string GotoMain = toolbox::toString("/%s/GotoMain",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",GotoMain) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value","Refresh Page") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::td();
  std::string CLRcounters = toolbox::toString("/%s/CLRcounters",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",CLRcounters) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value","CLR Counters") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::td();
  std::string Maintenance = toolbox::toString("/%s/Maintenance",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",Maintenance) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value","Maintenance") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::td();
  std::string MacGUI = toolbox::toString("/%s/MacGUI",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",MacGUI) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value","Check Mac Table") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::td();
  std::string ProblemsGUI = toolbox::toString("/%s/ProblemsGUI",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",ProblemsGUI) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value","Ethernet Faults") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::tr() << std::endl;
  *out << cgicc::table() << std::endl;
  *out << cgicc::hr() << std::endl;

  char buf[40];

  *out << cgicc::fieldset().set("style","font-size: 11pt; font-family: arial;");
  sprintf(buf,"PC Gigabit Card Statistics");
  *out << cgicc::legend(buf).set("style","color:blue").set("align","left") << cgicc::p() << std::endl ;
  *out << S->html_pc_status();
  *out << cgicc::fieldset() << endl;  //*out << cgicc::table() << endl;

  *out << cgicc::fieldset().set("style","font-size: 11pt; font-family: arial;");
  sprintf(buf,"Switch Port Statistics");
  *out << cgicc::legend(buf).set("style","color:blue").set("align","left") << cgicc::p() << std::endl ;
  html_port_status(in,out);
  *out << cgicc::fieldset() << endl;

  S->copy_stats_new2old();
}

void SwitchGUI::GotoMain(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  cgicc::Cgicc cgi(in);
  this->Default(in,out);
}

void SwitchGUI::BackupSwitch(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  cgicc::Cgicc cgi(in);
  S->BackupSwitch(switchTelnet_,backupDir_);
  this->Default(in,out);
}

void SwitchGUI::ResetSwitch(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  cgicc::Cgicc cgi(in);
  S->ResetSwitch(switchTelnet_);
  this->Default(in,out);
}

void SwitchGUI::PowerSwitch(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  cgicc::Cgicc cgi(in);
  std::string switchOperation_, switchNum_;
  switchOperation_ = cgi["switchOperation"]->getValue();
  switchNum_ = cgi["switchNum"]->getValue();
  S->PowerSwitch(upsTelnet_, switchNum_, switchOperation_);
  this->Default(in,out);
}



void SwitchGUI::ResetCounters(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  cgicc::Cgicc cgi(in);
  switch_ = cgi["switch"]->getIntegerValue();
  prt_ = cgi["prt"]->getIntegerValue();
  slt_ = cgi["slt"]->getIntegerValue();
  S->ResetCounters(switch_,prt_, switchTelnet_);
  this->Default(in,out);
}

void SwitchGUI::CLRcounters(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  cgicc::Cgicc cgi(in);
  S->CLRcounters(switchTelnet_);
  this->Default(in,out);
}

void SwitchGUI::Maintenance(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  cgicc::Cgicc cgi(in);

  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  std::string myUrn = getApplicationDescriptor()->getURN().c_str();
  xgi::Utils::getPageHeader(out,"SwitchGUI: VME Gigabit Switch Maintenance",myUrn,"","");

  std::stringstream sTitle;
  sTitle << "SwitchGUI: " << S->sidelabel << " Side Maintenance";
  *out << Header(sTitle.str(),false);

  *out << cgicc::table();
  *out << cgicc::tr();
  *out << cgicc::td();
  std::string GotoMain = toolbox::toString("/%s/GotoMain",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",GotoMain) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value","Go to Main") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td();
  *out << cgicc::td();
  std::string BackupSwitch = toolbox::toString("/%s/BackupSwitch",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",BackupSwitch) << std::endl ;
  if(S->sidelabel=="PLUS") *out << cgicc::input().set("type","submit").set("value","Backup Plus Switches") << std::endl ;
  if(S->sidelabel=="MINUS") *out << cgicc::input().set("type","submit").set("value","Backup Minus Switches") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  char *buf=0;
  if(S->sidelabel=="PLUS")buf="Reload Plus Switches";
  if(S->sidelabel=="MINUS")buf="Reload Minus Switches";
  *out << cgicc::td();
  std::string ResetSwitch = toolbox::toString("/%s/ResetSwitch",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",ResetSwitch) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value",buf) << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::tr() << std::endl;
  *out << cgicc::table() << std::endl;
  if(toolbox::net::getHostName() == "vmepcS2G18-09.cms") {
  *out << cgicc::table() << std::endl;
  std::string PowerSwitch = toolbox::toString("/%s/PowerSwitch",getApplicationDescriptor()->getURN().c_str());
  
  for(int i=0;i<3;i++) {
    *out << cgicc::tr() << std::endl;
    for(int j=0;j<8;j++) {
      char switchNumChar[2];
      switch(i) {
        case 0:
          *out << cgicc::td() << "Switch " << j+1 << cgicc::td() << std::endl;
          break;
        case 1:
          sprintf(switchNumChar, "%d", j);
          *out << cgicc::td() << cgicc::form().set("method","GET").set("action",PowerSwitch) << cgicc::input().set("type", "hidden").set("name", "switchNum").set("value",switchNumChar) << cgicc::input().set("type", "hidden").set("name", "switchOperation").set("value","on") << cgicc::input().set("type","submit").set("value","Power On/Off") << cgicc::form() << cgicc::td() << std::endl;
          break;
        default:
          sprintf(switchNumChar, "%d", j);
          *out << cgicc::td() << cgicc::form().set("method","GET").set("action",PowerSwitch) << cgicc::input().set("type", "hidden").set("name", "switchNum").set("value",switchNumChar) << cgicc::input().set("type", "hidden").set("name", "switchOperation").set("value","reboot") << cgicc::input().set("type","submit").set("value","Power Cycle") << cgicc::form() << cgicc::td() << std::endl;
          break;
      }
    }
    *out << cgicc::tr() << std::endl;
  }
}

  *out << cgicc::tr() << std::endl;
  *out << cgicc::table() << std::endl;
  *out << cgicc::hr() << std::endl;
  *out<<Footer()<<endl;
}

void SwitchGUI::MacGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  cgicc::Cgicc cgi(in);

  S->fill_switch_macs(switchTelnet_);

  std::stringstream sTitle;
  sTitle << "SwitchGUI: " << S->sidelabel << " Side MAC Addresses";
  *out << Header(sTitle.str(),false);

//  *out<<Header("VME Gigabit Switch MAC Tables",false);
  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  std::string myUrn = getApplicationDescriptor()->getURN().c_str();
  xgi::Utils::getPageHeader(out,"SwitchGUI: VME Gigabit Switch MAC Tables",myUrn,"","");

  *out << cgicc::table();
  *out << cgicc::tr();
  *out << cgicc::td();
  std::string GotoMain = toolbox::toString("/%s/GotoMain",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",GotoMain) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value","Go to Main") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::td();
  std::string Maintenance = toolbox::toString("/%s/Maintenance",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",Maintenance) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value","Maintenance") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::td();
  std::string GotoMacGUI = toolbox::toString("/%s/GotoMacGUI",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",GotoMacGUI) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value","Refresh Page") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::tr() << std::endl;
  *out << cgicc::table() << std::endl;
  *out << cgicc::hr() << std::endl;
  char buf[40];
  sprintf(buf,"Switch Mac Addresses");
  *out << cgicc::fieldset().set("style","font-size: 11pt; font-family: arial;");
  *out << cgicc::legend(buf).set("style","color:blue").set("align","left") << cgicc::p() << std::endl ;
  *out << S->html_mac_table();
  *out << cgicc::fieldset() << endl;
  *out<<Footer()<<endl;
}

void SwitchGUI::GotoMacGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  cgicc::Cgicc cgi(in);
  this->MacGUI(in,out);
}

void SwitchGUI::ProblemsGUI(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception) {
  cgicc::Cgicc cgi(in);
//  *out<<Header("VME Problem Tables",false);
  std::stringstream sTitle;
  sTitle << "SwitchGUI: " << S->sidelabel << " Side VME Problem Tables";
  *out << Header(sTitle.str(),false);

  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << std::endl;
  *out << cgicc::html().set("lang", "en").set("dir","ltr") << std::endl;
  std::string myUrn = getApplicationDescriptor()->getURN().c_str();
  xgi::Utils::getPageHeader(out,"SwitchGUI: VME Problem Tables",myUrn,"","");

  *out << cgicc::table();
  *out << cgicc::tr();
  *out << cgicc::td();
  std::string GotoMain = toolbox::toString("/%s/GotoMain",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",GotoMain) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value","Go to Main") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::td();
  std::string Maintenance = toolbox::toString("/%s/Maintenance",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",Maintenance) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value","Maintenance") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::td();
  std::string GotoMacGUI = toolbox::toString("/%s/GotoMacGUI",getApplicationDescriptor()->getURN().c_str());
  *out << cgicc::form().set("method","GET").set("action",GotoMacGUI) << std::endl ;
  *out << cgicc::input().set("type","submit").set("value","Check MAC Tables") << std::endl ;
  *out << cgicc::form() << std::endl;
  *out << cgicc::td() << std::endl;
  *out << cgicc::tr() << std::endl;
  *out << cgicc::table() << std::endl;
  *out << cgicc::hr() << std::endl;
  S->fill_problems(switchTelnet_);
  for(int swt=0;swt<4;swt++){
    char buf[40];
    sprintf(buf,"Switch %d Problems",swt+1);
    std::cout << buf << std::endl;
    *out << cgicc::fieldset().set("style","font-size: 11pt; font-family: arial;");
    *out << cgicc::legend(buf).set("style","color:blue").set("align","left") << cgicc::p() << std::endl ;
    *out << S->html_parse_problems(swt+1);
    *out << cgicc::fieldset() << endl;
  }
  *out<<Footer()<<endl;
}

void SwitchGUI::html_port_status(xgi::Input * in, xgi::Output * out ) {
  cgicc::Cgicc cgi(in);
  int crate,swt,prt,slt;
  std::stringstream sTitle;
  sTitle << "SwitchGUI: " << S->sidelabel << " Side Port Statuses";
  *out << Header(sTitle.str(),false);

  *out << "<table cellpadding=6 rules=groups frame=box>";
  *out << "<thead>" << std::endl << "<tr><th>crate</th><th>switch</th><th>port</th><th>link</th><th>rx</th><th>rx_error</th><th>tx</th><th>tx_error</th></tr>" << std::endl << "</tr>" << std::endl <<  "<tbody>" << std::endl;

  for(crate=0;crate<43;crate++){
    swt=S->side[crate].nswitch;
    prt=S->side[crate].nport;
    slt=S->side[crate].vlan;
    if(S->sidelabel=="PLUS" && prt != 13)
      *out << "<tr><td>" << S->side[crate].name << "</td><td>" << swt << "</td><td>" <<  "0/" << prt << "</td><td>" << S->sw[swt-1][prt-1].link << "</td><td>" << S->sw[swt-1][prt-1].rx << "</td><td>" << S->sw[swt-1][prt-1].rx_error << "</td><td>" << S->sw[swt-1][prt-1].tx << "</td><td>" << S->sw[swt-1][prt-1].tx_error << "</td><td>" <<  cgicc::form().set("method","GET").set("action", toolbox::toString("/%s/ResetCounters",getApplicationDescriptor()->getURN().c_str())) << std::endl <<  cgicc::input().set("type","hidden").set("name","switch").set("value",toolbox::toString("%d", swt)) << std::endl <<  cgicc::input().set("type","hidden").set("name","slt").set("value",toolbox::toString("%d", slt)) << std::endl <<  cgicc::input().set("type","hidden").set("name","prt").set("value",toolbox::toString("%d", prt)) << std::endl << cgicc::input().set("type","submit").set("value","Reset Counters") << std::endl <<  cgicc::form() << std::endl  << "</td></tr>" << std::endl;
    if(S->sidelabel=="MINUS" && prt != 13)
      *out << "<tr><td>" << S->side[crate].name << "</td><td>" << swt+6 << "</td><td>" <<  "0/" << prt << "</td><td>" << S->sw[swt-1][prt-1].link << "</td><td>" << S->sw[swt-1][prt-1].rx << "</td><td>" << S->sw[swt-1][prt-1].rx_error << "</td><td>" << S->sw[swt-1][prt-1].tx << "</td><td>" << S->sw[swt-1][prt-1].tx_error << "</td><td>" <<  cgicc::form().set("method","GET").set("action", toolbox::toString("/%s/ResetCounters",getApplicationDescriptor()->getURN().c_str())) << std::endl <<  cgicc::input().set("type","hidden").set("name","switch").set("value",toolbox::toString("%d", swt)) << std::endl <<  cgicc::input().set("type","hidden").set("name","slt").set("value",toolbox::toString("%d", slt)) << std::endl <<  cgicc::input().set("type","hidden").set("name","prt").set("value",toolbox::toString("%d", prt)) << std::endl << cgicc::input().set("type","submit").set("value","Reset Counters") << std::endl <<  cgicc::form() << std::endl  << "</td></tr>" << std::endl;
    if(prt != 13) 
      *out << "<tr><td></td><td></td><td></td><td></td><td>" << S->sw[swt-1][prt-1].rx-S->old[swt-1][prt-1].rx << "</td><td>" << S->sw[swt-1][prt-1].rx_error-S->old[swt-1][prt-1].rx_error << "</td><td>" << S->sw[swt-1][prt-1].tx-S->old[swt-1][prt-1].tx << "</td><td>" << S->sw[swt-1][prt-1].tx_error-S->old[swt-1][prt-1].tx_error << "</td></tr>" << std::endl;
  }
  *out << "</tbody>" << std::endl << "</table>" << std::endl;
  *out << cgicc::fieldset() << endl;
}

string SwitchGUI::Header(string myTitle,bool reload=true) {
  ostringstream *out = new ostringstream();

  *out << cgicc::HTMLDoctype(cgicc::HTMLDoctype::eStrict) << endl;
  *out << "<html>" << endl;
  *out << cgicc::head() << endl;
  *out << CSS();
  *out << cgicc::title(myTitle) << endl;


  *out << cgicc::head() << endl;

  *out << "<body background=\"/tmp/osulogo.jpg\">" << endl;

  *out << cgicc::fieldset().set("class","header") << endl;

  *out << cgicc::img().set("src","/tmp/mainemus.jpg").set("style","float: right; height: 100px") << endl;

  *out << cgicc::div(myTitle).set("class","title") << endl;

  *out << cgicc::div().set("class","expert") << endl;
  *out << cgicc::span("Experts ").set("style","font-weight: bold") << endl;
  *out << cgicc::a("Stan Durkin").set("href","mailto:durkin@mps.ohio-state.edu") << ", " << endl;
  *out << cgicc::a("Ben Bylsma").set("href","mailto:bylsma@mps.ohio-state.edu") << ", " << endl;
  *out << cgicc::a("Jianhui Gu").set("href","mailto:gujh@mps.ohio-state.edu") << ", " << endl;
  *out << cgicc::a("Grayson Williams").set("href","mailto:Grayson.Laurent.Williams@cern.ch") << endl;
  *out << cgicc::div() << endl;

  *out << cgicc::fieldset() << endl;

  *out << cgicc::br().set("style","clear: both;") << endl;

  return out->str();
}

xoap::MessageReference SwitchGUI::FixCrates(xoap::MessageReference msg) throw (xoap::exception::Exception) { 
//      SOAPMessage reply = xdaq::frameSend ( request_ );         
  xoap::MessageReference reply = msg;         
  xoap::SOAPBody body = reply->getSOAPPart().getEnvelope().getBody();         
  try {
    xoap::SOAPName counterTag ("CrateVector", "", "");
    vector<xoap::SOAPElement> content = body.getChildElements();                 
    for (unsigned int i = 0; i < content.size(); i++) {                         
      vector<xoap::SOAPElement> c = content[i].getChildElements(counterTag);
      for (unsigned int j = 0; j < c.size(); j++) {
        if (c[0].getElementName() == counterTag) {
          for(int crate=0;crate<32;crate++){
            if (S->side[crate].label == c[0].getValue()) {
              std::string command,command2;
              std::stringstream commandstream;
              command = (std::string) shutdownPort_ + " " + S->side[crate].ipaddr + " ";
              commandstream << S->side[crate].nport;
              commandstream >> command2;
              command += command2;
              cout << command << endl;
              int ierr;
              ierr=system(command.c_str());
            }
//                                      cout << "The server replied with counter: ";
//                                      cout << c[0].getValue() << endl;
          }
        }
      }

    }
  } catch (xoap::exception::Exception& e) {
    xoap::SOAPFault fault = body.getFault();
    string msg = "Server error: ";
    msg += fault.getFaultString();
    XCEPT_RETHROW(xoap::exception::Exception, msg, e);
  }

//      xoap::MessageReference reply = xoap::createMessage();
//      xoap::SOAPEnvelope envelope = reply->getSOAPPart().getEnvelope();
//      xoap::SOAPName responseName = envelope.createName("onMessageResponse", "xdaq",XDAQ_NS_URI);
//      xoap::SOAPBodyElement e = envelope.getBody().addBodyElement(responseName);
  return reply;
}



string SwitchGUI::CSS() {
  ostringstream *out = new ostringstream();

  *out << cgicc::style() << endl;
  *out << cgicc::comment() << endl;
  *out << "div.title {width: 60%; text-align: left; color: #000; font-size: 16pt; font-weight: bold;}" << endl;
  *out << "div.expert {width: 60%; text-align: left;}" << endl;
  *out << "fieldset.header {width: 95%; margin: 5px auto 5px auto; padding: 1px; border: 2px solid #555; background-color: #DDD;}" << endl;
  *out << "fieldset.footer {width: 95%; margin: 20px auto 5px auto; padding: 2px 2px 2px 2px; font-size: 9pt; font-style: italic; border: 0px solid #555; text-align: center;}" << endl;
  *out << "fieldset.fieldset, fieldset.normal, fieldset.expert {width: 90%; margin: 10px auto 10px auto; padding: 2px 2px 2px 2px; border: 2px solid #555; background-color: #FFF;}" << endl;
  *out << "fieldset.expert {background-color: #CCC; border: dashed 2px #C00; clear: both;}" << endl;
  *out << "div.legend {width: 100%; padding-left: 20px; margin-bottom: 10px; color: #00D; font-size: 12pt; font-weight: bold;}" << endl;
  *out << ".openclose {border: 1px solid #000; padding: 0px; cursor: pointer; font-family: monospace; color: #000; background-color: #FFF;}" << endl;
  *out << "table.data {border-width: 0px; border-collapse: collapse; margin: 5px auto 5px auto; font-size: 9pt;} " << endl;
  *out << "table.data td {padding: 1px 8px 1px 8px;}" << endl;
  *out << ".Halted, .Enabled, .Disabled, .Configured, .Failed, .unknown {padding: 2px; background-color: #000; font-family: monospace;}" << endl;
  *out << ".Halted {color: #F99;}" << endl;
  *out << ".Enabled {color: #9F9;}" << endl;
  *out << ".Disabled {color: #FF9;}" << endl;
  *out << ".Configured {color: #99F;}" << endl;
  *out << ".Failed, .unknown {color: #F99; font-weight: bold; text-decoration: blink;}" << endl;
  *out << ".error {padding: 2px; background-color: #000; color: #F00; font-family: monospace;}" << endl;
  *out << ".warning {padding: 2px; background-color: #F60; color: #000; font-family: monospace;}" << endl;
  *out << ".orange {padding: 2px; color: #930; font-family: monospace;}" << endl;
  *out << ".caution {padding: 2px; background-color: #FF6; color: #000; font-family: monospace;}" << endl;
  *out << ".yellow {padding: 2px; color: #990; font-family: monospace;}" << endl;
  *out << ".ok {padding: 2px; background-color: #6F6; color: #000; font-family: monospace;}" << endl;
  *out << ".green {padding: 2px; color: #090; font-family: monospace;}" << endl;
  *out << ".bad {padding: 2px; background-color: #F66; color: #000; font-family: monospace;}" << endl;
  *out << ".red {padding: 2px; color: #900; font-family: monospace;}" << endl;
  *out << ".questionable {padding: 2px; background-color: #66F; color: #000; font-family: monospace;}" << endl;
  *out << ".blue {padding: 2px; color: #009; font-family: monospace;}" << endl;
  *out << ".none {padding: 2px; font-family: monospace;}" << endl;
  *out << ".undefined {padding: 2px; background-color: #CCC; color: #333; font-family: monospace;}" << endl;

  *out << ".button {padding: 2px; -moz-border-radius: 3px; -webkit-border-radius: 3px; border: 1px solid #000; cursor: pointer;}" << endl;
  //*out << "body {background-image: url('/tmp/osu_fed_background2.png'); background-repeat: repeat;}" << endl;
  *out << cgicc::comment() << endl;
  *out << cgicc::style() << endl;

  return out->str();
}

string SwitchGUI::Footer() {
  ostringstream *out = new ostringstream();

  *out << cgicc::fieldset().set("class","footer") << endl;
  *out << cgicc::div().set("class","switch") << endl;
  *out << cgicc::span("Switches(Experts Only!)").set("style","font-weight: bold") << endl;
  std::string Switch_name, Switch_URL;
  for(int i=0;i<4;i++) {
    Switch_name = "Switch " + S->ip_addresses[i].label;
      Switch_URL = "http://" + S->ip_addresses[i].ipaddr;
      *out << cgicc::a(Switch_name).set("href",Switch_URL);
      if(i!=3) *out << ", ";
      *out << endl;
    }
  *out << cgicc::div() << endl;
  *out << cgicc::hr() << endl;
  *out << "Built on " << __DATE__ << " at " << __TIME__ << "." << cgicc::br() << endl;
  *out << cgicc::fieldset() << endl;

  *out << "</body>" << endl;
  *out << "</html>" << endl;

  return out->str();
}
