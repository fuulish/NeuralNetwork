#include "Layer.h"

void Layer::update_nodes(int num_following) {
  for( auto& node : nodes) {
    node.reset_size(num_following);
  }

  // for( auto it = nodes.begin(); it != nodes.end(); ++it ) {
  //   it->reset_size(num_following);
  // }
}

const std::vector<double> Layer::compute_activation(const std::vector<double>& input) {

  auto it = nodes.cbegin();

  int num_weights = size() * it->size();
  std::vector<double> weights(num_weights, 0.);

  std::vector<double> activation(size(), 0.);

  for( int i=0; i<size(); ++i ) {

  }

  return activation;
}

// std::list<std::vector<double>> Layer::compute_coupling(std::vector<double> activation) {
// 
// }