#include <nn/NeuralNetwork.h>
#include <cassert>
#include <sstream>

int main(int argc, char *argv[])
{
  NeuralNetwork brain;
  brain.add_layer(1);

  std::vector<double> one_pic(1, 0.);
  std::list< std::vector<double> > input;
  input.push_back(one_pic);
  one_pic[0] = -1.;
  input.push_back(one_pic);
  one_pic[0] = 1.;
  input.push_back(one_pic);

  std::list< std::vector<double> > output = brain.forward(input);
  std::list< std::vector<double> > expected;

  for( auto it : input )
    expected.push_back(it);

  assert ( output == expected );

  brain.add_layer(1, "tanh");
  brain.add_layer(1);

  output = brain.forward(input);

  auto it = output.begin();
}
