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
  std::list< std::vector<double> > input;
  input.push_back(one_pic);

  auto ener = brain.forward(input);
  std::vector<double> expected(1, 0.);

  assert( *(ener.begin()) == expected );
}
