#include "NeuralNetwork.h"
#include <cassert>
#include <sstream>

int main(int argc, char *argv[])
{
  NeuralNetwork brain;

  brain.add_layer(15);
  brain.add_layer(10);
  brain.add_layer(10);
  brain.add_layer(1);

  std::vector<double> one_pic(15, 1);
  std::list< std::vector<double> > input;
  input.push_back(one_pic);

  auto ener = brain.forward(input);
  std::vector<double> expected(1, 1500.);

  assert( *(ener.begin()) == expected );
}
