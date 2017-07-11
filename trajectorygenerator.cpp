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
    this->trajs.push_back(std::make_shared<mandel>(re,im)); 
  }
}

void TrajectoryGenerator::calculate_trajs(){
  stats_stale = true;
  size_t len;
  auto it = trajs.begin();
  while(it != trajs.end()){
    len = (*it)->calculate_trajectory(this->max, rmin, rmax, imin, imax);
    if (len == this->max){
      it = trajs.erase(it);
      continue;
    }
    it++;
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
  return(trajs.size());
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

  for(auto traj_it = trajs.begin(); traj_it != trajs.end(); traj_it++){
    size_t tlen = (*traj_it)->z.size();
    if(tlen < this->min){
      for(auto point_it = (*traj_it)->z.begin(); point_it != (*traj_it)->z.end(); point_it++){
        double rp = point_it->real();
        double ip = point_it->imag();
        size_t xi = (rp - rmin)/dx;
        size_t yi = (ip - imin)/dy;
        blue[arr_offset - xi * hist_ybins - yi] += 1;
        yi = hist_ybins - yi;
        blue[arr_offset - xi * hist_ybins - yi] += 1;
      }
      continue;
    }
    if(tlen < this->mid){
      for(auto point_it = (*traj_it)->z.begin(); point_it != (*traj_it)->z.end(); point_it++){
        double rp = point_it->real();
        double ip = point_it->imag();
        size_t xi = (rp - rmin)/dx;
        size_t yi = (ip - imin)/dy;
        green[arr_offset - xi * hist_ybins - yi - 1] += 1;
        yi = hist_ybins - yi;
        green[arr_offset - xi * hist_ybins - yi - 1] += 1;
      }
      continue;
    }
    for(auto point_it = (*traj_it)->z.begin(); point_it != (*traj_it)->z.end(); point_it++){
        double rp = point_it->real();
        double ip = point_it->imag();
        size_t xi = (rp - rmin)/dx;
        size_t yi = (ip - imin)/dy;
        red[arr_offset - xi * hist_ybins - yi - 2] += 1;
        yi = hist_ybins - yi;
        red[arr_offset - xi * hist_ybins - yi - 2] += 1;
    }
  }
  trajs.clear();
  double rmult = 255./std::sqrt(*std::max_element(red.begin(), red.end()));
  double gmult = 255./std::sqrt(*std::max_element(green.begin(), green.end()));
  double bmult = 255./std::sqrt(*std::max_element(blue.begin(), blue.end()));
  //double rmult = 255.0/(double)(*std::max_element(red.begin(), red.end()));
  //double gmult = 255.0/(double)(*std::max_element(green.begin(), green.end()));
  //double bmult = 255.0/(double)(*std::max_element(blue.begin(), blue.end()));

  for(size_t i = 0; i <= arr_offset; i++){
    //histogram[3*i] = (red[i]) * rmult;
    //histogram[3*i +1] = (green[i]) * gmult;
    //histogram[3*i +2] = (blue[i]) * bmult;
    histogram[3*i] = std::sqrt(red[i]) * rmult;
    histogram[3*i +1] = std::sqrt(green[i]) * gmult;
    histogram[3*i +2] = std::sqrt(blue[i]) * bmult;
  }    
}

std::vector<unsigned char> TrajectoryGenerator::get_histogram(){
  return(histogram);
}
