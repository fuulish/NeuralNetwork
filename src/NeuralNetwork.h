#include <list>
#include <vector>

class  NeuralNetwork {

    public:
        NeuralNetwork() {}
        void add_layer( int num_nodes ) {
        }

    private:
        int num_layers = 0;
        std::list<std::vector<double>> layers;


};