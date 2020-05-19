#include <algorithm> // for max()
#include <iostream>
#include <cmath>

using namespace std;

class Neuron {
protected:
	double z; // value
	double a; // activated value
public:
	Neuron(float z, float a) {
		this->z = z;
		this->a = a;
	}
	virtual void activate() = 0; // pure virtual method
	double getZ() const {
		return this->z;
	}
	double getA() const {
		return this->a;
	}
	void setZ(double z) {
		this->z = z;
	}
	void setA(double a) {
		this->a = a;
	}
	void print() {
		cout << this->a << endl;
	}
};

class SigmoidNeuron : public Neuron {
public:
	SigmoidNeuron() :Neuron(0.0, 0.0){}
	SigmoidNeuron(float z, float a) :Neuron(z, a) {}
	void activate() {
		// This method will apply sigmoid formula to it’s value (z) and assign it to
		// it’s activated value(a).
		this->a = 1 / (1 + exp(-(this->z)));
	}
};

class ReluNeuron : public Neuron {
public:
	ReluNeuron() :Neuron(0.0, 0.0) {}
	ReluNeuron(float z, float a) :Neuron(z, a) {}
	void activate() {
		// This method will apply relu formula to it’s value(z) and assign it to it’s
		// activated value(a).
		this->a = max(0.0, this->z);
	}
};

class LReluNeuron : public Neuron {
public:
	LReluNeuron() :Neuron(0.0, 0.0) {}
	LReluNeuron(float z, float a) :Neuron(z, a) {}
	void activate() {
		// This method will apply leaky relu formula to it’s value (z) and assign it
		// to it’s activated value(a).
		this->a = max(0.1 * this->z, this->z);
	}
};