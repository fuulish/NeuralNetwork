#include "NeuralNetwork.h"
#include <iostream>

void NeuralNetwork::add_layer(int num_nodes) {

    // invalidate cached weights

    // add layer with correct number of nodes

    Layer layer(num_nodes);
    layers.push_back(layer);

    // NOTE: as long as this is the only place we need to use the iterator for element access, OK, otherwise other data structure necessary

    if( layers.size() > 1 ) {
        std::list<Layer>::iterator it = layers.begin();
        std::advance(it, layers.size() - 2);

        it->update_nodes(num_nodes);
    }

    update_connectivity();

    // update node weight: each node in the previous layer should get his weights updated

    // update cached matrices for fast evaluation of linear algebra

}

void NeuralNetwork::initialize_nodes( std::ifstream input_file) {

}

void NeuralNetwork::update_connectivity() {

    for( auto it = layers.begin(); it != layers.end(); ++it ) {
        // update pointers to individual layers
    }
}

const std::vector<double> NeuralNetwork::forward( const std::vector<double>& input ) {
    // compute activiation in each layer and output

    std::vector<double> activation(input);

    for( auto it = layers.begin(); it != layers.end(); ++it ) {
        activation = it->compute_activation(activation);
    }

    return activation;

}

void NeuralNetwork::print() {
    for( auto& layer : layers ) {
        std::cout << "Layer contains: " << layer.size() << " nodes" << std::endl;
    }
}