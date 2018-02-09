#ifdef _WIN32

#include <windows.h>
#include <stdio.h>
#include "ITimer.h"

class	WindowsTimer : public ITimer
{
 public:
  WindowsTimer();
  virtual ~WindowsTimer();

  virtual void	run(int);
};
#endif
