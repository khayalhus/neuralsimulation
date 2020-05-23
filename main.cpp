#include "network.h" // includes Network and Layer classes, this file also includes neuron.h file
// which in turn includes Neuron and its subclasses
#include "matrix.h" // includes Matrix class

#include <string>
#include <fstream>

void open_file(int argc, char* argv[], ifstream& infile) {
	if (argc != 2) throw "Not enough or too much arguments";
	// throws error if input file is not properly given
	infile.open(argv[1]); // opens the specified file
}

void read_and_parse(ifstream& infile) {
	int layerAmount; // holds amount of layers in a network
	infile >> layerAmount; // gets layer amount from input file
	int * neuronAmount = new int[layerAmount]; // stores amount of neurons at each layer
	for (int i = 0; i < layerAmount; i++) {
		infile >> neuronAmount[i]; // gets amount of neurons for each layer from input file
	}
	int * typeID = new int[layerAmount]; // stores the type of neuron for each layer
	for (int i = 0; i < layerAmount; i++) {
		infile >> typeID[i]; // gets the type of neuron for each layer
	}

	Neuron* neurons; // holds neurons for a layer
	Layer* layers = new Layer[layerAmount]; // holds layers of a network
	for (int i = 0; i < layerAmount; i++) {
		// create Neurons of all layers with default value to be changed later
		switch (typeID[i]) {
		case 0:
			neurons = new SigmoidNeuron[neuronAmount[i]]; // create Sigmoid neuron objects
			break;
		case 1:
			neurons = new LReluNeuron[neuronAmount[i]]; // create Leaky ReLU neuron objects
			break;
		case 2:
			neurons = new ReluNeuron[neuronAmount[i]]; // create ReLU neuron objects
			break;
		default:
			throw "Unidentified activation function!";
			// throws error if undefined neuron type is requested
			break;
		}
		layers[i].addNeurons(neurons); // add neurons to the layer
		layers[i].setAmount(neuronAmount[i]); // stores the amount of layers inside the object
	}
	Network* network = new Network(layers, layerAmount); // create the network object

	// take values from the input file and assign it to the neurons of the first layer
	int inputX; // holds the input values
	int counter = 0;
	while (infile >> inputX) { // reads input values
		if (counter >= neuronAmount[0]) throw "Input shape does not match!"; // too many input
		network[0][0][counter].setA(inputX); // sets A as input value
		network[0][0][counter].setZ(inputX); // sets Z as input value, this is only for first layer. (layer 0)
		counter++; // increment counter for next input
	}
	if (counter != neuronAmount[0]) throw "Input shape does not match!"; // too less of an input

	infile.close(); // close after getting all the data
	
	for (int i = 1; i < layerAmount; i++) {
		// create matrix objects for the equation: Z = W * A + B
		// since vectors are just single colum or single row matrices, they can be represented as such
		Matrix* Z = new Matrix(neuronAmount[i], 1); // creates the result (Z) vector
		for (int j = 0; j < neuronAmount[i]; j++) {
			Z->setData(j, 0, 0.0); // gives the result vector a default value of 0.0
		}
		Matrix* W = new Matrix(neuronAmount[i], neuronAmount[i - 1]); // creates the W matrix
		for (int j = 0; j < neuronAmount[i]; j++) {
			for (int k = 0; k < neuronAmount[i - 1]; k++) {
				W->setData(j, k, 0.1); // sets all w values as 0.1
			}
		}
		Matrix* A = new Matrix(neuronAmount[i - 1], 1); // create the A matrix
		for (int j = 0; j < neuronAmount[i - 1]; j++) {
			A->setData(j, 0, network[0][i - 1][j].getA()); // transfers the A values from the neurons to the matrix
		}
		Matrix* B = new Matrix(neuronAmount[i], 1); // creates the B vector
		for (int j = 0; j < neuronAmount[i]; j++) {
			B->setData(j, 0, 0.1); // sets all b values as 0.1
		}
		Z->multiply(W, A); // does the multiplication of WA and equalizes it to Z vector
		Z->add(B); // adds B to this equalization Z += B

		for (int j = 0; j < neuronAmount[i]; j++) {
			network[0][i][j].setZ(Z->getData(j, 0)); // sends the result vector Z back to the neurons in the network
			network[0][i][j].activate(); // activates the neurons
		}

		delete Z, W, A, B; // deletes allocated memory for matrices since their purpose is over
	}
	delete[] neuronAmount; // deletes the array that holds amount of neurons
	delete[] typeID; // deletes the array that hold neuron types

	network->print(); // prints network

	delete network; // deletes network object

}

int main(int argc, char* argv[]) {
	ifstream infile;
	try {
		open_file(argc, argv, infile); // opens the specified file
	}
	catch (const char* result) {
		cout << result << endl; // throws an error if file can't be opened
		exit(1);
	}
	//infile.open("input1.txt");
	try {
		read_and_parse(infile); // reads from and closes file, parses info
	}
	catch (const char* result) {
		cout << result << endl; // throws an error if there is a problem with the input
		exit(1);
	}
	exit(0); // exits successfully
}