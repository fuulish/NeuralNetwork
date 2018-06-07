#include <vector>

class Node
{
public:
  Node() : weights{1.}, bias{0.} {}

  void update_weights(const std::vector<double>& input_weights)
  {
    weights = input_weights;
  }

  void update_bias(const std::vector<double>& input_bias)
  {
    bias = input_bias;
  }

  void reset_size(int num_weights)
  {
    std::vector<double> new_weights(num_weights, 1.);
    update_weights(new_weights);

    std::vector<double> new_bias(num_weights, 0.);
    update_bias(new_bias);
  }

  void initialize_weights();

private:
  std::vector<double> weights;
  std::vector<double> bias;
};