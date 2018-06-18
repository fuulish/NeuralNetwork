#include <nn/io.h>
#include <fstream>

std::list< std::vector<double> > list_of_vectors_from_file( std::string filename, int input_len )
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
