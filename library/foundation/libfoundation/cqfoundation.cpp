//Don't change this file manually, it was generated by automation tool.

#include "cqfoundation.hh"
#include "cqbridge.hh"

CQ_C_LINK void CQ_Logger_info(CQType message, CQType file, CQType line);
CQ_C_LINK void CQ_Logger_error(CQType message, CQType file, CQType line);

void CQLogger::info(const std::string &message, const std::string &file, int32_t line) {
    CQType aa = CQValue<std::string>::create(message);
    CQType bb = CQValue<std::string>::create(file);
    CQType cc = CQValue<int32_t>::create(line);
    CQ_Logger_info(aa, bb, cc);
    CQRelease(aa);
    CQRelease(bb);
    CQRelease(cc);
}

void CQLogger::error(const std::string &message, const std::string &file, int32_t line) {
    CQType aa = CQValue<std::string>::create(message);
    CQType bb = CQValue<std::string>::create(file);
    CQType cc = CQValue<int32_t>::create(line);
    CQ_Logger_error(aa, bb, cc);
    CQRelease(aa);
    CQRelease(bb);
    CQRelease(cc);
}
