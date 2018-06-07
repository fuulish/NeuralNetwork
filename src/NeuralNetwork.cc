#include "NeuralNetwork.h"

void NeuralNetwork::add_layer(int num_nodes) {

            // invalidate cached weights

            // add layer with correct number of nodes

            Layer layer(num_nodes);
            layers.push_back(layer);

            // update node weight 


            // update cached matrices for fast evaluation of linear algebra

}

void NeuralNetwork::initialize_nodes( std::ifstream input_file) {

}