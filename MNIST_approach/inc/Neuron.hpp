//
// Created by Moustapha on 27/09/2015.
//

#ifndef NEURAL_COURSE_NEURON_HPP
#define NEURAL_COURSE_NEURON_HPP

#include "Connection.h"
#include <vector>
namespace Neural_Net{
    class Neuron{
    public:
        Neuron();
        ~Neuron();

        void addConnection(unsigned int iNeuron, unsigned int iWeight);
        void addConnection(const Connection& conn);

        double output;

        std::vector<Connection> connections;
    };
}
#endif //NEURAL_COURSE_NEURON_HPP
