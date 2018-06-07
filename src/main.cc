#include <iostream>
#include "NeuralNetwork.h"

int main(int argc, char *argv[]) {
    NeuralNetwork brain;

    brain.add_layer(10);
    brain.add_layer(10);

    std::vector<double> input (10, 1.);
    
    brain.print();

    brain.forward(input);

}
