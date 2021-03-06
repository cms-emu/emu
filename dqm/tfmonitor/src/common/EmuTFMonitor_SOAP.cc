/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.                                        *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#include "emu/dqm/tfmonitor/EmuTFMonitor.h"

xoap::MessageReference EmuTFMonitor::requestObjectsList(xoap::MessageReference node) throw (xoap::exception::Exception)
{
  appBSem_.take();
  LOG4CPLUS_DEBUG (getApplicationLogger(), "Received Monitoring Objects List request");
  xoap::SOAPBody rb = node->getSOAPPart().getEnvelope().getBody();
  if (rb.hasFault() )
    {
      xoap::SOAPFault fault = rb.getFault();
      std::string errmsg = "DQMNode: ";
      errmsg += fault.getFaultString();
      XCEPT_RAISE(xoap::exception::Exception, errmsg);
    }

  xoap::MessageReference msg = xoap::createMessage();
  xoap::SOAPEnvelope envelope = msg->getSOAPPart().getEnvelope();
  xoap::SOAPBody body = envelope.getBody();
  xoap::SOAPName commandName = envelope.createName("requestObjectsList","xdaq", "urn:xdaq-soap:3.0");
  xoap::SOAPElement command = body.addBodyElement(commandName );
  xdata::Integer localTid(i2o::utils::getAddressMap()->getTid(this->getApplicationDescriptor()));

  xoap::SOAPName monitorName = envelope.createName("DQMNode", "", "");
  xoap::SOAPElement monitorElement = command.addChildElement(monitorName);
  monitorElement.addTextNode(localTid.toString());

  xoap::SOAPName histoName = envelope.createName("Obj", "", "");
  xoap::SOAPName histodirName = envelope.createName("Branch", "", "");

  if (plotter_ != NULL)
    {
      /*
        int tout=0;
        while ((plotter_->isBusy()) && (tout <sTimeout*2)) {
        usleep(500000); tout++;
        };
        if (tout==sTimeout*2) {
        LOG4CPLUS_WARN (getApplicationLogger(), "Plotter is still busy after " << sTimeout << " secs");
        return msg;
        }
      */
      std::map<std::string, ME_List>& MEs = plotter_->getMEs();

      for (std::map<std::string, ME_List >::iterator itr = MEs.begin();
           itr != MEs.end(); ++itr)
        {
          xdata::String dir(itr->first);
          xoap::SOAPElement histodirElement = monitorElement.addChildElement(histodirName);
          histodirElement.addTextNode(dir);
          for (ME_List_const_iterator h_itr = itr->second.begin();
               h_itr != itr->second.end(); ++h_itr)
            {
              xdata::String hname  (h_itr->first);
              xoap::SOAPElement histoElement = histodirElement.addChildElement(histoName);
              histoElement.addTextNode(hname);

              //	LOG4CPLUS_INFO(getApplicationLogger(),
              //	       "ME: " << itr->first << "/" << h_itr->second->getFullName() << " size: " << sizeof(*(h_itr->second->getObject())));

            }
        }
    }
  appBSem_.give();
  return msg;
}

