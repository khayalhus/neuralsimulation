#include <algorithm> // for max()
#include <iostream> // for cout and endl
#include <cmath> // for exp()

using namespace std;

class Neuron {
protected:
	double z; // value
	double a; // activated value
public:
	Neuron(float z, float a) {
		this->z = z; // sets activated value
		this->a = a; // sets value
	}
	virtual void activate() = 0; // pure virtual method
	double getZ() const {
		return this->z; // gets activated value
	}
	double getA() const {
		return this->a; // gets value
	}
	void setZ(double z) {
		this->z = z; // sets activated value
	}
	void setA(double a) {
		this->a = a; // sets value
	}
	void print() {
		cout << this->a << endl; // prints value
	}
};

class SigmoidNeuron : public Neuron {
public:
	SigmoidNeuron() :Neuron(0.0, 0.0){} // sets a default value
	void activate() {
		// This method will apply sigmoid formula to its value(z) and assign it to its activated value(a).
		this->a = 1 / (1 + exp(-(this->z)));
		// f(x) = 1 / (1 + e^(-x))
	}
};

class ReluNeuron : public Neuron {
public:
	ReluNeuron() :Neuron(0.0, 0.0) {} // sets a default value
	void activate() {
		// This method will apply relu formula to its value(z) and assign it to its activated value(a).
		this->a = max(0.0, this->z);
		// f(x) = max(0, x)
	}
};

class LReluNeuron : public Neuron {
public:
	LReluNeuron() :Neuron(0.0, 0.0) {} // sets a default value
	void activate() {
		// This method will apply leaky relu formula to its value(z) and assign it to its activated value(a).
		this->a = max(0.1 * this->z, this->z);
		// f(x) = max(0.1 * x, x)
	}
};