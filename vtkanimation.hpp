#ifndef VTKANIMATION_HPP
#define VTKANIMATION_HPP

#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>

#include <vtkImageImport.h>
#include <vtkImageActor.h>
#include <vtkSmartPointer.h>
#include <vtkAnimationCue.h>
#include <vtkCommand.h>
#include <vtkRenderer.h>
#include <vtkCommand.h>
#include <vtkAnimationScene.h>
#include <vtkRenderWindow.h>

class ImageAnimator{
  public:
  ImageAnimator(size_t x, size_t y):x_extent(x), y_extent(y){
    init_imagearray();
    init_imageimporter();
    init_imageactor();
    std::cout << x_extent << "x" << y_extent << std::endl;
    std::cout << this->imgactor << std::endl;
  }

  void Start(vtkAnimationCue::AnimationCueInfo *info, vtkRenderer *ren){
    ren->AddActor(this->imgactor);
    ren->ResetCamera();
    cout << "Start" << endl;
  }

  void Tick(vtkAnimationCue::AnimationCueInfo *info, vtkRenderer *ren){
    val -= 20;
    std::this_thread::sleep_for(std::chrono::milliseconds(40));
    std::fill(this->imgdata->begin(), this->imgdata->end(), val);
    this->imgimport->Modified();
    this->imgimport->Update();
    cout << "Tick" << endl;
    ren->GetRenderWindow()->Render();
  }

  void Stop(vtkAnimationCue::AnimationCueInfo *info, vtkRenderer *ren){
    ren->RemoveActor(this->imgactor);
    cout << "Stop" << endl;
  }
  
  protected:
  vtkSmartPointer<vtkImageImport> imgimport;
  vtkSmartPointer<vtkImageActor> imgactor;
  std::shared_ptr<std::vector<unsigned char> > imgdata;
  size_t x_extent, y_extent;
  double val = 0;

  void init_imagearray(){
    this->imgdata = std::make_shared<std::vector<unsigned char> >();
    this->imgdata->resize(x_extent * y_extent, 255);
  }
    
  void init_imageimporter(){
    this->imgimport = vtkSmartPointer<vtkImageImport>::New();
    this->imgimport->SetDataSpacing(1, 1, 1);
    this->imgimport->SetDataOrigin(0, 0, 0);
    this->imgimport->SetWholeExtent(0, x_extent-1, 0, y_extent-1, 0, 0);
    this->imgimport->SetDataExtentToWholeExtent();
    this->imgimport->SetDataScalarTypeToUnsignedChar();
    this->imgimport->SetNumberOfScalarComponents(1);
    this->imgimport->SetImportVoidPointer(this->imgdata->data());
    this->imgimport->Update();
  }

  void init_imageactor(){
    this->imgactor = vtkSmartPointer<vtkImageActor>::New();
    this->imgactor->SetInputData(this->imgimport->GetOutput());
  }


};

class vtkAnimationCueObserver : public vtkCommand {
  public:
  static vtkAnimationCueObserver *New()
  {
    return new vtkAnimationCueObserver;
  }

  void Execute(vtkObject *vtkNotUsed(caller), unsigned long event, void *calldata){
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

  void RegisterAnimator(AnimationHandler* animatorptr){
    this->animator = animatorptr;
  }

  void RegisterRenderer(vtkRenderer* renderptr){
    this->renderer = renderptr;
  }

  protected:
  AnimationHandler *animator;
  vtkRenderer *renderer;

};


#endif
