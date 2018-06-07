#include <list>
#include <vector>
#include <fstream>

class Node {
    public:
        Node () {}

        void update_weights( const std::vector<double>& input_weights) {
            weights = input_weights;
        }

        void update_bias( const std::vector<double>& input_bias ) {
            bias = input_bias;
        }

    private:
        std::vector<double> weights;
        std::vector<double> bias;
};

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

class  NeuralNetwork {

    public:
        NeuralNetwork() {}
        void add_layer( int num_nodes );
        void initialize_nodes( std::ifstream input_file );
        void update_connectivity();
        const std::vector<double> forward( const std::vector<double>& activation );
        void backward(/*some sort of loss function */);

    private:
        int num_layers = 0;
        std::list<Layer> layers;

        int num_previous_nodes = 0;

        // TODO: use smart_pointers, stupid
        std::list<std::list<Layer*>> graph;

};

/* Q&A

Q: is it easier to just add vector/array structures to the neural network without the other classes

*/
