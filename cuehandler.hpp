#ifndef CUEHANDLER_HPP
#define CUEHANDLER_HPP

#include <vtkAnimationCue.h>
#include <vtkCommand.h>
#include <vtkRenderer.h>

#include "animationhandler.hpp"

class CueHandler : public vtkCommand {
  public:
  static CueHandler *New();
    
  void Execute(vtkObject *vtkNotUsed(caller), unsigned long event, void *calldata);
  void RegisterAnimator(std::shared_ptr<AnimationHandler> animatorptr);
  void RegisterRenderer(vtkRenderer* renderptr);

  protected:
  std::shared_ptr<AnimationHandler> animator;
  vtkRenderer *renderer;

};

#endif
