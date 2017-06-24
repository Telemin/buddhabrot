#include "trajectory.hpp"
#include <iostream>

Trajectory::Trajectory(complex_num z0): 
  z0(z0), c(z0){
}

Trajectory::Trajectory(num x0, num y0): 
  z0(complex_num(x0, y0)), c(complex_num(x0, y0)){
}

Trajectory::Trajectory(complex_num z0, complex_num c): 
  z0(z0), c(c){
}

Trajectory::Trajectory(num x0, num y0, num cx, num cy):
  z0(complex_num(x0, y0)), c(complex_num(cx, cy)){
}

size_t Trajectory::calculate_trajectory(size_t max_steps){
  size_t step(0);
  complex_num c = this->c;
  complex_num zn = this->z0;

  this->z.reserve(max_steps);
  this->z.push_back(z0);
  
  while(step < max_steps){
    zn = std::pow(zn,2) + c;
    if((std::abs(zn.real()) > 2) || (std::abs(zn.imag()) > 2)){
      break;
    }
    step++;
  }

  this->z.shrink_to_fit();

  return(step);
}



    
     