/*
xoap::MessageReference EmuTFMonitor::requestReport(xoap::MessageReference node) throw (xoap::exception::Exception)
{
  appBSem_.take();
  LOG4CPLUS_DEBUG (getApplicationLogger(), "Received Report request");
  xoap::SOAPBody rb = node->getSOAPPart().getEnvelope().getBody();
  if (rb.hasFault() )
    {
      xoap::SOAPFault fault = rb.getFault();
      std::string errmsg = "DQMNode: ";
      errmsg += fault.getFaultString();
      XCEPT_RAISE(xoap::exception::Exception, errmsg);
    }

  xoap::MessageReference msg = xoap::createMessage();
  xoap::SOAPEnvelope envelope = msg->getSOAPPart().getEnvelope();
  xoap::SOAPBody body = envelope.getBody();
  xoap::SOAPName commandName = envelope.createName("requestReport","xdaq", "urn:xdaq-soap:3.0");
  xoap::SOAPElement command = body.addBodyElement(commandName );
  xdata::Integer localTid(i2o::utils::getAddressMap()->getTid(this->getApplicationDescriptor()));

  xoap::SOAPName monitorNode = envelope.createName("DQMNode", "", "");
  xoap::SOAPElement monitorNodeElement = command.addChildElement(monitorNode);
  xoap::SOAPName nodeID("id","","");
  monitorNodeElement.addAttribute(nodeID,localTid.toString());

  xoap::SOAPName reportInfo = envelope.createName("ReportInfo", "", "");
  xoap::SOAPElement reportInfoElement = monitorNodeElement.addChildElement(reportInfo);
  xoap::SOAPName runName = envelope.createName("run","","");
  xoap::SOAPName genDate = envelope.createName("genDate","","");
  reportInfoElement.addAttribute(genDate, emu::dqm::utils::now());
  reportInfoElement.addAttribute(runName, runNumber_.toString());
  xoap::SOAPName reportList = envelope.createName("ReportList", "", "");
  xoap::SOAPElement reportListElement = monitorNodeElement.addChildElement(reportList);


  if (plotter_ != NULL)
    {
      LOG4CPLUS_INFO (getApplicationLogger(), "report stage0");
      plotter_->updateFractionHistos();
      plotter_->updateCSCFractionHistos();
      LOG4CPLUS_INFO (getApplicationLogger(), "report stage1")
      // plotter_->generateOnlineReport(runNumber_.toString());
      LOG4CPLUS_INFO (getApplicationLogger(), "report stage2");
      DQMReport dqm_report = plotter_->getDQMReport();
      T_DQMReport& report = dqm_report.getReport();
      T_DQMReport::iterator itr;
      vector<ReportEntry>::iterator entry_itr;
      for (itr = report.begin(); itr != report.end(); ++itr)
        {
          xoap::SOAPName objectTag = envelope.createName("object","","");
          xoap::SOAPElement objectElement = reportListElement.addChildElement(objectTag);
          xoap::SOAPName objID = envelope.createName("id","","");
          xoap::SOAPName objName = envelope.createName("name","","");
          objectElement.addAttribute(objID, itr->first);
          objectElement.addAttribute(objName, itr->first);
          for (entry_itr = itr->second.begin(); entry_itr != itr->second.end(); ++ entry_itr)
            {
              xoap::SOAPName entryTag = envelope.createName("entry","","");
              xoap::SOAPElement entryElement = objectElement.addChildElement(entryTag);
              xoap::SOAPName testID = envelope.createName("testID","","");
              xoap::SOAPName descr = envelope.createName("descr","","");
              xoap::SOAPName severity = envelope.createName("severity","","");
              entryElement.addAttribute(testID, entry_itr->testID);
              entryElement.addAttribute(descr, entry_itr->descr);
              entryElement.addAttribute(severity, Form("%d",entry_itr->severity));
            }

        }

    }
  appBSem_.give();
  return msg;
}
*/

xoap::MessageReference EmuTFMonitor::requestFoldersList(xoap::MessageReference node) throw (xoap::exception::Exception)
{
  appBSem_.take();
  LOG4CPLUS_DEBUG (getApplicationLogger(), "Received Folders List request");
  xoap::SOAPBody rb = node->getSOAPPart().getEnvelope().getBody();
  if (rb.hasFault() )
    {
      xoap::SOAPFault fault = rb.getFault();
      std::string errmsg = "DQMNode: ";
      errmsg += fault.getFaultString();
      XCEPT_RAISE(xoap::exception::Exception, errmsg);
    }

  xoap::MessageReference msg = xoap::createMessage();
  xoap::SOAPEnvelope envelope = msg->getSOAPPart().getEnvelope();
  xoap::SOAPBody body = envelope.getBody();
  xoap::SOAPName commandName = envelope.createName("requestFoldersList","xdaq", "urn:xdaq-soap:3.0");
  xoap::SOAPElement command = body.addBodyElement(commandName );
  xdata::Integer localTid(i2o::utils::getAddressMap()->getTid(this->getApplicationDescriptor()));

  xoap::SOAPName monitorName = envelope.createName("DQMNode", "", "");
  xoap::SOAPElement monitorElement = command.addChildElement(monitorName);
  monitorElement.addTextNode(localTid.toString());


  xoap::SOAPName histodirName = envelope.createName("Folder", "", "");

  if (plotter_ != NULL)
    {
      /*
          int tout=0;
          while ((plotter_->isBusy()) && (tout <sTimeout*2))
            {
              usleep(500000);
              tout++;
            };
          if (tout==sTimeout*2)
            {
              LOG4CPLUS_WARN (getApplicationLogger(), "Plotter is still busy after " << sTimeout << " secs");
              return msg;
            }
      */
      std::map<std::string, MECanvases_List>& MEs = plotter_->getMECanvases();

      for (std::map<std::string, MECanvases_List >::iterator itr = MEs.begin();
           itr != MEs.end(); ++itr)
        {
          xdata::String folder(itr->first);
          xoap::SOAPElement histodirElement = monitorElement.addChildElement(histodirName);
          histodirElement.addTextNode(folder);
        }
    }
  appBSem_.give();
  return msg;
}

