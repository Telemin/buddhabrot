#include "trajectorygenerator.hpp"
#include <iostream>

TrajectoryGenerator::TrajectoryGenerator(double rmin, double rmax, double imin, double imax)
                            :rmin(rmin), rmax(rmax), imin(imin), imax(imax){
  std::random_device r;
  rand.seed(r());
}

void TrajectoryGenerator::generate_trajs(size_t n_trajs){
  num re;
  num im;
  num rmult = rand.max() / (rmax - rmin);
  num imult = rand.max() / (imax - imin);

  for(size_t i=0; i<n_trajs; i++){
    re = rand() / rmult + rmin;
    im = rand() / imult + imin;
    this->trajs.push_back(std::make_shared<mandel>(re,im)); 
  }
}

void TrajectoryGenerator::calculate_trajs(size_t steps){
  stats_stale = true;
  size_t len;
  auto it = trajs.begin();
  while(it != trajs.end()){
    len = (*it)->calculate_trajectory(steps, rmin, rmax, imin, imax);
    if (len == steps){
      it = trajs.erase(it);
      continue;
    }
    /*for(auto res_it = results_map.begin(); res_it != results_map.end(); res_it++){
    //add to results maps as needed
    }*/
    it++;
  }
}

size_t TrajectoryGenerator::num_trajs(){
  return(trajs.size());
}

void TrajectoryGenerator::calc_stats(){
  double count(0);
  double countsq(0); //should be okay(!)
  if(trajs.size() == 0){
    return;
  }
  for (auto it=trajs.begin(); it != trajs.end(); it++){
    count += (*it)->length();
    countsq += (*it)->length() * (*it)->length(); 
  }
  mean = count / trajs.size();
  double meansq = countsq / trajs.size();
  stddev = std::sqrt( meansq - std::pow(mean,2.0));
  stats_stale = false;
}

double TrajectoryGenerator::stddev_length(){
  if (stats_stale){
    calc_stats();
  }
  return(stddev);
}

double TrajectoryGenerator::mean_length(){
  if (stats_stale){
    calc_stats();
  }
  return(mean);
}

void TrajectoryGenerator::init_histogram(size_t x, size_t y){
  hist_xbins = x;
  hist_ybins = y;
  histogram.resize(x*y, 0);
  std::cout << "Init size: " << histogram.size() << std::endl;
};


void TrajectoryGenerator::deposit_to_histogram(){
  double dx = (rmax - rmin) / hist_xbins;
  double dy = (imax - imin) / hist_ybins;
  size_t arr_offset = hist_xbins * hist_ybins - 1;

  for(auto traj_it = trajs.begin(); traj_it != trajs.end(); traj_it++){
    for(auto point_it = (*traj_it)->z.begin(); point_it != (*traj_it)->z.end(); point_it++){
      double rp = point_it->real();
      double ip = point_it->imag();
      size_t xi = (rp - rmin)/dx;
      size_t yi = (ip - imin)/dy;
      histogram[arr_offset - xi * hist_ybins - yi] += 1;
    }
  }
  trajs.clear();
}

std::vector<double> TrajectoryGenerator::get_histogram(){
  return(histogram);
}
