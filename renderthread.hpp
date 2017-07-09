#ifndef RENDERTHREAD_HPP
#define RENDERTHREAD_HPP

#include <vtkAnimationScene.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

class RenderThread{
  public:

  void init_renderwindow(size_t x_res, size_t y_res);
  void init_scene(double scene_length);
  void register_animator(std::shared_ptr<AnimationHandler> animator);
  void execute();

  protected:
  double end_time;

  vtkSmartPointer<vtkRenderWindowInteractor> iren;
  vtkSmartPointer<vtkRenderer> renderer;
  vtkSmartPointer<vtkRenderWindow> renderwindow;
  vtkSmartPointer<vtkAnimationScene> scene;
  vtkSmartPointer<vtkAnimationCue> cue;
  vtkSmartPointer<CueHandler> cuehandler;
  std::shared_ptr<AnimationHandler> animator;
  
};

void RenderThread::init_renderwindow(size_t x_res, size_t y_res){
  this->iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  this->renderer = vtkSmartPointer<vtkRenderer>::New();
  this->renderwindow = vtkSmartPointer<vtkRenderWindow>::New();

  this->renderwindow->SetMultiSamples(0); //hw antialiasing level
  this->renderer->SetBackground(0,0,0);
  this->iren->SetRenderWindow(renderwindow); 
  this->renderwindow->AddRenderer(renderer);
  this->renderwindow->SetSize(800,800);
  this->renderwindow->Render(); //extra render before modified() seems to fix tiling wm behaviour
  this->renderwindow->Modified();
  this->renderwindow->Render();
}

void RenderThread::init_scene(double scene_length){
  this->end_time = scene_length;

  this->scene = vtkSmartPointer<vtkAnimationScene>::New();
  this->cue = vtkSmartPointer<vtkAnimationCue>::New();
  this->cuehandler = vtkSmartPointer<CueHandler>::New();
  
  this->scene->SetModeToRealTime();
  this->scene->SetLoop(0);
  this->scene->SetStartTime(0.);
  this->scene->SetEndTime(scene_length);
  this->scene->AddCue(cue);

  this->cue->SetStartTime(0);
  this->cue->SetEndTime(scene_length);
  this->cue->AddObserver(vtkCommand::StartAnimationCueEvent, cuehandler);
  this->cue->AddObserver(vtkCommand::EndAnimationCueEvent, cuehandler);
  this->cue->AddObserver(vtkCommand::AnimationCueTickEvent, cuehandler);

  this->cuehandler->RegisterRenderer(this->renderer);
}

void RenderThread::register_animator(std::shared_ptr<AnimationHandler> animator){
  this->animator = animator;
  this->cuehandler->RegisterAnimator(animator);
}

void RenderThread::execute(){
  this->scene->Play();
}

#endif
