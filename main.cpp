#include "main.hpp"

#include <vtkVersion.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkImageImport.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkXMLImageDataWriter.h>

int main(int argc, char *argv[]){
  size_t num_trajs = 5000000;
  size_t num_steps = 100;
  size_t hist_x = 1000;
  size_t hist_y = 1000;
  size_t num_loops = 10;

  TrajectoryGenerator ts1(-1.8,0.6,-1.3,1.3);
  ts1.init_histogram(hist_x, hist_y);

  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> elapsed_seconds;
  start = std::chrono::system_clock::now();

  for(size_t i = 0; i < num_loops; i++){
    ts1.generate_trajs(num_trajs);
    ts1.calculate_trajs(num_steps);
    ts1.deposit_to_histogram();
    elapsed_seconds = std::chrono::system_clock::now() - start;
    std::cout << "Loop " << i << ": " << elapsed_seconds.count() << " s.\n";
  }

  elapsed_seconds = std::chrono::system_clock::now() - start;

  std::cout << "Calculated " << num_trajs*num_loops << " trajectories in " << elapsed_seconds.count() 
            << " s.\n";
  
  std::vector<double> histo = ts1.get_histogram();

  std::string fname = "hist.txt";
  std::fstream fs(fname, std::fstream::out);
  for(size_t y = 0; y < hist_y; y++){
    for(size_t x = 0; x < hist_x; x++){
      fs << histo[y * hist_x + x] <<  " ";
    }
    fs << std::endl;
  }

  return(0);
}
