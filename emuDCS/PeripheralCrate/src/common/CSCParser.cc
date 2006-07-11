//-----------------------------------------------------------------------
// $Id: CSCParser.cc,v 1.4 2006/07/11 15:00:39 mey Exp $
// $Log: CSCParser.cc,v $
// Revision 1.4  2006/07/11 15:00:39  mey
// Update
//
// Revision 1.3  2006/05/31 12:37:26  mey
// Update
//
// Revision 1.2  2006/05/16 15:54:38  mey
// UPdate
//
// Revision 1.1  2006/03/27 09:30:59  mey
// Update
//
// Revision 2.0  2005/04/12 08:07:05  geurts
// *** empty log message ***
//
//
//-----------------------------------------------------------------------
#include "CSCParser.h"
#include "Singleton.h"
#include "CrateSetup.h"
//
CSCParser::CSCParser(xercesc::DOMNode * pNode, int crateNumber)
{
  parser_.parseNode(pNode);
  parser_.fillString("chamber_type", chamberType);
  parser_.fillString("label", label);
  csc_ = new Chamber();
  theCrate = Singleton<CrateSetup>::instance()->crate(crateNumber);
  theCrate->AddChamber(csc_);
  //
  std::cout << "Creating CSC Type=" << chamberType << std::endl;
  std::cout << "Done" << std::endl;
  //
  xercesc::DOMNode * pNode1 = pNode->getFirstChild();
  //
  while (pNode1) {
    if (pNode1->getNodeType() == xercesc::DOMNode::ELEMENT_NODE) {
      std::cout << "PeripheralCrateParser: pNode1=" << xercesc::XMLString::transcode(pNode1->getNodeName()) << std::endl;
      //
      if (strcmp("DAQMB",xercesc::XMLString::transcode(pNode1->getNodeName()))==0) {  
	daqmbParser_ = DAQMBParser(pNode1, crateNumber);
	daqmbParser_.SetCSC(csc_);
	csc_->SetDMB(daqmbParser_.daqmb());
      }
      //
      if (strcmp("TMB",xercesc::XMLString::transcode(pNode1->getNodeName()))==0) {  
	tmbParser_ = TMBParser(pNode1, crateNumber);
	tmbParser_.SetCSC(csc_);
	csc_->SetTMB(tmbParser_.tmb());
      }       
    }
    pNode1 = pNode1->getNextSibling();
  }
  //
}
//

























