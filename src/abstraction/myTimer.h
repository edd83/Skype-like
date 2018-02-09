#include "WindowsTimer.h"
#include "LinuxTimer.h"

class	myTimer :
#ifdef _WIN32
public WindowsTimer
#else
public LinuxTimer
#endif
{
 public:
  myTimer() {}
  ~myTimer() {}
};
