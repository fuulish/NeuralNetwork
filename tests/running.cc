#include <iostream>
#include <NeuralNetwork/NeuralNetwork.h>

int main(int argc, char *argv[])
{
  NeuralNetwork brain;

  brain.add_layer(10);
  brain.add_layer(10);

  // TODO: change this to take a list of vectors as input
  std::vector<double> one_pic(10, 1);
  std::list< std::vector<double> > input;

  input.push_back(one_pic);

  brain.print();

  brain.forward(input);
}
