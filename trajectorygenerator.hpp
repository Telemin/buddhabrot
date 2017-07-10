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
    std::vector<unsigned char> histogram;
    std::vector<size_t> red;
    std::vector<size_t> green;
    std::vector<size_t> blue;
    double hist_xbins, hist_ybins;
    double rmin, rmax, imin, imax;
    bool stats_stale = true;
    size_t min = 20;
    size_t mid = 200;
    size_t max = 2000;

  public:
    TrajectoryGenerator(double rmin, double rmax, double imax);

    static bool in_mandelbrot_center(double re, double imag);

    void generate_trajs(size_t n_trajs);
    void calculate_trajs();
    size_t num_trajs();

    void init_histogram(size_t x, size_t y);
    void deposit_to_histogram();
    std::vector<unsigned char> get_histogram();

};

#endif
