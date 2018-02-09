#pragma once

class ITimer
{
 public:
  virtual ~ITimer() {}

  virtual void	run(int) = 0;
};
