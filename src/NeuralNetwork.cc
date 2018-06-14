#include "NeuralNetwork.h"
#include <iostream>
#include <sstream>
#include <string>

void NeuralNetwork::add_layer(int num_nodes)
{

  // invalidate cached weights

  // add layer with correct number of nodes

  // 1st layer needs to get size of input layer

  if( (previous_size == 0) && (layers.size() == 0))
  {
    std::vector<double> mean( num_nodes, 0. );
    std::vector<double> stdev( num_nodes, 1. );

    this->mean = mean;
    this->stdev = stdev;

    previous_size = num_nodes;
  } else
  {
    Layer layer(num_nodes);
    layer.update_nodes(previous_size);
    previous_size = num_nodes;
    layers.push_back(layer);
  }

  update_connectivity();

  // update cached matrices for fast evaluation of linear algebra
}

void NeuralNetwork::add_layer(int num_nodes, const std::string& nonlinearity)
{
  add_layer(num_nodes);

  // better with deque
  auto last_layer = layers.end();
  --last_layer;

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
  // standardize input data

  // standardize_input_data( input );

  // compute activiation in each layer and output

  std::list< std::vector<double> > output;
  for (auto one = input.cbegin(); one != input.cend(); ++one)
  {
    std::vector<double> activation = forward( *one );
    output.push_back(activation);
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
  auto pre_last_layer = --(layers.rend());

  std::vector<double> gradient(pre_last_layer->size(), 1.);
  // std::vector<double> gradient;

  for( auto it=layers.rbegin(); it != layers.rend(); ++it )
  {
    // gradient = it->backprop_gradient(gradient);
    gradient = it->backprop_gradient( gradient );
  }

  return gradient;
}

std::vector<double> NeuralNetwork::forward(const std::vector<double>& input)
{
  std::vector<double> activation = standardize_input_data( input );

  // TODO: move to different abstraction
  for (auto it = layers.begin(); it != layers.end(); ++it) {
    it->set_cache(activation);
    activation = it->compute_activation(activation);
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

      auto it = layers.end();
      it--;
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