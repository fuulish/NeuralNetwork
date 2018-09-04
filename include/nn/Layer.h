#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <cmath>
#include <functional>
#include <nn/Node.h>

class Layer
{
  public:
    Layer(int num_nodes) : nodes(num_nodes), cache(num_nodes, 0.), nonlinear(NULL), nonlinear_gradient(NULL) {}

    void update_nodes(int num_following);
    // TODO: find better way to include more variants of activation
    //       maybe inherit from these class, but have multiple methods for activation
    //       1.) linear, then 2.) non-linear

    const std::vector<double> compute_activation(const std::vector<double> &input);
    std::vector<double> backprop_gradient( const std::vector<double>& gradient );
    void add_nonlinearity( const std::string& nonlinear_function );
    void set_bias( const std::list< double > bias );
    void set_weights( std::list< std::vector<double> > weights );
    int size() const;
    void print();
    void set_cache( const std::vector<double>& cache );

  private:
    std::list<Node> nodes;
    std::vector<double> cache;
    std::function<double(double)> nonlinear;
    std::function<double(double)> nonlinear_gradient;
};
