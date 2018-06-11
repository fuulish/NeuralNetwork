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

  const std::list<int> num_nodes { 10, 10, 1 };
  const std::list<int> layer_structure = brain.get_layer_structure();

  assert(num_nodes == layer_structure);

  std::vector<double> one_pic(15, 1);
  std::list< std::vector<double> > input;
  input.push_back(one_pic);

  brain.forward(input);
  //calculate output value with something else and compare here
}
