#include "Sequence.h"

#include <fstream>
#include "ofUtils.h"

namespace ofxIldaFile {
	//----------
	void Sequence::load(const string & filename) {
		try {
			ifstream file;
			file.open(ofToDataPath(filename), ios::in | ios::binary);
			if (!file) {
				throw(std::exception());
			}

			this->frames.clear();

			while (!file.eof()) {
				//try and read the header
				ofxIldaFile::Frame::Header header;
				file.read( (char*) & header, sizeof(header));

				//now swap the endian for > 8bit values (what were ILDA thinking??)
				header.swapEndian();

				//check that all the bytes of header read successfully
				if (!file) {
					throw(std::out_of_range::exception());
				}

				if (header.recordCount == 0) {
					//it's the end of the file (according to ILDA spec)
					break;
				}
				else {
					//it's a frame
					shared_ptr<Frame> frame;

					switch (header.format) {
					case Frame::Format_0:
						frame = make_shared<Frame_Format0>();
						break;
					case Frame::Format_1:
						frame = make_shared<Frame_Format1>();
						break;
					case Frame::Format_2:
						frame = make_shared<Frame_Format2>();
						break;
					case Frame::Format_4:
						frame = make_shared<Frame_Format4>();
						break;
					case Frame::Format_5:
						frame = make_shared<Frame_Format5>();
						break;
					default:
						throw std::out_of_range::exception();
					}

					frame->setHeader(header);
					frame->readRecords(file, header.recordCount);

					this->frames.push_back(frame);
				}
			}

			file.close();
		}
		catch (std::exception e) {
			ofLogError("ofxIldaFile::File::load") << "Failed : " << e.what();
		}
	}

	//----------
	void Sequence::save(const string & filename) const {
		try {
			ofstream file;
			file.open(ofToDataPath(filename).c_str(), ios::out | ios::binary | ios::trunc);
			if (!file.is_open()) {
				throw(std::exception("Cannot open file for writing"));
			}

			//write frames
			for (auto & frame : this->frames) {
				frame->writeHeader(file, this->frames.size());
				frame->writeRecords(file);
			}

			//write empty frame at end
			{
				auto endFrame = Frame_Format0();
				endFrame.writeHeader(file, this->frames.size());
			}
			
			file.close();
		}
		catch (std::exception e) {
			ofLogError("ofxIldaFile::File::save") << "Failed : " << e.what();
		}
	}

	//----------
	void Sequence::draw(float x, float y, float w, float h) const {
		for (auto frame : this->frames) {
			frame->draw(x, y, w, h);
		}
	}

	//----------
	float Sequence::getHeight() const {
		return 1.0f;
	}

	//----------
	float Sequence::getWidth() const {
		return 1.0f;
	}

	//----------
	std::vector<shared_ptr<ofxIldaFile::Frame>> Sequence::getFrames() {
		return this->frames;
	}

	//----------
	const std::vector<shared_ptr<ofxIldaFile::Frame>> Sequence::getFrames() const {
		return this->frames;
	}

	//----------
	void Sequence::addFrame(shared_ptr<Frame> frame) {
		this->frames.push_back(frame);
	}

	//----------
	size_t Sequence::size() const {
		return this->frames.size();
	}
}