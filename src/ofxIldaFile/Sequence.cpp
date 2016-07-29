#include "Sequence.h"

#include <fstream>
#include "ofUtils.h"

namespace ofxIlda {
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
				ofxIlda::Frame::Header header;
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
			ofLogError("ofxIlda::File::load") << "Failed : " << e.what();
		}
	}

	//----------
	void Sequence::save(const string & filename) const {
		try {
			ofstream file;
			file.open(filename, ios::out | ios::binary);
			if (!file) {
				throw(std::exception());
			}

			//write frames
			for (auto & frame : this->frames) {
				auto header = frame->getHeader();
				header.totalFrames = this->frames.size();

				//now swap the endian for > 8bit values (what were ILDA thinking??)
				header.swapEndian();

				file.write((char*)& header, sizeof(header));
				frame->writeRecords(file);
			}

			//write empty frame at end
			{
				auto endFrame = Frame_Format0();
				endFrame.writeRecords(file);
			}
			
		}
		catch (std::exception e) {
			ofLogError("ofxIlda::File::save") << "Failed : " << e.what();
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
}