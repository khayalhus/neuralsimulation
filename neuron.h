class Neuron {
	double z; // value
	double a; // activated value
public:
	virtual void activate() = 0; // pure virtual method
	double getZ() const {
		return this->z;
	}
	double getA() const {
		return this->a;
	}
};

class SigmoidNeuron : public Neuron {
public:
	void activate() {
		// This method will apply sigmoid formula to it’s value (z) and assign it to
		// it’s activated value(a).
	}
};

class ReluNeuron : public Neuron {
public:
	void activate() {
		// This method will apply relu formula to it’s value(z) and assign it to it’s
		// activated value(a).
	}
};

class LReluNeuron : public Neuron {
public:
	void activate() {
		// This method will apply leaky relu formula to it’s value (z) and assign it
		// to it’s activated value(a).
	}
};