#include "Records.h"

namespace ofxIldaFile {

	//----------
	void Records::Format0::swapEndian() {
		::swapEndian(this->x);
		::swapEndian(this->y);
		::swapEndian(this->z);
	}

	//----------
	void Records::Format1::swapEndian() {
		::swapEndian(this->x);
		::swapEndian(this->y);
	}

	//----------
	void Records::Format2::swapEndian() {

	}

	//----------
	void Records::Format4::swapEndian() {
		::swapEndian(this->x);
		::swapEndian(this->y);
		::swapEndian(this->z);
	}

	//----------
	ofColor Records::Format4::getColor() const {
		return ofColor(this->red, this->green, this->blue);
	}

	//----------
	ofColor Records::Format5::getColor() const {
		return ofColor(this->red, this->green, this->blue);
	}

	//----------
	void Records::Format5::swapEndian() {
		::swapEndian(this->x);
		::swapEndian(this->y);
	}
}