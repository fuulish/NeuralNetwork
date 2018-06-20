#include <list>
#include <vector>
#include <fstream>
#include <nn/Layer.h>
#include <algorithm>

class NeuralNetwork
{

  public:
    NeuralNetwork() : num_layers(0), previous_size(0) {}
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
    void from_file(const char * filename);
    void update_connectivity();
    // const std::vector<double> forward( const std::vector<double>& activation );
    std::list<std::vector<double> > forward(const std::list<std::vector<double>>& input);
    std::vector<double> forward(const std::vector<double>& input);

    std::vector<double> backward(const std::vector<double> & loss ); // compute gradient based on loss function
    std::vector<double> backward(); // compute the gradients solely based on the output/input

    void print();

    int get_number_of_layers() { return layers.size(); }
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

    // TODO: use pointer or reference here?
    Layer* get_layer( int num )
    {
        auto layer_it = layers.begin();
        std::advance(layer_it, num);

        return &(*layer_it);
    }

  private:
    std::list<Layer> layers;
    int num_layers, previous_size;
    int input_size;

    std::vector<double> mean, stdev;

    // TODO: use smart_pointers, stupid
    std::list<std::list<Layer *>> graph;
};

/* Q&A

Q: is it easier to just add vector/array structures to the neural network without the other classes

*/
