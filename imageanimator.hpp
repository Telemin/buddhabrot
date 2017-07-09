#ifndef IMAGEANIMATOR_HPP
#define IMAGEANIMATOR_HPP

#include <vector>
#include <algorithm>
#include <memory>
#include <thread>

#include <vtkAnimationCue.h>
#include <vtkImageImport.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>

#include "animationhandler.hpp"
#include "trajectorygenerator.hpp"

class ImageAnimator: public AnimationHandler{
  public:
  ImageAnimator(size_t x, size_t y);

  void Start(vtkAnimationCue::AnimationCueInfo *info, vtkRenderer *ren);
  void Tick(vtkAnimationCue::AnimationCueInfo *info, vtkRenderer *ren);
  void Stop(vtkAnimationCue::AnimationCueInfo *info, vtkRenderer *ren);
  void register_trajectorygenerator(std::shared_ptr<TrajectoryGenerator> traj);
  
  protected:
  vtkSmartPointer<vtkImageImport> imgimport;
  vtkSmartPointer<vtkImageActor> imgactor;
  std::shared_ptr<std::vector<double> > imgdata;
  std::shared_ptr<TrajectoryGenerator> trajgen;
  size_t x_extent, y_extent;
  double val = 0;

  void init_imagearray();    
  void init_imageimporter();
  void init_imageactor();
};



#endif
