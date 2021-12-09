#pragma once

#include "ofColor.h"
#include "ofLog.h"
#include "Records.h"

using std::vector;
using std::unique_ptr;
using std::make_unique;

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
