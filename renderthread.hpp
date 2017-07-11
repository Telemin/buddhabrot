#ifndef RENDERTHREAD_HPP
#define RENDERTHREAD_HPP

#include <vtkAnimationScene.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkCommand.h>

#include "newanimator.hpp"

class RenderThread{
  public:

  void init_renderwindow(size_t x_res, size_t y_res);
  void init_scene(double scene_length);
  void register_animator(std::shared_ptr<ImageAnimator> animator);
  void execute();

  protected:
  double end_time;

  vtkSmartPointer<vtkRenderWindowInteractor> iren;
  vtkSmartPointer<vtkInteractorStyleImage> istyle;
  vtkSmartPointer<vtkRenderer> renderer;
  vtkSmartPointer<vtkRenderWindow> renderwindow;
  vtkSmartPointer<vtkAnimationScene> scene;
  vtkSmartPointer<vtkAnimationCue> cue;
  vtkSmartPointer<CueHandler> cuehandler;
  std::shared_ptr<ImageAnimator> animator;
  
};

void RenderThread::init_renderwindow(size_t x_res, size_t y_res){
  this->istyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
  this->istyle->SetInteractionModeToImage2D();

  this->renderer = vtkSmartPointer<vtkRenderer>::New();
  this->renderer->SetBackground(0,0,0);

  this->renderwindow = vtkSmartPointer<vtkRenderWindow>::New();
  this->renderwindow->SetMultiSamples(0); //hw antialiasing level
  this->renderwindow->AddRenderer(renderer);
  this->renderwindow->SetSize(x_res,y_res);

  this->iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  this->iren->SetRenderWindow(renderwindow); 
  this->iren->SetInteractorStyle(this->istyle);
  this->iren->Initialize();

}

void RenderThread::init_scene(double scene_length){
  this->cuehandler = vtkSmartPointer<CueHandler>::New();
  this->iren->AddObserver(vtkCommand::TimerEvent, this->cuehandler);
  int tid = this->iren->CreateRepeatingTimer(100);
  std::cout << "Timer id: " << tid << std::endl;
}

void RenderThread::register_animator(std::shared_ptr<ImageAnimator> animator){
  this->animator = animator;
  this->animator->register_renderer(this->renderer);
  this->cuehandler->RegisterAnimator(animator);
}

void RenderThread::execute(){
  this->renderwindow->Render(); //extra render before modified() seems to fix tiling wm behaviour
  this->renderwindow->Modified();
  this->renderwindow->Render();
  this->iren->Start();
}

#endif
