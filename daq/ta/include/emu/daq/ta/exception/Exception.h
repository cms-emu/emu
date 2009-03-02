#ifndef _emu_daq_ta_exception_Exception_h_
#define _emu_daq_ta_exception_Exception_h_

#include "xcept/Exception.h"

/**
 * Exceptions thrown by the  package in the
 * namespace emu::daq::ta::exception
 */

namespace emu { namespace daq {
    
  /**
   * Generic exception raised by the emu::daq::ta package.
   */
//   XCEPT_DEFINE_EXCEPTION(ta, Exception)

  /**
   * I2O exception raised by the emu::daq::ta package.
   */
//   XCEPT_DEFINE_EXCEPTION(ta, I2O)

// TODO: revert to definition by macro

  namespace ta{
    namespace exception{
        class Exception: public xcept::Exception
        {
            public:

            Exception(std::string name,
                      std::string message,
                      std::string module,
                      int line,
                      std::string function)
            : xcept::Exception(name, message, module, line, function)
            {
            }

            Exception(std::string name,
                      std::string message,
                      std::string module,
                      int line,
                      std::string function,
                      xcept::Exception & e)
            : xcept::Exception(name, message, module, line, function, e)
            {
            }
        };
    }
  }

}}

#endif
