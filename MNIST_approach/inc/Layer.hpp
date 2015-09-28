//
// Created by Moustapha on 27/09/2015.
//

#ifndef NEURAL_COURSE_LAYER_HPP
#define NEURAL_COURSE_LAYER_HPP

#include <vector>
#include <stddef.h>
#include "Neuron.hpp"
#include "Weight.h"

namespace Neural_Net{
    class Layer{
    public:
        Layer* prev_layer;
        std::vector<Neuron*> neurons;
        std::vector<Weight*> weights;

        Layer(Layer* prev = NULL);
        ~Layer();

        void forward_prop();

        void back_prop(std::vector<double>& err_dX,
        std::vector<double>& err_out,
        double learningRate);
    };
}
#endif //NEURAL_COURSE_LAYER_HPP
