#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include <complex>
#include <vector>
#include <memory>

//Forward Decls
class Trajectory;

typedef double num;
typedef std::complex<num> complex_num;
typedef std::vector<complex_num> complex_vec;

typedef std::shared_ptr<Trajectory> traj_ptr;
typedef std::vector<traj_ptr> traj_vec;

#endif
