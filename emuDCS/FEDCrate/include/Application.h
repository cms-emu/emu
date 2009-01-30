/*****************************************************************************\
* $Id: Application.h,v 3.2 2009/01/30 19:14:16 paste Exp $
*
* $Log: Application.h,v $
* Revision 3.2  2009/01/30 19:14:16  paste
* New emu::base namespace and emu::base::Supervised inheritance added.
*
* Revision 3.1  2009/01/29 15:31:22  paste
* Massive update to properly throw and catch exceptions, improve documentation, deploy new namespaces, and prepare for Sentinel messaging.
*
* Revision 3.11  2008/11/15 13:59:14  paste
* Added initial support for AJAX communication.
*
* Revision 3.10  2008/10/29 16:01:43  paste
* Updated interoperability with primative DCC commands, added new xdata variables for future use.
*
* Revision 3.9  2008/10/13 11:56:40  paste
* Cleaned up some of the XML config files and scripts, added more SVG, changed the DataTable object to inherit from instead of contain stdlib objects (experimental)
*
* Revision 3.8  2008/10/09 11:21:19  paste
* Attempt to fix DCC MPROM load.  Added debugging for "Global SOAP death" bug.  Changed the debugging interpretation of certain DCC registers.  Added inline SVG to EmuFCrateManager page for future GUI use.
*
* Revision 3.7  2008/10/04 18:44:05  paste
* Fixed bugs in DCC firmware loading, altered locations of files and updated javascript/css to conform to WC3 XHTML standards.
*
* Revision 3.6  2008/08/25 12:25:49  paste
* Major updates to VMEController/VMEModule handling of CAEN instructions.  Also, added version file for future RPMs.
*
* Revision 3.5  2008/08/15 16:14:50  paste
* Fixed threads (hopefully).
*
* Revision 3.4  2008/08/15 08:35:50  paste
* Massive update to finalize namespace introduction and to clean up stale log messages in the code.
*
*
\*****************************************************************************/
#ifndef __EMUFEDAPPLICATION_H__
#define __EMUFEDAPPLICATION_H__

#include "emu/base/Supervised.h"
#include "FEDException.h"

#include <string>
#include <vector>

#include "xoap/DOMParser.h"
#include "xoap/MessageReference.h"
#include "xdata/soap/Serializer.h"
#include "xoap/SOAPName.h"
#include "xdata/xdata.h"
#include "xdaq/NamespaceURI.h"
#include "xdata/soap/NamespaceURI.h"
#include "xoap/domutils.h"
#include "xgi/Input.h"
#include "toolbox/fsm/FiniteStateMachine.h"
#include "xoap/Method.h"

