#include "trajectorygenerator.hpp"
#include "newanimator.hpp"
#include "cuehandler.hpp"
#include "renderthread.hpp"

int main(int, char *[])
{

  std::shared_ptr<TrajectoryGenerator> trajgen =
    std::make_shared<TrajectoryGenerator>(-1.7,0.8,1.3);

  trajgen->init_histogram(2000, 2000);

  std::shared_ptr<RenderThread> scenerenderer = std::make_shared<RenderThread>();
  std::shared_ptr<ImageAnimator> animator = std::make_shared<ImageAnimator>(2000,2000);
  animator->register_trajectorygenerator(trajgen);
  animator->launch_threads(5);

  scenerenderer->init_renderwindow(2000,2000);
  scenerenderer->init_scene(0);
  scenerenderer->register_animator(animator);
  scenerenderer->execute();
  animator->terminate_threads();
  trajgen->write_raw_data(std::string("out"));
  std::cout <<  "Done" << std::endl;

  return EXIT_SUCCESS;
}
