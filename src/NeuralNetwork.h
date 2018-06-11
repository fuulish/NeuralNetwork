#include <list>
#include <vector>
#include <fstream>
#include "Layer.h"
#include <algorithm>

class NeuralNetwork
{

  public:
    NeuralNetwork() : mean(0.), std(1.), num_layers(0) {}
    void add_layer(int num_nodes);
    void add_layer(int num_nodes, const char *nonlinearity);
    void add_layer(int num_nodes, const std::string &nonlinearity);
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

    void set_feature_standardization(double std, double mean)
    {
        this->mean = mean;
        this->std = std;
    }

    void standardize_input_data( std::list< std::vector<double> >& input )
    {
        for( auto &p : input )
        {
            std::transform( p.begin(), p.end(), p.begin(), [this]( double a ){return (a - this->mean) / this->std;});
        }
    }

  private:
    std::list<Layer> layers;
    double mean, std;
    int num_layers;

    // TODO: use smart_pointers, stupid
    std::list<std::list<Layer *>> graph;
};

/* Q&A

Q: is it easier to just add vector/array structures to the neural network without the other classes

*/