#define DEFINE_DEFAULT_SOAP2FSM_ACTION( COMMAND ) \
xoap::MessageReference on ##COMMAND(xoap::MessageReference message) \
{ \
	LOG4CPLUS_DEBUG(getApplicationLogger(), "FSM state change requested:  " #COMMAND); \
	fireEvent(#COMMAND); \
	return createReply(message); \
}

#define BIND_DEFAULT_SOAP2FSM_ACTION( CLASS, COMMAND ) xoap::bind(this, &CLASS::on ##COMMAND, #COMMAND, XDAQ_NS_URI);

namespace emu {
	namespace fed {
		
		class Application: public emu::base::Supervised {

		public:

			/** Default constructor. **/
			Application(xdaq::ApplicationStub *stub);

			/** Sends the GetParameters SOAP command to a target application.
			*
			*	@param applicationDescriptor is a pointer to the target application's
			*	descriptor.
			*	@returns a SOAP message reply for use with @sa readParameter.
			*
			*	@author Phillip Killewald &lt;paste@mps.ohio-state.edu&gt;
			**/
			xoap::MessageReference getParameters(xdaq::ApplicationDescriptor *applicationDescriptor)
			throw (emu::fed::SOAPException);

			/** Sends the GetParameters SOAP command to a target application.
			*
			*	@param applicationName is the class name of the application from which
			*	you are requesting parameters.
			*	@param instance is the instance of the application to which you are
			*	sending the request.
			*	@returns a SOAP message reply for use with @sa readParameter.
			*
			*	@author Phillip Killewald &lt;paste@mps.ohio-state.edu&gt;
			**/
			xoap::MessageReference getParameters(std::string applicationName, unsigned int instance)
			throw (emu::fed::SOAPException);

			/** Sets a parameter in a remote application.  I don't know where the
			*	binding to this command is set, but it seems to affect all
			*	of the applications we are concerned with.
			*
			*	@param klass is the target application class name (this
			*	function sends to all of the instances of that class.)
			*	@param name is the name of the variable you want to set.
			*	@param type is the type of the varialbe you want to set.  Use
			*	std::strings like "xsd:string" and "xsd:unsignedLong".
			*	@param value is a std::string representation of the value to be set.
			*	@param instance is the instance of the application whose parameter
			*	you want to set.  Optional.  Negative numbers will result in all
			*	applications of class name klass being sent the message.
			*
			*	@note Because I don't know where this call is handled, I do not
			*	know anything about error handling.  Just try to make sure
			*	the variable exists in the exported InfoSpace of the target
			*	application, and that the types match.
			*
			*	@author Phillip Killewald (stolen from Laria's CSCSupervisor.cc)
			**/
			void setParameter(std::string klass, std::string name, std::string type, std::string value, int instance = -1)
			throw (emu::fed::SOAPException);

			/** Reads a reply from onGetParameters and returns a named parameter from
			*	a target ApplicationInfoSpace.
			*
			*	@note We cannot separate templated declarations from templated definitions.
			*	Sorry.
			*
			*	@param message is the SOAP reply from onGetParameters containing a
			*	serialized form of the target ApplicationInfoSpace.
			*	@param parameterName is the name of whatever you want from the
			*	target ApplicationInfoSpace.
			*
			*	@author Phillip Killewald &lt;paste@mps.ohio-state.edu&gt;
			**/
			template<typename T>
			T readParameter(xoap::MessageReference message, std::string parameterName)
			throw (emu::fed::SOAPException)
			{
				T thingToGet;
				xdata::soap::Serializer serializer;
				xoap::DOMParser *parser;
				try {
					parser = new xoap::DOMParser();
				} catch (xoap::exception::Exception &e) {
					std::ostringstream error;
					error << "Unable to construct xoap DOMParser";
					XCEPT_RETHROW(emu::fed::SOAPException, error.str(), e);
				}

				std::string messageStr;
				message->writeTo(messageStr);
				xercesc::DOMDocument *doc;
				try {
					doc = parser->parse(messageStr);
				} catch (xoap::exception::Exception &e) {
					std::ostringstream error;
					error << "Unable to parse SOAP message: " << messageStr;
					XCEPT_RETHROW(emu::fed::SOAPException, error.str(), e);
				}

				//xoap::SOAPElement sInfoSpace = message->getSOAPPart().getEnvelope().getBody().getChildElements(*(new xoap::SOAPName("GetParametersResponse", "", "")))[0];

				xoap::SOAPName *name = new xoap::SOAPName(parameterName, "xdaq", XDAQ_NS_URI);
				//std::cout << "Looking for " << name->getQualifiedName() << ", " << name->getURI() << std::endl;


				xercesc::DOMNodeList *dataNode = doc->getElementsByTagNameNS(xoap::XStr(XDAQ_NS_URI), xoap::XStr("data"));
				xercesc::DOMNodeList *dataElements = dataNode->item(0)->getChildNodes();

				bool found = false;
				for (unsigned int j = 0; j < dataElements->getLength(); j++) {
					xercesc::DOMNode *n = dataElements->item(j);
					if (n->getNodeType() == xercesc::DOMNode::ELEMENT_NODE) {
						std::string nodeName = xoap::XMLCh2String(n->getNodeName());
						if (nodeName == name->getQualifiedName()) {
							serializer.import (&thingToGet, n);
							found = true;
							break;
						}
					}
				}
				if (!found) {
					std::ostringstream error;
					error << "Unable to find parameter " << parameterName;
					XCEPT_RAISE(emu::fed::SOAPException, error.str());
				}
				return thingToGet;
			}

			/** Returns a standard Header for the EmuFCrate pages.  Displays a title,
			*	 the experts (with links), and some cool pictures.
			*
			*	@param myTitle is the title that will be displayed at the top of the
			*	 page.
			*	@param jsFileNames is a vector of file names to be included as javascripts,
			*	 see the directory FEDCrate/js for a list of files one can include.
			*	@returns a huge std::string that is basically the header of the page in
			*	 HTML.  Good for outputting straight to the xgi::Output.
			**/
			virtual std::string Header(std::string myTitle, std::vector<std::string> jsFileNames);
			virtual inline std::string Header(std::string myTitle)
			{
				std::vector<std::string> fileNames;
				return Header(myTitle, fileNames);
			}

			/** Returns the standard Footer for the EmuFCrate applications.
			*
			*	@returns a huge std::string that is basically the footer code in HTML.  Good
			*	 for outputting straight to the xgi::Output.
			**/
			virtual std::string Footer();

			/** Dumps out information from the CGI input variable for debugging.
			*
			*	@param in is the standard CGI input variable that is passed to almost
			*	everything.
			*
			*	@returns a string with a mess of debugging text.
			**/
			std::string dumpEnvironment(xgi::Input *in);

			/** Serializes this application's ApplicationInfoSpace and returns it.
			*	As things stand, is bound to the "GetParameters" SOAP command.
			*
			*	@author Phillip Killewald &lt;paste@mps.ohio-state.edu&gt;
			**/
			xoap::MessageReference onGetParameters(xoap::MessageReference message);

			/** Method used as a general call-back from FSM state changes.
			*
			*	@param fsm is the finite state machine that just transitioned stated
			**/
			//void stateChanged(toolbox::fsm::FiniteStateMachine &fsm);

			/** Method used as a general call-back when the FSM transitions to the Failed state.
			*
			*	@param event is the event (exception) that caused the failure
			**/
			//void transitionFailed(toolbox::Event::Reference event);

			/** Method that will cause the FSM to perform a transition bound to a given event if it exists.
			*
			*	@param event is the named transition that the FSM will attempt to perform.
			**/
			//void fireEvent(std::string event);

			/** Creates a simple reply to a SOAP command.
			*
			*	@param message is the message to which a reply is generated
			**/
			//xoap::MessageReference createSOAPReply(xoap::MessageReference message);

			/** Fire a FSM transition command from a CGI GET parameter.
			*
			*	@param in is the standard XGI input.  Requires a field named "action" with a string corresponding to the requested transition
			*	@param out is the standard XGI output
			*
			*	@author Phillip Killewald &lt;paste@mps.ohio-state.edu&gt;
			**/
			void webFire(xgi::Input *in, xgi::Output *out);

			/** Redirect the browser to the default page.
			*
			*	@param in is the standard XGI input
			*	@param out is the standard XGI output
			*	@param location is the URL to where the browser will redirect
			*
			*	@author Phillip Killewald &lt;paste@mps.ohio-state.edu&gt;
			**/
			void webRedirect(xgi::Input *in, xgi::Output *out, std::string location = "");
			inline void webRedirect (xgi::Output *out, std::string location = "") { return webRedirect(new xgi::Input("", 0), out, location); }

			/** Create a simple SOAP command for FSM transitions.
			*
			*	@param command is the FSM transition command
			**/
			xoap::MessageReference createSOAPCommand(std::string command);

			/** Send a SOAP command to a given application or applications
			*
			*	@param command is the command to be send
			*	@param klass is the name of the class to which the command should be sent
			*	@param instance is the instance of the given class to which the command should be sent.  A -1 value means send to all instances of the given class.
			**/
			void sendSOAPCommand(std::string command, std::string klass, int instance = -1)
			throw (emu::fed::SOAPException);

		protected:

			/// The finite state machine!
			toolbox::fsm::FiniteStateMachine fsm_;

			/// The run number of the current run.  Useful for log files.
			xdata::UnsignedLong runNumber_;

			/// The "endcap" for the application.  This is just some name that can be used to distinguish differently-configured applications from each other.
			xdata::String endcap_;

			/// The text string that represents the current FSM state.
			xdata::String state_;

			/// Whether or not the current state has been transitioned to via SOAP or via a web request.
			bool soapLocal_;

		};
	}
}


#endif
