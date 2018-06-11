#include <list>
#include <vector>
#include <fstream>
#include "Layer.h"
#include <algorithm>

class NeuralNetwork
{

  public:
    NeuralNetwork() : num_layers(0) {}
    void add_layer(int num_nodes);
    void add_layer(int num_nodes, const char *nonlinearity);
    void add_layer(int num_nodes, const std::string &nonlinearity);

    void set_input_size( int num_input )
    {
        std::vector<double> mean( num_input, 0. );
        this->mean = mean;

        std::vector<double> stdev( num_input, 1. );
        this->stdev  = stdev ;
    }

    void from_file(std::string filename);
    void update_connectivity();
    // const std::vector<double> forward( const std::vector<double>& activation );
    std::list<std::vector<double>> forward(std::list<std::vector<double>> input);

    void backward(/*some sort of loss function */);

    void print();

    int get_number_of_layers() { return num_layers; }
    const std::list<int> get_layer_structure()
    {
        std::list<int> layer_structure;
        for (auto p : layers)
        {
            layer_structure.push_back(p.size());
        }

        return layer_structure;
    }

    void set_feature_standardization(std::vector<double> stdev, std::vector<double> mean)
    {
        this->mean = mean;
        this->stdev = stdev;
    }

    std::vector<double> standardize_input_data( const std::vector<double> & input )
    {

        std::vector<double> standardized( input.size(), 0. );
        std::transform( input.begin(), input.end(), mean.begin(), standardized.begin(), []( double a, double b ){ return( a - b ); });
        std::transform( standardized.begin(), standardized.end(), stdev.begin(), standardized.begin(), []( double a, double b ){ return( a / b ); });

        return standardized;

    }

  private:
    std::list<Layer> layers;
    int num_layers;

    std::vector<double> mean, stdev;

    // TODO: use smart_pointers, stupid
    std::list<std::list<Layer *>> graph;
};

/* Q&A

Q: is it easier to just add vector/array structures to the neural network without the other classes

*/
