#include "NeuralNetwork.h"
#include <iostream>
#include <sstream>
#include <string>

void NeuralNetwork::add_layer(int num_nodes)
{

  // invalidate cached weights

  // add layer with correct number of nodes

  Layer layer(num_nodes);
  auto last_layer = layers.end();

  if (layers.size() >= 1)
  {
    --last_layer;
    layer.update_nodes(last_layer->size());
  }

  layers.push_back(layer);

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
  std::string nonlin ("nonlinearity");

  add_layer(num_nodes, nonlin);
}

void NeuralNetwork::update_connectivity()
{

  for (auto it = layers.begin(); it != layers.end(); ++it)
  {
    // update pointers to individual layers
  }
}

std::list< std::vector<double> > NeuralNetwork::forward(std::list< std::vector<double> > input)
{
  // standardize input data

  standardize_input_data( input );

  // compute activiation in each layer and output

  std::list< std::vector<double> > output;

  // TODO: enter here, efficient matrix multiplication routine

  for (auto one = input.cbegin(); one != input.cend(); ++one)
  {
    std::vector<double> activation;
    activation = *one;

    // TODO: move to different abstraction
    for (auto it = layers.begin(); it != layers.end(); ++it)
      activation = it->compute_activation(activation);

    output.push_back(activation);
  }

  return output;
}

void NeuralNetwork::print()
{
  for (auto &layer : layers)
  {
    std::cout << "Layer contains: " << layer.size() << " nodes" << std::endl;

    layer.print();
  }
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

    std::stringstream ms( line );
    std::string token;

    std::getline( ms, token, ',' );
    double mean = stod( token );

    std::getline( ms, token, ',' );
    double std = stod( token );

    std::cout << mean << std << std::endl;

    set_feature_standardization( std, mean );

    int num_nodes;

    for( int i=0; i<num_layers; ++i )
    {
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

    // read in weights and biases for each node

    // for( int i=0; i<num_layers; ++i )
    // {
    //   std::getline( myfile, line );
    //   num_nodes = std::stoi( line );
    // }
  }
  // else 
  // {
  //     raise 
  // }

  myfile.close();

}