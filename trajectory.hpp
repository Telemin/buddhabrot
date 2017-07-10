#ifndef TRAJECTORY_HPP
#define TRAJECTORY_HPP

#include <complex>
#include <iostream>

template <class T>
class Trajectory {
  friend class TrajectoryGenerator;
  public:

  Trajectory(std::complex<T> z, std::complex<T> c):z0(z), c(c){}

  virtual size_t calculate_trajectory(size_t max_steps, double rmin, double rmax,
                                      double imin, double imax){
    step = max_steps;

    z.resize(max_steps);
    z[0] = z0;
        
    for(auto it = (this->z.begin() + 1); it != this->z.end(); it++){
      std::complex<T> tmpz = std::pow(*(it-1),2) + c;
      if((tmpz.real() <= rmin) || (tmpz.real() >= rmax) ||
         (tmpz.imag() <= imin) || (tmpz.imag() > imax) ){
        step = it - z.begin();
        break;
      }
      *it = tmpz;
    }
    this->z.resize(step);
    return(step);
  }

  size_t length(){ 
    return(step);
  }

  protected:
    std::complex<T> z0;
    std::complex<T> c;
    std::vector<std::complex<T> > z;
    size_t step;
    
};

template <class T>
class MandelTrajectory : public Trajectory<T>{
  public:
  MandelTrajectory(std::complex<T> z):Trajectory<T>(z, z){}

  MandelTrajectory(T x0, T y0):Trajectory<T>(std::complex<T>(x0, y0), std::complex<T>(x0, y0)){}
};

template <class T>
class JuliaTrajectory : public Trajectory<T>{
  public:
  JuliaTrajectory(std::complex<T> z, std::complex<T> c):Trajectory<T>(z,c){}

  JuliaTrajectory(T x0, T y0, T cx, T cy):Trajectory<T>(std::complex<T>(x0, y0),
                                                        std::complex<T>(cx, cy)){}
};

#endif
