#include "network.h" // includes Network and Layer classes, this file also includes neuron.h file
// which in turn includes Neuron and its subclasses
#include "matrix.h"

#include <string>
#include <fstream>

void open_file(int argc, char* argv[], ifstream& infile) {
	if (argc != 2) throw "Not enough or too much arguments";
	// throws error if input file is not properly given
	infile.open(argv[1]);
}

void read_and_parse(ifstream& infile) {
	int layerAmount;
	infile >> layerAmount; // get layer amount
	int * neuronAmount = new int[layerAmount]; // store amount of neurons at each layer
	for (int i = 0; i < layerAmount; i++) {
		infile >> neuronAmount[i]; // get amount of neurons for each layer
	}
	int * typeID = new int[layerAmount]; // store the type of neuron for each layer
	for (int i = 0; i < layerAmount; i++) {
		infile >> typeID[i]; // get the type of neuron for each layer
	}

	Neuron* neurons; // holds neurons for a layer
	Layer* layer; // hold layers for a network
	Network* network = new Network(layerAmount);
	// make Neurons with default value to be changed later
	for (int i = 0; i < layerAmount; i++) {
		switch (typeID[i]) {
		case 0:
			neurons = new SigmoidNeuron[neuronAmount[i]];
			break;
		case 1:
			neurons = new LReluNeuron[neuronAmount[i]];
			break;
		case 2:
			neurons = new ReluNeuron[neuronAmount[i]];
			break;
		default:
			throw "Unidentified activation function";
			break;
		}
		
		layer = new Layer(neurons, neuronAmount[i]);
		network->add_layer(layer, i);
	}

	// take values from the input file and assign it to the neurons of the first layer
	int inputX;
	int counter = 0;
	while (infile >> inputX) {
		if (counter >= neuronAmount[0]) throw "Input shape does not match!"; // too many input
		network[0][0][counter].setA(inputX);
		network[0][0][counter].setZ(inputX);
		counter++;
	}
	if (counter != neuronAmount[0]) throw "Input shape does not match!"; // too less of an input

	
	for (int i = 1; i < layerAmount; i++) {
		Matrix* Z = new Matrix(neuronAmount[i], 1);
		for (int j = 0; j < neuronAmount[i]; j++) {
			Z->setData(j, 0, 0.0);
		}
		Matrix* W = new Matrix(neuronAmount[i], neuronAmount[i - 1]);
		for (int j = 0; j < neuronAmount[i]; j++) {
			for (int k = 0; k < neuronAmount[i - 1]; k++) {
				W->setData(j, k, 0.1);
			}
		}
		Matrix* A = new Matrix(neuronAmount[i - 1], 1);
		for (int j = 0; j < neuronAmount[i - 1]; j++) {
			A->setData(j, 0, network[0][i - 1][j].getA());
		}
		Matrix* B = new Matrix(neuronAmount[i], 1);
		for (int j = 0; j < neuronAmount[i]; j++) {
			B->setData(j, 0, 0.1);
		}
		Z->multiply(W, A);
		Z->add(B);

		for (int j = 0; j < neuronAmount[i]; j++) {
			network[0][i][j].setZ(Z->getData(j, 0));
			network[0][i][j].activate();
		}

		delete Z, W, A, B;
	}
	delete[] neuronAmount;
	delete[] typeID;
	// won't come to this line if exception
	infile.close(); // close after getting all the data
	network->print();
}

int main(int argc, char* argv[]) {
	ifstream infile;
	
	try {
		open_file(argc, argv, infile);
	}
	catch (const char* result) {
		cout << result << endl;
		exit(1);
	}
	// infile.open("input1.txt");

	try {
		read_and_parse(infile);
	}
	catch (const char* result) {
		cout << result << endl;
		exit(1);
	}

}