#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include <complex>
#include <vector>
#include <list>
#include <memory>

#include "tbb/concurrent_queue.h"

#include "trajectory.hpp"

//Forward Decls

typedef double num;
typedef std::complex<num> complex_num;
typedef std::vector<complex_num> complex_vec;

typedef Trajectory<num> traj;
typedef MandelTrajectory<num> mandel;
typedef JuliaTrajectory<num> julia;

typedef std::shared_ptr<traj> traj_ptr;
typedef tbb::concurrent_queue<mandel*> traj_container;

#endif
