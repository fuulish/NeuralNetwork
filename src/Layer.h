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

    std::vector<double> backprop_gradient( const std::vector<double>& gradient );

    void add_nonlinearity( const std::string& nonlinear_function ) {
        if( nonlinear_function.compare("tanh") == 0 ) {
            nonlinear = []( double a ){ return tanh(a); };
            // TODO: eliminate twice tanh evaluation
            nonlinear_gradient = [] ( double a ){ return ( 1 - (tanh(a)*tanh(a)));};
        }
    }

    void set_bias( const std::list< double > bias )
    {
        auto it = bias.begin();
        for( auto& p : nodes ) {

            p.update_bias( *it );
            std::advance(it, 1);

        }
    }

    void set_weights( std::list< std::vector<double> > weights )
    {
        auto it = weights.begin();
        for( auto& p : nodes ) {

            p.update_weights( *it );
            std::advance(it, 1);

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

    void set_cache( const std::vector<double>& cache )
    {
        this->cache = cache;
    }

    // std::vector<double> backprop_gradient( const std::vector<double>& gradient );

  private:
    std::list<Node> nodes;
    std::vector<double> activation;
    std::function<double(double)> nonlinear = NULL;
    std::function<double(double)> nonlinear_gradient = NULL;
    std::vector<double> cache;
};