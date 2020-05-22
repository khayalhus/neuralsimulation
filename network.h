#include "neuron.h" // includes Neuron and its subclasses

class Layer {
	Neuron* neurons;
	int amount;
public:
	Layer() {
		this->neurons = NULL;
		amount = 0;
	}
	Layer(Neuron* neurons, int amount) {
		this->neurons = neurons;
		this->amount = amount;
	}
	~Layer() {
		delete[] neurons;
	}
	Neuron& operator[] (int index) {
		return neurons[index];
	}
	void print() {
		for (int i = 0; i < amount; i++) {
			neurons[i].print();
		}
	}
};

class Network {
	Layer* layers;
	int amount;
public:
	Network(int amount) {
		this->amount = amount;
		layers = new Layer[amount];
	}
	Network(Layer* layers, int amount) {
		this->layers = layers;
		this->amount = amount;
	}
	~Network() {
		delete[] layers;
	}
	void add_layer(Layer* layer, int index) {
		layers[index] = *layer;
	}
	Layer& operator[] (int index) {
		return layers[index];
	}
	void print() {
		for (int i = 0; i < amount; i++) {
			cout << "Layer " << i << ":" << endl;
			layers[i].print();
		}
	}
};