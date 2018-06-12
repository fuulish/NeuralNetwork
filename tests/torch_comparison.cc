#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <NeuralNetwork.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

std::list< std::vector<double> > read_from_txt( std::string filename, int input_len )
{

  int line_count = 0;
  std::string line;
  std::vector<double> one_pic( input_len );
  std::list< std::vector<double> > output;

  std::ifstream data_file;
  data_file.open( filename );

  while( std::getline( data_file, line ) )
  {
    one_pic[line_count++] = std::stod( line );

    if( line_count == input_len )
    {
      output.push_back( one_pic );
      line_count = 0;
    }

  }

  return output;

}

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
  ss_input << DATA_DIR << "torch_reference.txt";

  // TODO: get that magic number from somewhere
  std::list< std::vector<double> > input = read_from_txt( ss_input.str(), 64);
  std::list< std::vector<double> > output = brain.forward( input );
  std::list< std::vector<double> > reference = read_from_txt( ss_reference.str(), 1 );

  assert( output == reference );
}