#ifndef NODE_H
#define NODE_H

#include <vector>

class Node
{
public:
  Node() : weights{1.}, bias{0.} {}

  void update_weights(const std::vector<double> &input_weights);
  void update_bias(double input_bias);
  void reset_size(int num_weights);
  void initialize_weights();
  int size() const;
  double activate(const std::vector<double> &input);
  std::vector<double> gradient();

private:
  std::vector<double> weights;
  double bias;
};

#endif
