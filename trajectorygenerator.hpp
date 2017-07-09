#ifndef TRAJECTORYSET_HPP
#define TRAJECTORYSET_HPP

#include <random>
#include <algorithm>

#include "typedefs.hpp"
#include "trajectory.hpp"

class TrajectoryGenerator{
  private:
    traj_container trajs;
    std::default_random_engine rand;
    std::vector<double> histogram;
    double hist_xbins, hist_ybins;
    double mean, stddev;
    double rmin, rmax, imin, imax;
    bool stats_stale = true;

  public:
    TrajectoryGenerator(double rmin, double rmax, double imin, double imax);

    void generate_trajs(size_t);
    void calculate_trajs(size_t);
    size_t num_trajs();

    double mean_length();
    double stddev_length();
    void calc_stats();
    void init_histogram(size_t x, size_t y);
    void deposit_to_histogram();
    std::vector<double> get_histogram();

};

#endif
