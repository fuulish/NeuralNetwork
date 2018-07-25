#include <cmath>
#include <algorithm>
#include <nn/Layer.h>
#include <cassert>

void Layer::update_nodes(int num_following)
{
  for (auto &node : nodes)
  {
    node.reset_size(num_following);
  }
}

const std::vector<double> Layer::compute_activation(const std::vector<double> &input)
{

  std::vector<double> activation(size(), 0.);

  int cnt = 0;
  for (auto& node : nodes)
  {
    activation[cnt++] = node.activate(input);
  }

  // TODO: find better way to treat non-linear activation, reference ok?
  if( nonlinear )
  {
    for( auto& p : activation )
    {
      p = nonlinear(p);
    }
    /* include non-linearity */
  }

  return activation;
}

std::vector<double> Layer::backprop_gradient( const std::vector<double>& gradient ) // gradient is the gradient on each node from the previous layer
{

  // size of new gradient is the size of the nodes' weight array
  std::vector<double> backprop ((*nodes.cbegin()).size(), 0.);

// TODO: check why this assertion is meaninless
#ifdef DEBUG
//   assert( gradient.size() == backprop.size() );
#endif

  // 1. get gradient from each node on previous layer
  // not always do we need the previous' layer's activations, but sometimes? <- node-specific

  auto cache_it = cache.cbegin();
  auto gradient_it = gradient.cbegin();

  for( auto& node : nodes ) {

    std::vector<double> node_grad = node.gradient();

#ifdef DEBUG
//     std::cout << cache.size() << gradient.size() << node_grad.size() <<  backprop.size() << std::endl;
#endif

    std::transform( node_grad.begin(), node_grad.end(), node_grad.begin(),
                    [ gradient_it ] ( double a )
                    { return (*gradient_it) * a; } );

    if( nonlinear )
    {
      std::transform( node_grad.begin(), node_grad.end(), node_grad.begin(),
                      [ this, cache_it ] ( double a )
                      { return a * this->nonlinear_gradient( *cache_it ); } );
    }

    std::transform( node_grad.begin(), node_grad.end(), backprop.begin(), backprop.begin(), []( double a, double b ) {return a + b; } );

    // std::cout << "MY SIZE: " << node_grad.size() << std::endl;

    // for( auto grd : node_grad )
    // {
    //   std::cout << "NODE GRAD: " << grd << " " << *cache_it << std::endl;

    //   if( nonlinear )
    //     std::cout << "BLABLA: " << this->nonlinear_gradient( *cache_it ) << std::endl;

    //   if( nonlinear ) {
    //     std::transform( node_grad.begin(), node_grad.end(), backprop.begin(), backprop.begin(),
    //                   [ this, cache_it ]( double a, double b ){ return b + ( (a) * this->nonlinear_gradient( *cache_it ) );} );
    //   }

    // }

    std::advance( cache_it, 1 );
    std::advance( gradient_it, 1 );

    // std::transform( node_gra );
    // backprop 
  }

  // 2. get gradient of activation function <- layer-specific // multiply with gradient from 1.

  return backprop;
}

void Layer::add_nonlinearity( const std::string& nonlinear_function ) {
    if( nonlinear_function.compare("tanh") == 0 ) {
        nonlinear = []( double a ){ return tanh(a); };
        // TODO: eliminate twice tanh evaluation
        nonlinear_gradient = [] ( double a ){ return 1 - ( a*a ); }; // this is the outermost function derivative, a is the saved activation, i.e., tanh(node_input) // TODO think about how to do differently
    }
}

void Layer::set_bias( const std::list< double > bias )
{
    auto it = bias.begin();
    for( auto& p : nodes ) {

        p.update_bias( *it );
        std::advance(it, 1);

    }
}

void Layer::set_weights( std::list< std::vector<double> > weights )
{
    auto it = weights.begin();
    for( auto& p : nodes ) {

        p.update_weights( *it );
        std::advance(it, 1);

    }

}

int Layer::size() const
{
    return nodes.size();
}

void Layer::print()
{
    for (auto &node : nodes)
        std::cout << "node with " << node.size() << " weights" << std::endl;
}
void Layer::set_cache( const std::vector<double>& cache )
{
    this->cache = cache;
}