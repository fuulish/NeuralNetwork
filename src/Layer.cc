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

std::vector<double> Layer::backprop_gradient( const std::vector<double>& gradient ) // gradient is the gradient on each node from the previous layer
{

  // size of new gradient is the size of the nodes' weight array
  std::vector<double> backprop ((*nodes.cbegin()).size(), 0.);

  // 1. get gradient from each node on previous layer
  // not always do we need the previous' layer's activations, but sometimes? <- node-specific

  for( auto it: nodes ) {
    it->gradient();
    // backprop 
  }

  // 2. get gradient of activation function <- layer-specific // multiply with gradient from 1.

  return backprop;
}