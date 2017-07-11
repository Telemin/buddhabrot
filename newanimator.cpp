#include "newanimator.hpp"
#include <algorithm>

ImageAnimator::ImageAnimator(size_t x, size_t y):x_extent(x), y_extent(y){
  init_imagearray();
  init_imageimporter();
  init_imageactor();
  std::cout << x_extent << "x" << y_extent << std::endl;
  std::cout << this->imgactor << std::endl;
}

void ImageAnimator::register_renderer(vtkSmartPointer<vtkRenderer> ren){
  this->renderer = ren;
  this->renderer->AddActor(this->imgactor);
};

void ImageAnimator::render(){
  std::cout << "Frame " << ++frame << std::endl;
  this->trajgen->generate_trajs(5000);
  this->trajgen->calculate_trajs();
  this->trajgen->deposit_to_histogram();
  std::vector<unsigned char> histo = this->trajgen->get_histogram(2, 0);
  std::copy(histo.begin(), histo.end(), this->imgdata->begin());
  this->imgimport->Modified();
  this->imgimport->Update();
  this->renderer->GetRenderWindow()->Render();
}

void ImageAnimator::init_imagearray(){
  this->imgdata = std::make_shared<std::vector<unsigned char> >();
  this->imgdata->resize(x_extent * y_extent * 3, 0);
}
    
void ImageAnimator::init_imageimporter(){
  this->imgimport = vtkSmartPointer<vtkImageImport>::New();
  this->imgimport->SetDataSpacing(1, 1, 1);
  this->imgimport->SetDataOrigin(0, 0, 0);
  this->imgimport->SetWholeExtent(0, x_extent-1, 0, y_extent-1, 0, 0);
  this->imgimport->SetDataExtentToWholeExtent();
  this->imgimport->SetDataScalarTypeToUnsignedChar();
  this->imgimport->SetNumberOfScalarComponents(3);
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
