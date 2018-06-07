#include <iostream>
#include "NeuralNetwork.h"

int main(int argc, char *argv[]) {
    NeuralNetwork brain;

    brain.add_layer(10);

    std::cout << "everything fine so far" << std::endl;

}
