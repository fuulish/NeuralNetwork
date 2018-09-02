#include <nn/NeuralNetwork.h>
#include <nn/io.h>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <ctime>

int main(int argc, char *argv[]) {

  NeuralNetwork brain;

  // std::cout << "initializing network" << std::endl;
  brain.from_file( argv[1] );

  std::string filename( argv[2] );

  // std::cout << "reading external data" << std::endl;
  std::list< std::vector<double> > input = list_of_vectors_from_file( filename, brain.get_input_size() );

  // std::cout << "computing forward pass" << std::endl;

  std::list< std::vector<double> > output = brain.forward( input );

  for( auto& it : output ) {
    std::cout << it[0] << std::endl;
  }

}
