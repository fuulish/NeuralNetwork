#include <iostream>
#include "NeuralNetwork.h"

int main(int argc, char *argv[]) {
    NeuralNetwork brain;

    brain.add_layer(10);
    brain.add_layer(10);

    std::list<std::vector<double>> input;
    std::vector<double> one_pic(10, 1);

    input.push_back(one_pic);
    
    brain.print();

    brain.forward(input);

}
