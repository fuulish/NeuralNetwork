#include <vector>
#include <list>
#include "Node.h"

class Layer {
    public:
        Layer(int num_nodes) : nodes(num_nodes), activation(num_nodes) {}

        void update_nodes();
        // TODO: should this return a reference as well?
        std::vector<double> compute_activation( const std::vector<double>& input);

        // const std::vector<double> activation();
    private:
        std::list<Node> nodes;
        std::vector<double> activation;
};