#include <vector>
#include <list>
#include <iostream>
#include "Node.h"

class Layer
{
  public:
    Layer(int num_nodes) : nodes(num_nodes), activation(num_nodes) {}

    void update_nodes(int num_following);
    // TODO: find better way to include more variants of activation
    //       maybe inherit from these class, but have multiple methods for activation
    //       1.) linear, then 2.) non-linear

    const std::vector<double> compute_activation(const std::vector<double> &input);

    int size() const
    {
        return nodes.size();
    }

    void print()
    {
        for (auto &node : nodes)
            std::cout << "node with " << node.size() << " weights" << std::endl;
    }

  private:
    std::list<Node> nodes;
    std::vector<double> activation;
};