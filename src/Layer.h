#include <vector>
#include <list>
#include "Node.h"

class Layer {
    public:
        Layer(int num_nodes) : nodes(num_nodes), activation(num_nodes) {}

        void update_nodes( int num_following );
        // TODO: should this return a reference as well?
        const std::vector<double> compute_activation( const std::vector<double>& input);

        int size () {
          return nodes.size();
        }

        // const std::vector<double> activation();
    private:
        std::list<Node> nodes;
        std::vector<double> activation;
};