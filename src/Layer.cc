#include "Layer.h"
#include "cmath"

void Layer::update_nodes(int num_following)
{
  for (auto &node : nodes)
  {
    node.reset_size(num_following);
  }
}

const std::vector<double> Layer::compute_activation(const std::vector<double> &input)
{

  std::vector<double> activation(size(), 0.);

  int cnt = 0;
  for (auto node : nodes)
  {
    activation[cnt++] = node.activate(input);
  }

  // TODO: find better way to treat non-linear activation, reference ok?
  if( nonlinear )
  {
    for( auto& p : activation )
    {
      p = nonlinear(p);
    }
    /* include non-linearity */
  }

  return activation;
}