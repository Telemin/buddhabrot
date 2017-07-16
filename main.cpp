#include "trajectorygenerator.hpp"
#include "newanimator.hpp"
#include "cuehandler.hpp"
#include "renderthread.hpp"

int main(int, char *[])
{

  std::shared_ptr<TrajectoryGenerator> trajgen =
    std::make_shared<TrajectoryGenerator>(-1.7,0.8,1.3);

  trajgen->init_histogram(1200, 1200);

  std::shared_ptr<RenderThread> scenerenderer = std::make_shared<RenderThread>();
  std::shared_ptr<ImageAnimator> animator = std::make_shared<ImageAnimator>(1200,1200);
  animator->register_trajectorygenerator(trajgen);
  animator->launch_threads(5);

  scenerenderer->init_renderwindow(1200,1200);
  scenerenderer->init_scene(0);
  scenerenderer->register_animator(animator);
  scenerenderer->execute();
  animator->terminate_threads();
  std::cout <<  "Done" << std::endl;

  return EXIT_SUCCESS;
}
