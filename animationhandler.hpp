#ifndef ANIMATIONHANDLER_HPP
#define ANIMATIONHANDLER_HPP

class AnimationHandler{
  public:

  virtual void Start(vtkAnimationCue::AnimationCueInfo *info, vtkRenderer *ren) =0;
  virtual void Tick(vtkAnimationCue::AnimationCueInfo *info, vtkRenderer *ren) =0;
  virtual void Stop(vtkAnimationCue::AnimationCueInfo *info, vtkRenderer *ren) =0;
};

#endif
