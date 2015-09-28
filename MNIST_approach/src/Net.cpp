//
// Created by Moustapha on 27/09/2015.
//

#include <assert.h>
#include <Global_Prop.hpp>
#include "Net.hpp"


Neural_Net::Net::Net() {

}

Neural_Net::Net::~Net() {
    for(int i=0;i<layers.size();++i){
        delete layers[i];
    }


}

void Neural_Net::Net::forward_prop(const std::vector<double> &input, std::vector<double> &output) {
    std::vector<Layer*>::iterator layers_it = layers.begin();
    std::vector<Neuron*>::iterator neuron_it;

    //check if layer iterator is a valid one
    if(layers_it < layers.end()){
        //then initialize all output of input layer neurons to input vector
        neuron_it = (*layers_it)->neurons.begin();

        int count = 0;

        //input vector should have as much input as there's neurons
        //one neuron <= one input
        assert(input.size() == (*layers_it)->neurons.size());

        //wire every input to input-layer neuron
        while(neuron_it != (*layers_it)->neurons.end()){
            (*neuron_it)->output = input[count];
            neuron_it++;
            count++;
        }
    }

    //iterate through layers and perform forward_prop
    for(layers_it++; layers_it != layers.end(); layers_it++){
        (*layers_it)->forward_prop();
    }

    //copy the output layer to the output vector
    layers_it = layers.end()-1;
    neuron_it = (*layers_it)->neurons.begin();

    while(neuron_it != (*layers_it)->neurons.begin()){
        output.push_back((*neuron_it)->output);
        neuron_it++;
    }
}

void Neural_Net::Net::back_prop(const std::vector<double> &output, const std::vector<double> &target) {
/**
 * backpropagates through neural net from output to input
 * the main concept is we know the error, but we go backward to check each layer
 * output and change the weights to reduce the error
 */

    std::vector<Layer*>::iterator layer_it = layers.end()-1;

    std::vector<double> dEdX((*layer_it)->neurons.size());
    std::vector<std::vector<double> > dXdY;

    int layer_count = layers.size();

    dXdY.resize(layer_count);

    int i;

    /**
     * calculate the dEdX for output layer
     * it's simply the derivative of standard error function
     * (0.5*sum(actual-target)^2) => actual-target
     */
    for(i=0;i<(*layer_it)->neurons.size();i++){
        dEdX[i] = output[i]-target[i];
    }

    //storing last dEdX ans reserve for others
    dXdY[layer_count-1] = dEdX;
    //resize and initialize the other vectors
    for(i=0;i<layer_count-1;i++){
        dXdY[i].resize(layers[i]->neurons.size(),0.0);
    }

    /**
     * now iterate through all layers and invoke
     * backpropagation function execluding the input layer
     * since it's the start layer giving it the dEdX of the next layer since we are
     * progressing backwards
     */
    i = layer_count-1;
    for(layer_it;layer_it!=layers.begin();layer_it--){
        (*layer_it)->back_prop(dXdY[i],dXdY[i-1],ETA);
        //dec the index to move along with layers
        i--;
    }
    dXdY.clear();
}
