#include "NeuralNetwork.h"
#include <cassert>
#include <sstream>

int main(int argc, char *argv[])
{
  NeuralNetwork brain;

  std::stringstream ss;
  ss << DATA_DIR << "network.txt";

  std::string input_file = ss.str();

  brain.from_file(input_file);

  std::vector<double> one_pic(15, 1);

  auto ener = brain.forward(one_pic);
  std::vector<double> expected(1, 9.999999958776927);

  std::cout << ener[0] << " " << expected[0] << std::endl;

  assert( ener[0] == expected[0] );

  std::vector<double> gradient = brain.backward();

  std::cout << gradient.size() << std::endl;

  assert( fabsf(3.0865e-19 - gradient[0]) < 1.e24 );

  for (auto it = gradient.cbegin(); it != gradient.cend(); ++it)
  {
    std::cout << *it << std::endl;
  }
}
