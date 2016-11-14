#pragma once

#include "Frame.h"

#include <vector>
#include <string>
#include <memory>

using namespace std;

namespace ofxIldaFile {
	class Sequence : ofBaseDraws {
	public:
		void load(const string & filename);
		void save(const string & filename) const;

		void draw(float x, float y, float w, float h) const override;
		float getHeight() const override;
		float getWidth() const override;

		vector<shared_ptr<Frame>> getFrames();
		const vector<shared_ptr<Frame>> getFrames() const;
		void addFrame(shared_ptr<Frame>);

		size_t size() const;
	protected:
		vector<shared_ptr<Frame>> frames;
	};
}