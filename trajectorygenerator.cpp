#include "trajectorygenerator.hpp"
#include <iostream>

TrajectoryGenerator::TrajectoryGenerator(double rmin, double rmax, double imax)
                            :rmin(rmin), rmax(rmax), imin(-imax), imax(imax){
  std::random_device r;
  rand.seed(r());
}

void TrajectoryGenerator::generate_trajs(size_t n_trajs){
  num re;
  num im;
  num rmult = rand.max() / (rmax - rmin);
  num imult = rand.max() / (imax - imin);

  for(size_t i=0; i<n_trajs; i++){
    do{
      re = rand() / rmult + rmin;
      im = rand() / imult + imin;
    } while(TrajectoryGenerator::in_mandelbrot_center(re, im));

    mandel* traj = new mandel(re,im);
    size_t len = traj->calculate_trajectory(this->max, rmin, rmax, imin, imax);
    if (len < this->max){
    	this->trajs.push(traj); 
    } else {
      delete traj;
    }
  }
}

bool TrajectoryGenerator::in_mandelbrot_center(double re, double im){
  // See wikipedia article
  num im2 = std::pow(im, 2.0);
  num p = std::pow(re - 0.25, 2.0) + im2;
  num card = 4. * p * ( p + re - 0.25);
  num bulb = 16 * (std::pow(re + 1., 2.) + im2 );
  if(card < im2 || bulb < 1){
    return(true);
  }
  return(false);
}

size_t TrajectoryGenerator::num_trajs(){
  return(trajs.unsafe_size());
}

void TrajectoryGenerator::init_histogram(size_t x, size_t y){
  hist_xbins = x;
  hist_ybins = y;
  histogram.resize(x*y*3, 0);
  red.resize(x*y, 0);
  green.resize(x*y, 0);
  blue.resize(x*y, 0);
};


void TrajectoryGenerator::deposit_to_histogram(){
  double dx = (rmax - rmin) / hist_xbins;
  double dy = (imax - imin) / hist_ybins;
  size_t arr_offset = hist_xbins * hist_ybins - 1;

  size_t iterations = trajs.unsafe_size();
  std::cout << "Queue Size: " << iterations << std::endl;
  for(size_t i = 0; i < iterations; i++){
    mandel* traj_it;
    if(!trajs.try_pop(traj_it)){
	std::cout << "Queue shorter than expected, this is an error!" << std::endl;
     	break;
    }	
    size_t tlen = traj_it->z.size();
    if(tlen < this->thres){
    } else if(tlen < this->min){
      for(auto point_it = traj_it->z.begin(); point_it != traj_it->z.end(); point_it++){
        double rp = point_it->real();
        double ip = point_it->imag();
        size_t xi = (rp - rmin)/dx;
        size_t yi = (ip - imin)/dy;
        blue[arr_offset - xi * hist_ybins - yi] += 1;
        yi = hist_ybins - yi - 1;
        blue[arr_offset - xi * hist_ybins - yi] += 1;
      }
    } else if(tlen < this->mid){
      for(auto point_it = traj_it->z.begin(); point_it != traj_it->z.end(); point_it++){
        double rp = point_it->real();
        double ip = point_it->imag();
        size_t xi = (rp - rmin)/dx;
        size_t yi = (ip - imin)/dy;
        green[arr_offset - xi * hist_ybins - yi] += 1;
        yi = hist_ybins - yi - 1;
        green[arr_offset - xi * hist_ybins - yi] += 1;
      }
    } else {
      for(auto point_it = traj_it->z.begin(); point_it != traj_it->z.end(); point_it++){
        double rp = point_it->real();
        double ip = point_it->imag();
        size_t xi = (rp - rmin)/dx;
        size_t yi = (ip - imin)/dy;
        red[arr_offset - xi * hist_ybins - yi] += 1;
        yi = hist_ybins - yi - 1;
        red[arr_offset - xi * hist_ybins - yi] += 1;
      }
    }
    delete traj_it;
  }
}

std::vector<unsigned char> TrajectoryGenerator::get_histogram(double gamma, double thres){
  double igamma = 1./gamma;
  double rmax = *std::max_element(red.begin(), red.end());
  double gmax = *std::max_element(green.begin(), green.end());
  double bmax = *std::max_element(blue.begin(), blue.end());

  std::fill(histogram.begin(), histogram.end(), 0);
  size_t arr_offset = hist_xbins * hist_ybins;
  for(size_t i = 0; i < arr_offset; i++){
    double rr = red[i]/rmax;
    histogram[3*i] = 255.*std::pow(rr, igamma);
    double gr = green[i]/gmax;
    histogram[3*i +1] = 255.*std::pow(gr, igamma);
    double br = blue[i]/bmax;
    histogram[3*i +2] = 255.*std::pow(br, igamma);
  }    
  return(histogram);
}

void TrajectoryGenerator::runthread(){
  while(!this->stop){
    if(this->trajs.unsafe_size() < 1000){	  
	generate_trajs(100);
    }
  }
} 

void TrajectoryGenerator::launch_threads(size_t nthreads){
  this->stop = false;
  for(size_t i = 0; i < nthreads; i++){
    threads.push_back(std::thread(&TrajectoryGenerator::runthread, this));
  }
}

void TrajectoryGenerator::stop_threads(){
  this->stop = true;
  for(auto& it : this->threads){
    it.join();
  }
}
