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

    void set_input_size( int num_input );
    int get_input_size();
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
    const std::list<int> get_layer_structure();
    void set_feature_standardization(std::vector<double> stdev, std::vector<double> mean);
    std::vector<double> standardize_input_data( const std::vector<double> & input );
    // TODO: use pointer or reference here?
    Layer& get_layer( int num );
    const std::vector<double>& get_stdev();

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
