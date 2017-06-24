#include "trajectoryset.hpp"
#include <iostream>

TrajectorySet::TrajectorySet(){
  std::random_device r;
  rand.seed(r());
}

void TrajectorySet::generate_trajs(size_t n_trajs){
  num re;
  num im;
  num rmult = rand.max() / 2.0;

  for(size_t i=0; i<n_trajs; i++){
    re = rand() / rmult - 1.0;
    im = rand() / rmult - 1.0;
    this->trajs.push_back(std::make_shared<Trajectory>(re,im)); 
  }
}

void TrajectorySet::calculate_trajs(size_t steps){
  size_t len;
  for(auto traj_it = trajs.begin(); traj_it != trajs.end(); traj_it++){
    len = (*traj_it)->calculate_trajectory(steps);
    for(auto res_it = results_map.begin(); res_it != results_map.end(); res_it++)
  }
}
