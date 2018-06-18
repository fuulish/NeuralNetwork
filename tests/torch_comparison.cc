#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <NeuralNetwork/NeuralNetwork.h>
#include <NeuralNetwork/io.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

int main( int argc, char *argv[] )
{
  std::stringstream ss;
  ss << DATA_DIR << "torch_network.txt";

  NeuralNetwork brain;

  std::string input_file = ss.str();
  brain.from_file(input_file);

  std::stringstream ss_input;
  ss_input << DATA_DIR << "torch_input.txt";

  std::stringstream ss_reference;
  ss_reference << DATA_DIR << "torch_reference.txt";

  // TODO: get that magic number from somewhere
  std::list< std::vector<double> > input = list_of_vectors_from_file( ss_input.str(), 64);
  std::list< std::vector<double> > output = brain.forward( input );
  std::list< std::vector<double> > reference = list_of_vectors_from_file( ss_reference.str(), 1 );

  std::cout << input.size() << reference.size() << std::endl;

  auto ref_iter = reference.begin();

  int num_fails = 0;

  for( auto out_iter = output.begin(); out_iter != output.end(); ++out_iter )
  {
    if( fabsf( (*out_iter)[0] - (*ref_iter)[0] ) > 1.e-6 )
    {
      std::cout << (*out_iter)[0] << " " << (*ref_iter)[0] << std::endl;
      ++num_fails;
    }
    std::advance(ref_iter, 1);
  }

  if( num_fails ) {
    std::cout << num_fails << std::endl;
    return 1;
  }
  else {
    return 0;
  }
}
