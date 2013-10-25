#pragma once

#include <iostream>
#include <map>
#include "cinder/app/App.h"
#include "DataTypes.h"

// Debug console output
class DemoUtil {
public:
  static std::ostream& LogStream(const char* id, float logPeriod) {
    static std::map<const char*, double> timestamps;
    std::map<const char*, double>::const_iterator it = timestamps.find(id);
    double lastTime = 0.0;
    if (it != timestamps.end()) {
      lastTime = it->second;
    }
    double time = ci::app::getElapsedSeconds();
    if (logPeriod < time - lastTime) 
    {
      timestamps[id] = time;
      return std::cout;
    } else {
      static std::ostream cnul(0);
      cnul.clear();
      return cnul;
    }
  }
};

#define LM_STRING(x) #x
#define LM_LOG_STREAM(file, line, period) DemoUtil::LogStream(file ":" LM_STRING(line), period)

#define LM_LOG LM_LOG_STREAM(__FILE__, __LINE__, 1)
#define LM_LOG2(logPeriod) LM_LOG_STREAM(__FILE__, __LINE__, logPeriod)

// todo: allow logs with id's passed as arguments. Can't do this now as the map stores the pointers to strings.
// so they have to be constant in mem.
//#define LM_LOG_ID(id) LM_LOG_STREAM_ID(__FILE__, __LINE__, id, 1)

template <typename T>
inline T lmClip(T val, T min, T max) {
   val = std::min(val, 1.0f);
   val = std::max(0.0f, val);
   return val;
}

template <typename T>
inline T lmInterpolate(lmReal t, const T& v0, const T& v1) {
  return (1-t)*v0+t*v1;
}