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

  const std::list<int> num_nodes {15, 10, 10, 1};
  const std::list<int> layer_structure = brain.get_layer_structure();

  assert(num_nodes == layer_structure);
}
