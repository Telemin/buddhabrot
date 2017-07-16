#ifndef TRAJECTORYSET_HPP
#define TRAJECTORYSET_HPP

#include <random>
#include <algorithm>
#include <thread>

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
    bool stop;
    size_t thres = 10;
    size_t min = 200;
    size_t mid = 2000;
    size_t max = 20000;
    std::vector<std::thread> threads;

  public:
    TrajectoryGenerator(double rmin, double rmax, double imax);

    static bool in_mandelbrot_center(double re, double imag);

    void launch_threads(size_t nthreads);
    void stop_threads();
    void runthread();
    void generate_trajs(size_t n_trajs);
    void calculate_trajs();
    size_t num_trajs();

    void init_histogram(size_t x, size_t y);
    void deposit_to_histogram();
    std::vector<unsigned char> get_histogram(double gamma = 2.0, double thres = 0.);

};

#endif
