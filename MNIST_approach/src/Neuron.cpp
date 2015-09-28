//
// Created by Moustapha on 27/09/2015.
//

#include "Neuron.hpp"

Neural_Net::Neuron::Neuron()
    :output(0.0)
{

}

Neural_Net::Neuron::~Neuron() {

}

void Neural_Net::Neuron::addConnection(unsigned int iNeuron, unsigned int iWeight) {
    connections.push_back(Connection(iNeuron, iWeight));
}

void Neural_Net::Neuron::addConnection(const Neural_Net::Connection &conn) {
    connections.push_back(conn);
}
