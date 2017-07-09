#include "imageanimator.hpp"

ImageAnimator::ImageAnimator(size_t x, size_t y):x_extent(x), y_extent(y){
  init_imagearray();
  init_imageimporter();
  init_imageactor();
  std::cout << x_extent << "x" << y_extent << std::endl;
  std::cout << this->imgactor << std::endl;
}

void ImageAnimator::Start(vtkAnimationCue::AnimationCueInfo *info, vtkRenderer *ren){
  ren->AddActor(this->imgactor);
  ren->ResetCamera();
  this->imgimport->Modified();
  this->imgimport->Update();
}

void ImageAnimator::Tick(vtkAnimationCue::AnimationCueInfo *info, vtkRenderer *ren){
  this->trajgen->generate_trajs(10000);
  this->trajgen->calculate_trajs(200);
  this->trajgen->deposit_to_histogram();
  std::vector<double> histo = this->trajgen->get_histogram();
  std::copy(histo.begin(), histo.end(), this->imgdata->begin());
  this->imgimport->Modified();
  this->imgimport->Update();
  ren->GetRenderWindow()->Render();
}

void ImageAnimator::Stop(vtkAnimationCue::AnimationCueInfo *info, vtkRenderer *ren){
  ren->RemoveActor(this->imgactor);
}

void ImageAnimator::init_imagearray(){
  this->imgdata = std::make_shared<std::vector<double> >();
  this->imgdata->resize(x_extent * y_extent, 0);
}
    
void ImageAnimator::init_imageimporter(){
  this->imgimport = vtkSmartPointer<vtkImageImport>::New();
  this->imgimport->SetDataSpacing(1, 1, 1);
  this->imgimport->SetDataOrigin(0, 0, 0);
  this->imgimport->SetWholeExtent(0, x_extent-1, 0, y_extent-1, 0, 0);
  this->imgimport->SetDataExtentToWholeExtent();
  this->imgimport->SetDataScalarTypeToDouble();
  this->imgimport->SetNumberOfScalarComponents(1);
  this->imgimport->SetImportVoidPointer(this->imgdata->data());
  this->imgimport->Update();
}

void ImageAnimator::init_imageactor(){
  this->imgactor = vtkSmartPointer<vtkImageActor>::New();
  this->imgactor->SetInputData(this->imgimport->GetOutput());
}

void ImageAnimator::register_trajectorygenerator(std::shared_ptr<TrajectoryGenerator> traj){
  this->trajgen = traj;
}
