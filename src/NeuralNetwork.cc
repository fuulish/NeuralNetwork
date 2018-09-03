#include <nn/NeuralNetwork.h>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

void NeuralNetwork::add_layer(int num_nodes)
{

  // invalidate cached weights

  // 1st layer needs to get size of input layer

  if( (previous_size == 0) && (layers.size() == 0))
  {
    std::vector<double> mean( num_nodes, 0. );
    std::vector<double> stdev( num_nodes, 1. );

    this->mean = mean;
    this->stdev = stdev;

    previous_size = num_nodes;
  } else
  // add layer with correct number of nodes
  {
    Layer layer(num_nodes);
    layer.update_nodes(previous_size);
    previous_size = num_nodes;
    layers.push_back(layer);
  }

  update_connectivity();
}

void NeuralNetwork::add_layer(int num_nodes, const std::string& nonlinearity)
{
  add_layer(num_nodes);

  auto last_layer = layers.rbegin();
  last_layer->add_nonlinearity(nonlinearity);
}

void NeuralNetwork::add_layer(int num_nodes, const char * nonlinearity)
{

  std::string nonlin (nonlinearity);

  add_layer(num_nodes, nonlin);
}

void NeuralNetwork::update_connectivity()
{

  for (auto it = layers.begin(); it != layers.end(); ++it)
  {
    // update pointers to individual layers
  }
}

std::list< std::vector<double> > NeuralNetwork::forward(const std::list< std::vector<double> >& input)
{
  std::list< std::vector<double> > output;

  for (auto one = input.cbegin(); one != input.cend(); ++one)
  {
    std::vector<double> activation = forward( *one );
    output.push_back( activation );
  }

  return output;
}

std::vector<double> NeuralNetwork::backward( const std::vector<double> & loss )
{
  std::cout << "Not Implemented!" << std::endl;

  std::vector<double> gradient;
  return gradient;
}

std::vector<double> NeuralNetwork::backward()
{

  int grad_size;
  if( layers.size() >= 2 )
  {
    grad_size = layers.rbegin()->size();
  }
  else
  {
    grad_size = mean.size();    
  }
  std::vector<double> gradient( grad_size, 1. );

  for( auto it=layers.rbegin(); it != layers.rend(); ++it )
  {
    gradient = it->backprop_gradient( gradient );
  }

  return gradient;
}

std::vector<double> NeuralNetwork::forward(const std::vector<double>& input)
{
  std::vector<double> activation = standardize_input_data( input );

  // TODO: move to different abstraction
  for (auto it = layers.begin(); it != layers.end(); ++it) {
    activation = it->compute_activation(activation);
    it->set_cache(activation);
  }

  return activation;

}

void NeuralNetwork::print()
{
  for (auto &layer : layers)
  {
    std::cout << "Layer contains: " << layer.size() << " nodes" << std::endl;

    layer.print();
  }
}

void NeuralNetwork::from_file( const char * filename )
{
  std::string my_file_name( filename );
  from_file( my_file_name );
}

void NeuralNetwork::from_file( std::string filename ) 
{
  std::ifstream myfile;
  myfile.open(filename, std::ios::in);
  std::string line;

  if( myfile.is_open()) 
  {
    std::getline( myfile, line );
    num_layers = std::stoi( line );
    std::getline( myfile, line );

    int num_input = std::stoi( line );
    int num_nodes;

    add_layer( num_input );

    for( int i=0; i<num_layers; ++i )
    {
      std::string token;

      std::getline( myfile, line );
      std::stringstream ss( line );

      std::getline( ss, token, ':' );
      num_nodes = std::stoi( token );

      std::getline( ss, token, ':');

      add_layer( num_nodes, token );

      auto it = layers.rbegin();
      it->add_nonlinearity( token );

    }

    std::vector<double> mean, stdev;

    for( int i=0; i<num_input; ++i ) 
    {
      std::getline( myfile, line );
      stdev.push_back( std::stod( line ) );

      std::getline( myfile, line );
      mean.push_back( std::stod( line ) );
    }

    set_feature_standardization( stdev, mean );

    for( auto& my_layer : layers )
    {
      std::list< std::vector<double> > weights;
      std::list< double > bias;

      for( int i=0; i<my_layer.size(); ++i )
      {
        std::getline( myfile, line );
        std::stringstream ss (line);

        std::vector<double> node_weights;

        int cnt = 0;
        for( std::string token; std::getline(ss, token, ','); ++cnt)
        {
          node_weights.push_back( std::stod( token ) );
        }

        weights.push_back(node_weights);

        std::getline( myfile, line );
        bias.push_back( std::stod( line ) );
      }

      my_layer.set_weights(weights);
      my_layer.set_bias(bias);

    }

  }

  myfile.close();

}

void NeuralNetwork::set_input_size( int num_input )
{
    std::vector<double> mean( num_input, 0. );
    this->mean = mean;

    std::vector<double> stdev( num_input, 1. );
    this->stdev  = stdev ;
}

int NeuralNetwork::get_input_size() {
    return this->mean.size();
}

const std::list<int> NeuralNetwork::get_layer_structure()
{
    std::list<int> layer_structure;
    for (auto& p : layers)
    {
        layer_structure.push_back(p.size());
    }

    return layer_structure;
}

void NeuralNetwork::set_feature_standardization(std::vector<double> stdev, std::vector<double> mean)
{
    this->mean = mean;
    this->stdev = stdev;
}

std::vector<double> NeuralNetwork::standardize_input_data( const std::vector<double> & input )
{

    std::vector<double> standardized( input.size(), 0. );
    std::transform( input.begin(), input.end(), mean.begin(), standardized.begin(), []( double a, double b ){ return( a - b ); });
    std::transform( standardized.begin(), standardized.end(), stdev.begin(), standardized.begin(), []( double a, double b ){ return( a / b ); });

    return standardized;

}

Layer& NeuralNetwork::get_layer( int num )
{
    auto layer_it = layers.begin();
    std::advance(layer_it, num);

    return *layer_it;
}

const std::vector<double>& NeuralNetwork::get_stdev()
{
    return stdev;
}