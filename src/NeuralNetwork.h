#include <list>
#include <vector>
#include <fstream>
#include "Layer.h"

class  NeuralNetwork {

    public:
        NeuralNetwork() {}
        void add_layer( int num_nodes );
        void initialize_nodes( std::ifstream input_file );
        void update_connectivity();
        const std::vector<double> forward( const std::vector<double>& activation );
        void backward(/*some sort of loss function */);

        void print();

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
