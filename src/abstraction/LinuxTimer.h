#ifndef _WIN32

#include <unistd.h>
#include "ITimer.h"

class   LinuxTimer : public ITimer
{
 public:
  LinuxTimer();
  virtual ~LinuxTimer();

  virtual void	run(int);
};
#endif
