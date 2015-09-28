//
// Created by Moustapha on 27/09/2015.
//

#ifndef NEURAL_COURSE_NET_HPP
#define NEURAL_COURSE_NET_HPP

#include <vector>
#include "Layer.hpp"

namespace Neural_Net{
    class Net{
    public:
        Net();
        ~Net();

        void forward_prop(const std::vector<double>& input,
        std::vector<double>& output);

        void back_prop(const std::vector<double>& output,
        const std::vector<double>& target);

        std::vector<Layer*> layers;
    };
}

#endif //NEURAL_COURSE_NET_HPP
