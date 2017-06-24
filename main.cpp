#include "main.hpp"
#include <iostream>

int main(int argc, char *argv[]){
  TrajectorySet ts1;
  ts1.generate_trajs(100000);
  ts1.calculate_trajs(1000);
  return(0);
}
