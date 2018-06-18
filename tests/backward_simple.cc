
#include <nn/NeuralNetwork.h>
#include <cassert>
#include <sstream>

int main(int argc, char *argv[])
{
  NeuralNetwork brain;

  std::stringstream ss;
  ss << DATA_DIR << "network.txt";

  std::string input_file = ss.str();

  brain.add_layer(2);
  brain.add_layer(2, "tanh");
  brain.add_layer(1);

  std::vector<double> one_pic(2, 1);
  auto ener = brain.forward(one_pic);

  std::cout << ener[0] << " " << 0.7616 << std::endl;

  std::vector<double> gradient = brain.backward();

  std::cout << gradient.size() << std::endl;

  for (auto it = gradient.cbegin(); it != gradient.cend(); ++it)
  {
    std::cout << "Final: " << *it << std::endl;
  }

  assert( fabsf(gradient[0] - 0.14130165) < 1.e-5 );
  assert( fabsf(gradient[0] - 0.14130165) < 1.e-5 );
}
