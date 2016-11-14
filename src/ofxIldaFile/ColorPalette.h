#pragma once

#include "ofColor.h"
#include "Records.h"

namespace ofxIldaFile {
	class ColorPalette {
	public:
		//get singleton
		static ColorPalette & X();

		vector<ofColor> & getColors();
		const vector<ofColor> & getColors() const;

		void addRecord(const Records::Format2 &);
		void clear();

		ofColor getColor(size_t index);

		void loadDefaultPalette();
	protected:
		vector<ofColor> colors;
	};
}