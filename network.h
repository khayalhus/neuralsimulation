#include "neuron.h" // includes Neuron and its subclasses

class Layer {
	Neuron* neurons; // holds array of neurons
	int amount; // holds amount of neurons
public:
	Layer() {
		// assigns default values for default constructor
		this->neurons = NULL;
		amount = 0;
	}
	~Layer() {
		delete[] neurons; // releases dynamic array
	}
	Neuron& operator[] (int index) {
		return neurons[index]; // returns neuron at that index
	}
	void addNeurons(Neuron* neurons) {
		this->neurons = neurons; // adds neurons to the layer
	}
	void setAmount(int amount) {
		this->amount = amount; // sets the amount of neurons
	}
	void print() {
		for (int i = 0; i < amount; i++) {
			neurons[i].print(); // prints values of all neurons inside layer
		}
	}
};

class Network {
	Layer* layers; // holds layers of the network
	int amount; // holds the amount of layers in the network
public:
	Network(Layer* layers, int amount) {
		this->layers = layers; // sets the layers
		this->amount = amount; // sets the amount of layers
	}
	~Network() {
		delete[] layers; // frees layers array
	}
	Layer& operator[] (int index) {
		return layers[index]; // returns layer at the given index
	}
	void print() {
		for (int i = 0; i < amount; i++) {
			cout << "Layer " << i << ":" << endl;
			layers[i].print(); // prints layers inside the network
		}
	}
};