#ifndef TRAJECTORYSET_HPP
#define TRAJECTORYSET_HPP

#include <random>

#include "typedefs.hpp"
#include "trajectory.hpp"

class TrajectorySet{
  private:
    traj_vec trajs;
    std::default_random_engine rand;

  public:
    TrajectorySet();

    void generate_trajs(size_t);
    void calculate_trajs(size_t);
};

#endif