xoap::MessageReference EmuTFMonitor::requestObjects(xoap::MessageReference node) throw (xoap::exception::Exception)
{
  LOG4CPLUS_INFO (getApplicationLogger(), "Received Monitoring Objects request");
  xoap::SOAPBody rb = node->getSOAPPart().getEnvelope().getBody();
  std::string folder = "";
  std::string objname = "";
  xoap::MessageReference msg = xoap::createMessage();
  xoap::SOAPEnvelope envelope = msg->getSOAPPart().getEnvelope();
  xoap::SOAPBody body = envelope.getBody();
  xoap::SOAPName commandName = envelope.createName("requestObjects","xdaq", "urn:xdaq-soap:3.0");
  xoap::SOAPElement command = body.addBodyElement(commandName );
  xdata::Integer localTid(i2o::utils::getAddressMap()->getTid(this->getApplicationDescriptor()));

  xoap::SOAPName monitorName = envelope.createName("DQMNode", "", "");
  xoap::SOAPElement monitorElement = command.addChildElement(monitorName);
  monitorElement.addTextNode(localTid.toString());

  appBSem_.take();
  try
    {
      if (rb.hasFault() )
        {
          xoap::SOAPFault fault = rb.getFault();
          std::string errmsg = "DQMNode: ";
          errmsg += fault.getFaultString();
          XCEPT_RAISE(xoap::exception::Exception, errmsg);
        }
      else
        {
          if (plotter_ != NULL)
            {
              /*
                     int tout=0;
                     while ((plotter_->isBusy()) && (tout <sTimeout*2))
                       {
                         usleep(500000);
                         tout++;
                       };
                     if (tout==sTimeout*2)
                       {
                         LOG4CPLUS_WARN (getApplicationLogger(), "Plotter is still busy after " << sTimeout << " secs");
                         return msg;
                       }
              */
              std::map<std::string, ME_List >& MEs = plotter_->getMEs();
              xoap::SOAPName cmdTag = envelope.createName("requestObjects","xdaq", "urn:xdaq-soap:3.0");
              std::vector<xoap::SOAPElement> content = rb.getChildElements (cmdTag);
              for (std::vector<xoap::SOAPElement>::iterator n_itr = content.begin();
                   n_itr != content.end(); ++n_itr)
                {
                  xoap::SOAPName folderTag ("Folder", "", "");
                  std::vector<xoap::SOAPElement> folderElement = n_itr->getChildElements (folderTag );
                  for (std::vector<xoap::SOAPElement>::iterator f_itr = folderElement.begin();
                       f_itr != folderElement.end(); ++f_itr)
                    {
                      folder = f_itr->getValue();
                      // == Find object folder in MEs list
                      xoap::SOAPElement folderElement = monitorElement.addChildElement(folderTag);
                      folderElement.addTextNode(folder);
                      std::map<std::string, ME_List >::iterator melist_itr = MEs.find(folder);
                      if (melist_itr != MEs.end())
                        {
                          // LOG4CPLUS_WARN (getApplicationLogger(), "Folder: " << folder);
                          xoap::SOAPName objectTag ("Object", "", "");
                          std::vector<xoap::SOAPElement> objectElement = f_itr->getChildElements (objectTag );
                          for (std::vector<xoap::SOAPElement>::iterator o_itr = objectElement.begin();
                               o_itr != objectElement.end(); ++o_itr)
                            {

                              objname = o_itr->getValue();
                              xoap::SOAPName nameTag ("Name","","");

                              // == Find object in MEs list
                              ME_List_const_iterator meobj_itr = melist_itr->second.find(objname);
                              if (meobj_itr != melist_itr->second.end())
                                {
                                  xoap::SOAPElement objectElement = folderElement.addChildElement(objectTag);
                                  objectElement.addAttribute(nameTag, objname);
                                  std::map<std::string, std::string>::iterator param_itr;
                                  std::map<std::string, std::string> params = meobj_itr->second->getParameters();
                                  for (param_itr = params.begin(); param_itr != params.end(); ++param_itr)
                                    {
                                      xoap::SOAPName paramTag (param_itr->first, "", "");
                                      xoap::SOAPElement paramElement = objectElement.addChildElement(paramTag);
                                      paramElement.addTextNode(param_itr->second);
                                    }
                                  // Check and Update detector efficiency histograms
                                  // if (objname.find("EMU_Status") != std::string::npos) plotter_->updateEfficiencyHistos();
                                  TMessage* buf = new TMessage(kMESS_OBJECT);
                                  buf->Reset();
                                  buf->SetWriteMode();

                                  int res = buf->WriteObjectAny(meobj_itr->second->getObject(), meobj_itr->second->getObject()->Class());
				  int buf_size = buf->Length();

				  if (res == 1) 
				    {
				      char * attch_buf = reinterpret_cast<char *> ( malloc(buf_size) ); // new char[buf.BufferSize()];
				      if (attch_buf != NULL)
					{
					  buf->Reset();
					  buf->SetReadMode();
					  memset(attch_buf, 0, buf_size);
					  buf->ReadBuf(attch_buf, buf_size);
					  // memcpy (attch_buf, buf->Buffer(), buf->BufferSize()); 
					  buf->Reset();
					  // memset(attch_buf, 'A', buf->BufferSize());
					  std::string contenttype = "application/octet-stream";
					  xoap::AttachmentPart * attachment = msg->createAttachmentPart(attch_buf, buf_size, contenttype);
					  //attachment->addMimeHeader("Content-Description", h_itr->first);
					  attachment->setContentLocation(folder+"/"+objname);
					  attachment->setContentEncoding("binary");
					  std::cout << "size: " <<buf->BufferSize() << ", name: " << folder << "/" << objname << std::endl;
					  msg->addAttachmentPart(attachment);
					  LOG4CPLUS_INFO (getApplicationLogger(), "Sending "<<  meobj_itr->second->getFullName());
					  delete[] attch_buf;
					  delete buf;
					}
				      else 
					{
					  LOG4CPLUS_ERROR (getApplicationLogger(), "Cannot allocate buffer for attachment");
					}
				    }
				  else 
				    {
				      LOG4CPLUS_ERROR (getApplicationLogger(), "Cannot write object to buffer");
				    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
  catch (xoap::exception::Exception &e)
    {
      LOG4CPLUS_WARN(getApplicationLogger(), xcept::stdformat_exception_history(e));
    }
  catch (xdaq::exception::Exception& e)
    {
      LOG4CPLUS_WARN(getApplicationLogger(), xcept::stdformat_exception_history(e));
    }
  catch (xcept::Exception e)
    {
      LOG4CPLUS_WARN(getApplicationLogger(), xcept::stdformat_exception_history(e));
    }
/*
  std::ofstream fout("/csc_data/mon_soap_dump.txt", ios::app);
  std::string dump="";
  fout << "------- START -------" << std::endl;
  msg->writeTo(dump);
  fout << dump<< std::endl;
  fout << "------- STOP -------" << std::endl;
  fout.close();
*/
  appBSem_.give();	  

  return msg;
}

xoap::MessageReference EmuTFMonitor::requestCanvasesList(xoap::MessageReference node) throw (xoap::exception::Exception)
{
  appBSem_.take();
  LOG4CPLUS_DEBUG (getApplicationLogger(), "Received Monitoring Canvases List request");
  xoap::SOAPBody rb = node->getSOAPPart().getEnvelope().getBody();
  if (rb.hasFault() )
    {
      xoap::SOAPFault fault = rb.getFault();
      std::string errmsg = "DQMNode: ";
      errmsg += fault.getFaultString();
      XCEPT_RAISE(xoap::exception::Exception, errmsg);
    }

  xoap::MessageReference msg = xoap::createMessage();
  xoap::SOAPEnvelope envelope = msg->getSOAPPart().getEnvelope();
  xoap::SOAPBody body = envelope.getBody();
  xoap::SOAPName commandName = envelope.createName("requestCanvasesList","xdaq", "urn:xdaq-soap:3.0");
  xoap::SOAPElement command = body.addBodyElement(commandName );
  xdata::Integer localTid(i2o::utils::getAddressMap()->getTid(this->getApplicationDescriptor()));

  xoap::SOAPName monitorName = envelope.createName("DQMNode", "", "");
  xoap::SOAPElement monitorElement = command.addChildElement(monitorName);
  monitorElement.addTextNode(localTid.toString());

  xoap::SOAPName histoName = envelope.createName("Obj", "", "");
  xoap::SOAPName histodirName = envelope.createName("Branch", "", "");

  if (plotter_ != NULL)
    {
      /*
          int tout=0;
          while ((plotter_->isBusy()) && (tout <sTimeout*2))
            {
              usleep(500000);
              tout++;
            };
          if (tout==sTimeout*2)
            {
              LOG4CPLUS_WARN (getApplicationLogger(), "Plotter is still busy after " << sTimeout << " secs");
              return msg;
            }
      */
      std::map<std::string, MECanvases_List>& MECanvases = plotter_->getMECanvases();

      for (std::map<std::string, MECanvases_List >::iterator itr = MECanvases.begin();
           itr != MECanvases.end(); ++itr)
        {
          xdata::String dir(itr->first);
          xoap::SOAPElement histodirElement = monitorElement.addChildElement(histodirName);
          histodirElement.addTextNode(dir);
          for (MECanvases_List_const_iterator h_itr = itr->second.begin();
               h_itr != itr->second.end(); ++h_itr)
            {
              xdata::String hname  (h_itr->first);
              xoap::SOAPElement histoElement = histodirElement.addChildElement(histoName);
              histoElement.addTextNode(hname);

              //	LOG4CPLUS_INFO(getApplicationLogger(),
              //       "Canvas: " << itr->first << "/" << h_itr->second->getFullName());

            }
        }
    }
  appBSem_.give();
  return msg;
}

xoap::MessageReference EmuTFMonitor::requestCanvas(xoap::MessageReference node) throw (xoap::exception::Exception)
{
  appBSem_.take();
  LOG4CPLUS_INFO (getApplicationLogger(), "Received Monitoring Canvas request");
  xoap::SOAPBody rb = node->getSOAPPart().getEnvelope().getBody();
  std::string folder = "";
  std::string objname = "";
  xoap::MessageReference msg = xoap::createMessage();
  xoap::SOAPEnvelope envelope = msg->getSOAPPart().getEnvelope();
  xoap::SOAPBody body = envelope.getBody();
  xoap::SOAPName commandName = envelope.createName("requestCanvas","xdaq", "urn:xdaq-soap:3.0");
  xoap::SOAPElement command = body.addBodyElement(commandName );
  //  xoap::SOAPName statusName = envelope.createName("Status", "", "");
  //  xoap::SOAPElement statusElement = command.addChildElement(statusName);
  xdata::Integer localTid(i2o::utils::getAddressMap()->getTid(this->getApplicationDescriptor()));
  xoap::SOAPName monitorName = envelope.createName("DQMNode", "", "");
  xoap::SOAPElement monitorElement = command.addChildElement(monitorName);
  monitorElement.addTextNode(localTid.toString());

  if (rb.hasFault() )
    {
      xoap::SOAPFault fault = rb.getFault();
      std::string errmsg = "DQMNode: ";
      errmsg += fault.getFaultString();
      XCEPT_RAISE(xoap::exception::Exception, errmsg);
    }
  else
    {
      if (plotter_ != NULL)
        {
          xoap::SOAPName cmdTag = envelope.createName("requestCanvas","xdaq", "urn:xdaq-soap:3.0");
          std::vector<xoap::SOAPElement> content = rb.getChildElements (cmdTag);
          for (std::vector<xoap::SOAPElement>::iterator n_itr = content.begin();
               n_itr != content.end(); ++n_itr)
            {
              xoap::SOAPName folderTag ("Folder", "", "");
              std::vector<xoap::SOAPElement> folderElement = n_itr->getChildElements (folderTag );
              for (std::vector<xoap::SOAPElement>::iterator f_itr = folderElement.begin();
                   f_itr != folderElement.end(); ++f_itr)
                {
                  folder = f_itr->getValue();

		  // LOG4CPLUS_WARN (getApplicationLogger(), "Folder: " << folder);
		  xoap::SOAPName objectTag ("Canvas", "", "");
		  std::vector<xoap::SOAPElement> objectElement = f_itr->getChildElements (objectTag );
		  for (std::vector<xoap::SOAPElement>::iterator o_itr = objectElement.begin();
		       o_itr != objectElement.end(); ++o_itr)
		    {
		      objname = o_itr->getValue();

		      // == Find object in MEs list
		      // ME_List_const_iterator meobj_itr = melist_itr->second.find(objname);
		      TCanvas* cnv = plotter_->getCanvas(folder+objname);
		      if (cnv != NULL)
			{
			  TMessage buf(kMESS_OBJECT);
			  buf.Reset();
			  buf.SetWriteMode();

			  int w=1200;
			  int h=800;

			  xoap::SOAPName widthTag ("Width", "", "");
			  if (o_itr->getAttributeValue(widthTag ) != "")
			     w = atoi((o_itr->getAttributeValue (widthTag )).c_str());

			  xoap::SOAPName heightTag ("Height", "", "");
			  if (o_itr->getAttributeValue (heightTag ) != "")
			     h = atoi((o_itr->getAttributeValue (heightTag )).c_str());

			  cnv->Draw();
			  cnv->SetCanvasSize(w,h);
			  // buf.WriteObjectAny(meobj_itr->second->getObject(), meobj_itr->second->getObject()->Class());
			  buf.WriteObjectAny(cnv, cnv->Class());
			  int buf_size = buf.Length();
			  char * attch_buf = new char[buf_size];
			  buf.Reset();
			  buf.SetReadMode();
			  buf.ReadBuf(attch_buf, buf_size);
			  std::string contenttype = "application/octet-stream";
			  xoap::AttachmentPart * attachment = msg->createAttachmentPart(attch_buf, buf_size, contenttype);
			  //attachment->addMimeHeader("Content-Description", h_itr->first);
			  attachment->setContentLocation(folder+objname);
			  attachment->setContentEncoding("binary");
			  msg->addAttachmentPart(attachment);
			  LOG4CPLUS_INFO (getApplicationLogger(), "Sending "<<  cnv->GetName());
			  delete []attch_buf;
			  // delete cnv;
			}
		      else
			{
			  LOG4CPLUS_WARN (getApplicationLogger(), "Can not find canvas object: " << folder << objname);
			}
		    }

                }
            }
        }
    }
  appBSem_.give();
  return msg;
}

/*
xoap::MessageReference EmuTFMonitor::requestCanvas(xoap::MessageReference node) throw (xoap::exception::Exception)
{
  appBSem_.take();
  LOG4CPLUS_DEBUG (getApplicationLogger(), "Received Monitoring Canvas request");
  xoap::SOAPBody rb = node->getSOAPPart().getEnvelope().getBody();
  std::string folder = "";
  std::string objname = "";
  xoap::MessageReference msg = xoap::createMessage();
  xoap::SOAPEnvelope envelope = msg->getSOAPPart().getEnvelope();
  xoap::SOAPBody body = envelope.getBody();
  xoap::SOAPName commandName = envelope.createName("requestCanvas","xdaq", "urn:xdaq-soap:3.0");
  xoap::SOAPElement command = body.addBodyElement(commandName );
  //  xoap::SOAPName statusName = envelope.createName("Status", "", "");
  //  xoap::SOAPElement statusElement = command.addChildElement(statusName);
  xdata::Integer localTid(i2o::utils::getAddressMap()->getTid(this->getApplicationDescriptor()));
  xoap::SOAPName monitorName = envelope.createName("DQMNode", "", "");
  xoap::SOAPElement monitorElement = command.addChildElement(monitorName);
  monitorElement.addTextNode(localTid.toString());

  if (rb.hasFault() )
    {
      xoap::SOAPFault fault = rb.getFault();
      std::string errmsg = "DQMNode: ";
      errmsg += fault.getFaultString();
      XCEPT_RAISE(xoap::exception::Exception, errmsg);
    }
  else
    {
      if (plotter_ != NULL)
        {
          std::map<std::string, ME_List >& MEs = plotter_->getMEs();
          std::map<std::string, MECanvases_List >& MECanvases = plotter_->getMECanvases();
          xoap::SOAPName cmdTag = envelope.createName("requestCanvas","xdaq", "urn:xdaq-soap:3.0");
          std::vector<xoap::SOAPElement> content = rb.getChildElements (cmdTag);
          for (std::vector<xoap::SOAPElement>::iterator n_itr = content.begin();
               n_itr != content.end(); ++n_itr)
            {
              xoap::SOAPName folderTag ("Folder", "", "");
              std::vector<xoap::SOAPElement> folderElement = n_itr->getChildElements (folderTag );
              for (std::vector<xoap::SOAPElement>::iterator f_itr = folderElement.begin();
                   f_itr != folderElement.end(); ++f_itr)
                {
                  folder = f_itr->getValue();
                  // == Find object folder in MEs list
                  // std::map<std::string, ME_List >::iterator melist_itr = MEs.find(folder);
                  std::map<std::string, MECanvases_List >::iterator cnvlist_itr = MECanvases.find(folder);
                  // if (melist_itr != MEs.end())
                  if (cnvlist_itr != MECanvases.end())
                    {
                      // LOG4CPLUS_WARN (getApplicationLogger(), "Folder: " << folder);
                      xoap::SOAPName objectTag ("Canvas", "", "");
                      std::vector<xoap::SOAPElement> objectElement = f_itr->getChildElements (objectTag );
                      for (std::vector<xoap::SOAPElement>::iterator o_itr = objectElement.begin();
                           o_itr != objectElement.end(); ++o_itr)
                        {
                          objname = o_itr->getValue();

                          // == Find object in MEs list
                          // ME_List_const_iterator meobj_itr = melist_itr->second.find(objname);
                          MECanvases_List_const_iterator cnvobj_itr = cnvlist_itr->second.find(folder+objname);
                          if (cnvobj_itr != cnvlist_itr->second.end())
                            {
                              TMessage buf(kMESS_OBJECT);
                              buf.Reset();
                              buf.SetWriteMode();
                              // EmuTFMonitoringCanvas* cnv = new EmuTFMonitoringCanvas(*(cnvobj_itr->second));
                              EmuMonitoringCanvas* cnv = cnvobj_itr->second;

                              xoap::SOAPName widthTag ("Width", "", "");
                              if (o_itr->getAttributeValue(widthTag ) != "")
                                cnv->setCanvasWidth(atoi((o_itr->getAttributeValue (widthTag )).c_str()));

                              xoap::SOAPName heightTag ("Height", "", "");
                              if (o_itr->getAttributeValue (heightTag ) != "")
                                cnv->setCanvasHeight(atoi((o_itr->getAttributeValue (heightTag )).c_str()));

                              std::string runNum = runNumber_.toString();
                              if (runNumber_ == xdata::UnsignedInteger(0)) runNum="N/A";
                              cnv->setRunNumber(runNum);
                              // cnv->Draw(melist_itr->second);
                              cnv->getCanvasObject()->Draw();
                              // buf.WriteObjectAny(meobj_itr->second->getObject(), meobj_itr->second->getObject()->Class());
                              buf.WriteObjectAny(cnv->getCanvasObject(), cnv->getCanvasObject()->Class());
                              char * attch_buf = new char[buf.BufferSize()];
                              buf.Reset();
                              buf.SetReadMode();
                              buf.ReadBuf(attch_buf, buf.BufferSize());
                              std::string contenttype = "application/octet-stream";
                              xoap::AttachmentPart * attachment = msg->createAttachmentPart(attch_buf, buf.BufferSize(), contenttype);
                              //attachment->addMimeHeader("Content-Description", h_itr->first);
                              attachment->setContentLocation(folder+objname);
                              attachment->setContentEncoding("binary");
                              msg->addAttachmentPart(attachment);
                              LOG4CPLUS_DEBUG (getApplicationLogger(), "Sending "<<  cnv->getFullName());
                              delete []attch_buf;
                              // delete cnv;
                            }
                          else
                            {
                              LOG4CPLUS_WARN (getApplicationLogger(), "Can not find canvas object: " << objname);
                            }
                        }
                    }
                  else
                    {
                      LOG4CPLUS_WARN (getApplicationLogger(), "Can not find folder: " << folder);
                    }

                }
            }
        }
    }
  appBSem_.give();
  return msg;
}
*/

xoap::MessageReference EmuTFMonitor::requestCSCCounters(xoap::MessageReference node) throw (xoap::exception::Exception)
{
  appBSem_.take();
  LOG4CPLUS_DEBUG (getApplicationLogger(), "Received CSC Counters request");
  xoap::SOAPBody rb = node->getSOAPPart().getEnvelope().getBody();
  xoap::MessageReference msg = xoap::createMessage();
  xoap::SOAPEnvelope envelope = msg->getSOAPPart().getEnvelope();
  xoap::SOAPBody body = envelope.getBody();
  xoap::SOAPName commandName = envelope.createName("requestCSCCounters","xdaq", "urn:xdaq-soap:3.0");
  xoap::SOAPElement command = body.addBodyElement(commandName );
  xdata::Integer localTid(i2o::utils::getAddressMap()->getTid(this->getApplicationDescriptor()));

  xoap::SOAPName monitorName = envelope.createName("DQMNode", "", "");
  xoap::SOAPElement monitorElement = command.addChildElement(monitorName);
  monitorElement.addTextNode(localTid.toString());

  if (rb.hasFault() )
    {
      xoap::SOAPFault fault = rb.getFault();
      std::string errmsg = "DQMNode: ";
      errmsg += fault.getFaultString();
      XCEPT_RAISE(xoap::exception::Exception, errmsg);
    }
  else
    {


      //  xoap::SOAPName cntName = envelope.createName("Obj", "", "");
      xoap::SOAPName cscName = envelope.createName("CSC", "", "");

      if (plotter_ != NULL)
        {
          std::map<std::string, CSCCounters >& cntrs = plotter_->getCSCCounters();
          // std::cout << cntrs.size()<< std::endl;
          for (std::map<std::string, CSCCounters >::iterator itr = cntrs.begin();
               itr != cntrs.end(); ++itr)
            {
              xdata::String csc(itr->first);
              xoap::SOAPElement cscElement = monitorElement.addChildElement(cscName);
              cscElement.addTextNode(csc);
              // std::cout << csc.toString() << std::endl;
              // std::cout << itr->second.size() << std::endl;

              for (CSCCounters::iterator c_itr = itr->second.begin(); c_itr != itr->second.end(); ++c_itr)
                {
                  xdata::String name = c_itr->first;
                  xdata::UnsignedInteger value = c_itr->second;
                  // LOG4CPLUS_INFO (getApplicationLogger(), csc.toString() << ": " << name.toString() << "=" << value.toString());

                  xoap::SOAPName cntrName = envelope.createName(name, "", "");
                  xoap::SOAPElement cntElement = cscElement.addChildElement(cntrName);
                  cntElement.addTextNode(value.toString());

                }

            }
        }
    }
  appBSem_.give();
  return msg;
}
