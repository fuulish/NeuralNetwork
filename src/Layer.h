#include <vector>
#include <list>
#include <iostream>
#include "Node.h"

class Layer {
    public:
        Layer(int num_nodes) : nodes(num_nodes), activation(num_nodes) {}

        void update_nodes( int num_following );
        // TODO: should this return a reference as well?
        // const std::vector<double> compute_activation( const std::vector<double>& input);

        const std::vector<double> compute_activation(std::list<std::vector<double>> input);
        std::list<std::vector<double>> compute_coupling(std::vector<double> activation);

        int size () const {
          return nodes.size();
        }


        void print() {
          for ( auto& node : nodes )
            std::cout << "node with " << node.size() << " weights" << std::endl;
        }

        // const std::vector<double> activation();
    private:
        std::list<Node> nodes;
        std::vector<double> activation;
};