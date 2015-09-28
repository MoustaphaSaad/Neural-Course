//
// Created by Moustapha on 27/09/2015.
//

#ifndef NEURAL_COURSE_WEIGHT_H
#define NEURAL_COURSE_WEIGHT_H

namespace Neural_Net {
    class Weight {
    public:
        Weight(double val = 0.0);
        ~Weight();

        double value;
    };
}


#endif //NEURAL_COURSE_WEIGHT_H
