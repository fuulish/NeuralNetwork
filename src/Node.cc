#include <nn/Node.h>
#include <numeric>

void Node::update_weights(const std::vector<double> &input_weights)
{
  weights = input_weights;
}

void Node::update_bias(double input_bias)
{
  bias = input_bias;
}

void Node::reset_size(int num_weights)
{
  std::vector<double> new_weights(num_weights, 1.);
  update_weights(new_weights);
  update_bias(0.);
}

int Node::size() const
{
  return weights.size();
}

double Node::activate(const std::vector<double> &input)
{
  return std::inner_product(input.begin(), input.end(), weights.begin(), 0.) + bias;
}

std::vector<double> Node::gradient()
{
  return weights;
}
