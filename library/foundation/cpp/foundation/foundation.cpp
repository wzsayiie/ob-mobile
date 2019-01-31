//Don't change this file manually, it was generated by automation tool.

#include "foundation.h"
#include "bridge.h"

BRG_EXPORT void FDN_Logger_info(BRGType message);
BRG_EXPORT void FDN_Logger_error(BRGType message);

namespace FDN {
    
    void Logger::info(const std::string &message) {
        BRGType aa = BRGValue<std::string>::create(message);
        FDN_Logger_info(aa);
        BRGRelease(aa);
    }
    
    void Logger::error(const std::string &message) {
        BRGType aa = BRGValue<std::string>::create(message);
        FDN_Logger_error(aa);
        BRGRelease(aa);
    }
}