//
// Created by Moustapha on 27/09/2015.
//

#include <assert.h>
#include "Layer.hpp"
#include "Global_Prop.hpp"

Neural_Net::Layer::Layer(Neural_Net::Layer *prev)
    :prev_layer(prev)
{

}

Neural_Net::Layer::~Layer() {
    for(int i=0;i<neurons.size();i++){
        delete neurons[i];
        delete weights[i];
    }
}

void Neural_Net::Layer::forward_prop() {
    //making sure prev layer is attached
    assert(prev_layer != NULL);

    std::vector<Neuron*>::iterator neuron_it;
    std::vector<Connection>::iterator con_it;

    double dSum;

    for(neuron_it = neurons.begin();
            neuron_it != neurons.end();
            neuron_it++)
    {
        Neuron* neuron = *neuron_it;

        con_it = neuron->connections.begin();
        //assert that weight_ix is initialized correctly
        assert((*con_it).weight_ix < weights.size());

        //this is the bias neuron, since it's not a real node then the bias is the weight itself
        dSum = weights[(*con_it).weight_ix]->value;

        for(con_it++;con_it!=neuron->connections.end();con_it++){
            //check the size
            assert((*con_it).weight_ix < weights.size());
            //check neuron index
            assert((*con_it).neuron_ix < prev_layer->neurons.size());

            //FEED FORWARD FORMULA
            dSum += (weights[(*con_it).weight_ix]->value) * (prev_layer->neurons[(*con_it).neuron_ix]->output);
        }
        //calling activation function in order to map the output
        neuron->output = sigmoid(dSum);
    }
}

void Neural_Net::Layer::back_prop(std::vector<double> &err_dX, std::vector<double>& err_out, double learningRate) {
    //err_dX = next layer error
    //err_out = current layer error

    double output;

    std::vector<double> err_dY(neurons.size());

    //d_out1/d_net1 => part 2 of the equation = dxdy of the sigmoid function
    //calculate: dEdY = f'(Y) * dEdX
    for(int i=0;i<neurons.size();i++){
        output = neurons[i]->output;

        err_dY[i] = sigmoid_dx(output) * err_dX[i];
    }

    std::vector<double> dEdW;
    dEdW.resize(weights.size(),0.0);
    //calculate: dEdW = neuron_output * dEdY
    //go through each neuron and update differential for corresponding weight

    //d_net1/d_w[i] => this is part 3 of the equation = dxdy of the net1
    std::vector<Neuron*>::iterator neuron_it;
    std::vector<Connection>::iterator con_it;
    int i=0;
    for(neuron_it = neurons.begin();neuron_it!= neurons.end();neuron_it++){
        Neuron* neuron = *neuron_it;

        for(con_it = neuron->connections.begin();
                con_it != neuron->connections.end();
                con_it++)
        {
            auto nix = (*con_it).neuron_ix;

            if(nix == ULONG_MAX){
                //this is the bias weight
                output = 1.0;
            }else{
                output = prev_layer->neurons[nix]->output;
            }

            dEdW[(*con_it).weight_ix] += err_dY[i] * output;
        }

        i++;
    }

    i = 0;
    for(neuron_it = neurons.begin();neuron_it!=neurons.end();neuron_it++){
        Neuron* neuron = *neuron_it;

        for(con_it = neuron->connections.begin();
                con_it!=neuron->connections.end();
                con_it++)
        {
            auto nix = (*con_it).neuron_ix;
            if(nix != ULONG_MAX)
            {
                //elminate bias neuron since we need to keep it's value
                err_out[nix] += err_dY[i] * weights[(*con_it).weight_ix]->value;
            }
        }
        i++;
    }

    //change the weights of the layer
    for(i=0;i<weights.size();i++){
        auto oldVal = weights[i]->value;
        //this is the change formula => w' = w - ETA * dE/dW
        auto newVal = oldVal - ETA * dEdW[i];
        weights[i]->value = newVal;
    }
}
