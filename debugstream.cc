#include "debugstream.h"

#include <utility>

void DebugSendStringCallBack_Default_(const char *str, int num) {
  printf("%.*s",num,str);
}

DebugStreamEndl endl;


DebugStream::DebugStream \
(std::function<void(const char*,int)>  fun_ , int buf_len_ ) : fun(std::move(fun_)) ,buf_len(buf_len_)  {
  DebugStreamBuf = new char[buf_len];
}
DebugStream::DebugStream(const DebugStream &obj) {
  this->buf_len = obj.buf_len;
  this->out_en = obj.out_en;
  this->fun = obj.fun;
  // Re-divide a piece of memory, and the function pointer does not need to be reset
  this->DebugStreamBuf = new char[this->buf_len];
}
DebugStream &DebugStream::operator=(const DebugStream &obj) {
  if (this->DebugStreamBuf != nullptr) {
    // Compared with the copy construction, the memory originally pointed to by delete is required
    delete DebugStreamBuf;
  }
  this->buf_len = obj.buf_len;
  this->out_en = obj.out_en;
  this->fun = obj.fun;
  // Re-divide a piece of memory, and the function pointer does not need to be reset
  this->DebugStreamBuf = new char[this->buf_len];
  return *this;
}
DebugStream::~DebugStream() {
  if(newline) (*this)("\n");
  if (this->DebugStreamBuf != nullptr) {
    delete DebugStreamBuf;
  }
}

DebugStream &DebugStream::operator()(const char *fmt, ...) {
#ifdef NO_DEBUG_OUTPUT //
  return *this;
#endif // NO_DEBUG_OUTPUT
  if (!this->out_en) {
    return *this;
  }
  va_list ap;
  va_start(ap, fmt);
  vsprintf((char *) DebugStreamBuf, fmt, ap);
  va_end(ap);
  uint16_t i = strlen((const char *) DebugStreamBuf);
  fun(DebugStreamBuf, i);

  // solve the bug that add newline still add space
  if(DebugStreamBuf[i-1]==0X0A||DebugStreamBuf[i-1]==0X0D) {
    newline_= true;
  }

  return *this;
}

