#include "Layer.h"

void Layer::update_nodes(int num_following) {
  // TODO: should this be auto&, does this matter
  for( auto node : nodes) {
    node.reset_size(num_following);
  }

  // for( auto it = nodes.begin(); it != nodes.end(); ++it ) {
  //   it->reset_size(num_following);
  // }
}

std::vector<double> Layer::compute_activation(const std::vector<double>& input) {
    std::vector<double> activation;

    return activation;
}
