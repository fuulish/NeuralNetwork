#include <vector>

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