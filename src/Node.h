#include <vector>
#include <numeric>

class Node
{
public:
  Node() : weights{1.}, bias{0.} {}

  void update_weights(const std::vector<double> &input_weights)
  {
    weights = input_weights;
  }

  void update_bias(double input_bias)
  {
    bias = input_bias;
  }

  void reset_size(int num_weights)
  {
    std::vector<double> new_weights(num_weights, 1.);
    update_weights(new_weights);
    update_bias(0.);
  }

  void initialize_weights();

  int size() const
  {
    return weights.size();
  }

  double activate(const std::vector<double> &input)
  {
    return std::inner_product(input.begin(), input.end(), weights.begin(), 0.) + bias;
  }

  std::vector<double> gradient()
  {
    return weights;
  }

private:
  std::vector<double> weights;
  double bias;
};