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

#include "trajectorygenerator.hpp"

class ImageAnimator{
  public:
  ImageAnimator(size_t x, size_t y);

  void register_renderer(vtkSmartPointer<vtkRenderer> ren);
  void render();
  void register_trajectorygenerator(std::shared_ptr<TrajectoryGenerator> traj);
  void launch_threads(size_t nthreads = 1);
  
  protected:
  vtkSmartPointer<vtkImageImport> imgimport;
  vtkSmartPointer<vtkImageActor> imgactor;
  vtkSmartPointer<vtkRenderer> renderer;
  std::shared_ptr<std::vector<unsigned char> > imgdata;
  std::shared_ptr<TrajectoryGenerator> trajgen;
  size_t x_extent, y_extent;
  size_t frame = 0;
  double val = 0;

  void init_imagearray();    
  void init_imageimporter();
  void init_imageactor();
};



#endif
