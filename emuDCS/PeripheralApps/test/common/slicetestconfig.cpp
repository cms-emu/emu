//-----------------------------------------------------------------------
// $Id: slicetestconfig.cpp,v 1.3 2008/08/13 11:30:52 geurts Exp $
// $Log: slicetestconfig.cpp,v $
// Revision 1.3  2008/08/13 11:30:52  geurts
// introduce emu::pc:: namespaces
// remove any occurences of "using namespace" and make std:: references explicit
//
// Revision 1.2  2008/01/10 11:57:29  liu
// update
//
// Revision 1.1  2007/12/26 11:25:04  liu
// new parser and applications
//
// Revision 3.0  2006/07/20 21:15:48  geurts
// *** empty log message ***
//
// Revision 2.1  2006/02/01 20:58:02  mey
// Got rid of TestBeamController
//
// Revision 2.0  2005/04/12 08:07:07  geurts
// *** empty log message ***
//
//
//-----------------------------------------------------------------------
#include <iostream>
#include "VMEController.h"
#include "Crate.h"
#include "DAQMB.h"
#include "CCB.h"
#include "EmuController.h"
#include "TMB.h"
#include "ALCTController.h"
#include "MPC.h"
#include <unistd.h>

int main(int argc, char **argv)
{
  char *xmlFile = "configSliceTest.xml";

  // process command line arguments
  if (argc>1)
    for (int i=1;i<argc;i++){
      if (!strcmp(argv[i],"-h")){                                                                     
        std::cout << "Usage: " << argv[0] <<"[-f (file="<< xmlFile <<")]" << std::endl;
        exit(0);
      }
      if (!strcmp(argv[i],"-f")) xmlFile=argv[++i];
    }

 
  std::cout << "PeripheralCrate configuration file: " << xmlFile << std::endl;
  //PeripheralCrateParser parser;
  //parser.parseFile(xmlFile);

  //TestBeamCrateController tbController;
  emu::pc::EmuController emuController;
  emuController.SetConfFile(xmlFile);
  emuController.init();
  //
  std::cout << "Created TestBeamController for SliceTest" << std::endl;  
  
  std::cout << "Configuring TestBeamController for SliceTest: " << std::endl; 
  emuController.configure();
  std::cout << "Finished TestBeamCrateController configure for SliceTest" << std::endl;

  // Examples of direct access to some modules 
  //DAQMB * daqmb = parser.daqmbParser().daqmb();
  //CCB * ccb = parser.ccbParser().ccb();
  //DAQMBTester tester(daqmb, ccb, false);
  //tester.runAllTests();

  return 0;
}


