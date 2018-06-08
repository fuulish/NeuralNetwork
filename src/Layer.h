#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <cmath>
#include <functional>
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

    void add_nonlinearity( const std::string& nonlinear_function ) {
        if( nonlinear_function.compare("tanh") == 0 ) {
            nonlinear = std::bind( tanh, std::placeholders::_1 );
        }
    }

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
    std::function<double(double)> nonlinear = NULL;
};