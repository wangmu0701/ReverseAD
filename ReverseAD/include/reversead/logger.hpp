#ifndef REVERSE_AD_LOGGER_H_
#define REVERSE_AD_LOGGER_H_

#include <iostream>

namespace ReverseAD {

class Log;

class Logger {
 public:
  template <typename T>
  friend Logger& operator << (Logger& os, const T& content) {
    if (os._sink) {
      (*(os._sink)) << content;
    }
    return os;
  }
  friend Logger& operator << (Logger& os, std::ostream& (*f)(std::ostream&)) {
    if (os._sink) {
      f(*(os._sink));
    }
    if (os._fatal) {
      (*os._sink) << "Fatal error encountered, halt!" << std::endl;
      exit(-1);
    }
    return os;
  }
 private:
  Logger(std::ostream* sink) :_sink(sink), _fatal(false){};
  Logger(std::ostream* sink, bool fatal) : _sink(sink), _fatal(fatal) {};

  std::ostream* const _sink;
  const bool _fatal;

  friend class Log;
};

class Log {
 public:
  Log(std::ostream* infosink, std::ostream* fatalsink)
    : info(infosink), fatal(fatalsink, true) {};
  Logger info;
  Logger fatal;
};

} // namespace ReverseAD

#endif // REVERSE_AD_LOGGER_H_
