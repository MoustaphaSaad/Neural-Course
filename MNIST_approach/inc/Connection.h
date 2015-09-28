//
// Created by Moustapha on 27/09/2015.
//

#ifndef NEURAL_COURSE_CONNECTION_H
#define NEURAL_COURSE_CONNECTION_H

#include <limits.h>

namespace Neural_Net {
    class Connection {
    public:
        ///neuron_ix of the neuron
        unsigned int neuron_ix;
        ///weight_ix of the connection
        unsigned int weight_ix;

        Connection(unsigned int neuron = ULONG_MAX, unsigned int _weight = ULONG_MAX);
        ~Connection();
    };
}


#endif //NEURAL_COURSE_CONNECTION_H
