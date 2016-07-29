#pragma once

#include "Frame.h"

#include <vector>
#include <string>
#include <memory>

using namespace std;

namespace ofxIlda {
	class Sequence : ofBaseDraws {
	public:
		void load(const string & filename);
		void save(const string & filename) const;

		void draw(float x, float y, float w, float h) const override;
		float getHeight() const override;
		float getWidth() const override;

	protected:
		vector<shared_ptr<Frame>> frames;
	};
}