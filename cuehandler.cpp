#include "cuehandler.hpp"

CueHandler *CueHandler::New(){
  return new CueHandler;
}

/*void CueHandler::Execute(vtkObject *vtkNotUsed(caller), unsigned long event, void *calldata){
  if((this->animator != 0) && (this->renderer != 0)){
    vtkAnimationCue::AnimationCueInfo *info =
      static_cast<vtkAnimationCue::AnimationCueInfo *>(calldata);
    switch(event){
      case vtkCommand::StartAnimationCueEvent:
        animator->Start(info, this->renderer);
        break;
      case vtkCommand::AnimationCueTickEvent:
        animator->Tick(info, this->renderer);
        break;
      case vtkCommand::EndAnimationCueEvent:
        animator->Stop(info, this->renderer);
        break;
    }
  }
}
*/

void CueHandler::Execute(vtkObject *vtkNotUsed(caller), unsigned long event, void *calldata){
  animator->render();
}

void CueHandler::RegisterAnimator(std::shared_ptr<ImageAnimator> animatorptr){
  this->animator = animatorptr;
}

void CueHandler::RegisterRenderer(vtkRenderer* renderptr){
  this->renderer = renderptr;
}

