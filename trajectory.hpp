#ifndef TRAJECTORY_HPP
#define TRAJECTORY_HPP

#include <complex>

#include "typedefs.hpp"

class Trajectory {

  private:
    complex_num z0;
    complex_num c;
    complex_vec z;


  public:
    Trajectory(num, num);
    Trajectory(complex_num);
    Trajectory(num, num, num, num);
    Trajectory(complex_num, complex_num);

    size_t calculate_trajectory(size_t);
    
};

#endif
