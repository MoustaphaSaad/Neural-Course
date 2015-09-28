//
// Created by Moustapha on 27/09/2015.
//

#ifndef NEURAL_COURSE_GLOBAL_PROP_HPP
#define NEURAL_COURSE_GLOBAL_PROP_HPP
#include <math.h>

namespace Neural_Net{
    static double sigmoid(double val){
        return 1.7159*tanh(0.66666667 * val);
    }

    static double sigmoid_dx(double val){
        return (0.66666667/1.7159*(1.7159+val)*(1.7159-val));
    }

    static const double ETA = 0.15;
}
#endif //NEURAL_COURSE_GLOBAL_PROP_HPP
