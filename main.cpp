#include "trajectorygenerator.hpp"
#include "newanimator.hpp"
#include "cuehandler.hpp"
#include "renderthread.hpp"

int main(int, char *[])
{

  std::shared_ptr<TrajectoryGenerator> trajgen =
    std::make_shared<TrajectoryGenerator>(-1.7,0.8,1.3);

  trajgen->init_histogram(1500, 1500);

  std::shared_ptr<RenderThread> scenerenderer = std::make_shared<RenderThread>();
  std::shared_ptr<ImageAnimator> animator = std::make_shared<ImageAnimator>(1500,1500);
  animator->register_trajectorygenerator(trajgen);

  scenerenderer->init_renderwindow(1500,1500);
  scenerenderer->init_scene(0);
  scenerenderer->register_animator(animator);
  scenerenderer->execute();

  return EXIT_SUCCESS;
}
