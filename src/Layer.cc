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
    activation[cnt++] = tanh(node.activate(input));
  }

  return activation;
}