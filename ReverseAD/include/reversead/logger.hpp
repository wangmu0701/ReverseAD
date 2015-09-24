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
  void reset(std::ostream* sink) {
    _sink = sink;
  }
  Logger(std::ostream* sink) :_sink(sink), _fatal(false){};
  Logger(std::ostream* sink, bool fatal) : _sink(sink), _fatal(fatal) {};

  std::ostream* _sink;
  const bool _fatal;

  friend class Log;
};

class Log {
 public:
  void reset_info(std::ostream* infosink) {
    info.reset(infosink);
  }
  Log(std::ostream* infosink, std::ostream* warnsink, std::ostream* fatalsink)
    : info(infosink), warning(warnsink), fatal(fatalsink, true) {};
  Logger info;
  Logger warning;
  Logger fatal;
};

} // namespace ReverseAD

#endif // REVERSE_AD_LOGGER_H_
