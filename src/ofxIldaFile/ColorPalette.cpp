#include "ColorPalette.h"

#include "ofGraphics.h"

namespace ofxIldaFile {
	//----------
	ColorPalette & ColorPalette::X() {
		static unique_ptr<ColorPalette> colorPalette = make_unique<ColorPalette>();
		return *colorPalette;
	}

	//----------
	vector<ofColor> & ColorPalette::getColors() {
		return this->colors;
	}

	//----------
	const vector<ofColor> & ColorPalette::getColors() const {
		return this->colors;
	}

	//----------
	void ColorPalette::addRecord(const Records::Format2 & record) {
		this->colors.emplace_back(record.red, record.green, record.blue);
	}

	//----------
	void ColorPalette::clear() {
		this->colors.clear();
	}

	//----------
	ofColor ColorPalette::getColor(size_t index) {
		if (this->colors.empty()) {
			this->loadDefaultPalette();
		}
		else if (index >= this->colors.size()) {
			ofLogWarning("ofxIldaFile::ColorPalette") << "Color index [" << index << "] outside bounds of currently loaded palette.";
		}

		return this->colors[index];
	}

	//----------
	void ColorPalette::loadDefaultPalette() {
		this->clear();

		//default palette : http://www.laserist.org/StandardsDocs/ILDA_IDTF14_rev011.pdf
		this->colors.emplace_back(255, 0, 0);
		this->colors.emplace_back(255, 16, 0);
		this->colors.emplace_back(255, 32, 0);
		this->colors.emplace_back(255, 48, 0);
		this->colors.emplace_back(255, 64, 0);
		this->colors.emplace_back(255, 80, 0);
		this->colors.emplace_back(255, 96, 0);
		this->colors.emplace_back(255, 112, 0);
		this->colors.emplace_back(255, 128, 0);
		this->colors.emplace_back(255, 144, 0);
		this->colors.emplace_back(255, 160, 0);
		this->colors.emplace_back(255, 176, 0);
		this->colors.emplace_back(255, 192, 0);
		this->colors.emplace_back(255, 208, 0);
		this->colors.emplace_back(255, 224, 0);
		this->colors.emplace_back(255, 240, 0);
		this->colors.emplace_back(255, 255, 0);
		this->colors.emplace_back(224, 255, 0);
		this->colors.emplace_back(192, 255, 0);
		this->colors.emplace_back(160, 255, 0);
		this->colors.emplace_back(128, 255, 0);
		this->colors.emplace_back(96, 255, 0);
		this->colors.emplace_back(64, 255, 0);
		this->colors.emplace_back(32, 255, 0);
		this->colors.emplace_back(32, 255, 0);
		this->colors.emplace_back(0, 255, 0);
		this->colors.emplace_back(0, 255, 36);
		this->colors.emplace_back(0, 255, 73);
		this->colors.emplace_back(0, 255, 109);
		this->colors.emplace_back(0, 255, 146);
		this->colors.emplace_back(0, 255, 182);
		this->colors.emplace_back(0, 255, 219);
		this->colors.emplace_back(0, 255, 255);
		this->colors.emplace_back(0, 227, 255);
		this->colors.emplace_back(0, 198, 255);
		this->colors.emplace_back(0, 170, 255);
		this->colors.emplace_back(0, 142, 255);
		this->colors.emplace_back(0, 113, 255);
		this->colors.emplace_back(0, 85, 255);
		this->colors.emplace_back(0, 56, 255);
		this->colors.emplace_back(0, 28, 255);
		this->colors.emplace_back(0, 0, 255);
		this->colors.emplace_back(32, 0, 255);
		this->colors.emplace_back(64, 0, 255);
		this->colors.emplace_back(96, 0, 255);
		this->colors.emplace_back(128, 0, 255);
		this->colors.emplace_back(160, 0, 255);
		this->colors.emplace_back(192, 0, 255);
		this->colors.emplace_back(224, 0, 255);
		this->colors.emplace_back(255, 0, 255);
		this->colors.emplace_back(255, 32, 255);
		this->colors.emplace_back(255, 64, 255);
		this->colors.emplace_back(255, 96, 255);
		this->colors.emplace_back(255, 128, 255);
		this->colors.emplace_back(255, 160, 255);
		this->colors.emplace_back(255, 192, 255);
		this->colors.emplace_back(255, 224, 255);
		this->colors.emplace_back(255, 255, 255);
		this->colors.emplace_back(255, 224, 224);
		this->colors.emplace_back(255, 192, 192);
		this->colors.emplace_back(255, 160, 160);
		this->colors.emplace_back(255, 128, 128);
		this->colors.emplace_back(255, 96, 96);
		this->colors.emplace_back(255, 64, 64);
		this->colors.emplace_back(255, 32, 32);
	}

}
