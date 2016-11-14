#include "Frame.h"
#include "ColorPalette.h"

#include "ofPolyline.h"
#include "ofGraphics.h"
#include "ofMesh.h"

namespace ofxIldaFile {
#pragma mark Frame::Header
	//----------
	void Frame::Header::swapEndian() {
		::swapEndian(this->recordCount);
		::swapEndian(this->frameNumber);
		::swapEndian(this->totalFrames);
	}

#pragma mark Frame
	//----------
	Frame::Frame() {

	}

	//----------
	void Frame::setHeader(const Header & header) {
		this->header = header;
	}

	//----------
	const Frame::Header & Frame::getHeader() const {
		return header;
	}

	//----------
	void Frame::buildHeader() {
		this->header.format = this->getFormat();
		this->header.recordCount = (uint16_t) this->size();
	}

	//----------
	void Frame::writeHeader(ostream & file, size_t totalFrames) {
		this->buildHeader();
		auto header = this->getHeader();
		header.totalFrames = static_cast<uint16_t>(totalFrames);

		//now swap the endian for > 8bit values (what were ILDA thinking??)
		header.swapEndian();
		file.write((char*)& header, sizeof(header));
	}

	//----------
	void Frame::draw(const ofRectangle & bounds, bool flipY /*= true*/) const {
		ofPushMatrix();
		{
			//translate to center rectangle
			ofTranslate(bounds.getCenter());

			//scale to rectangle size
			ofScale(bounds.width / 2.0f, bounds.height / 2.0f);

			//scale out the limits
			ofScale(1.0f / float(1 << 15),
				1.0f / float(1 << 15),
				1.0f / float(1 << 15));

			//flip y
			if (flipY) {
				ofScale(1.0f, -1.0f, 1.0f);
			}

			//draw the lines
			this->draw();
		}
		ofPopMatrix();
	}

	//----------
	void Frame::draw(float x, float y, float w, float h) const {
		this->draw(ofRectangle(x, y, w, h));
	}

	//----------
	float Frame::getHeight() const {
		return 1;
	}

	//----------
	float Frame::getWidth() const {
		return 1;
	}

#pragma mark Frame_
	//----------
	template<typename RecordType>
	const vector<RecordType> & Frame_<RecordType>::getRecords() const {
		return this->records;
	}

	//----------
	template<typename RecordType>
	const RecordType & Frame_<RecordType>::getRecord(size_t index) const {
		return this->records[index];
	}

	//----------
	template<typename RecordType>
	void Frame_<RecordType>::addRecord(const Record & record) {
		this->records.push_back(record);
		this->buildHeader();
	}

	//----------
	template<typename RecordType>
	void Frame_<RecordType>::readRecords(istream & stream, size_t numberOfRecords) {
		for (int i = 0; i < numberOfRecords; i++) {
			Record record;
			stream.read((char*)&record, sizeof(Record));
			record.swapEndian();
			this->addRecord(record);
		}
	}

	//----------
	template<typename RecordType>
	size_t Frame_<RecordType>::writeRecords(ostream & stream) const{
		for (auto record : this->records) {
			record.swapEndian();
			stream.write((char*)&record, sizeof(Record));
		}
		return records.size();
	}

#pragma mark Frame_Format0
	//----------
	void Frame_Format0::draw() const {
		ofPolyline line;
		bool isBlanking = true;
		size_t currentActiveColor = -1;

		ofPushStyle();
		{
			for (const auto & record : this->records) {
				bool lineStarts = false;
				bool lineEnds = false;
				bool switchColor = false;
				bool draws = true;

				//color change
				if (record.colorIndex != currentActiveColor) {
					switchColor = true;
				}

				//blanking
				if (isBlanking) {
					if (record.statusCode & Records::StatusCode::Blanking) {
						//still blanking
						draws = false;
					}
					else {
						//not blanking any more
						lineStarts = true;
						isBlanking = false;
					}
				}
				else {
					if (record.statusCode & Records::StatusCode::Blanking) {
						//start blanking
						lineEnds = true;
						draws = false;
						isBlanking = true;
					}
					else {
						//still not blanking
					}
				}

				//end of frame
				if (record.statusCode & Records::StatusCode::LastPoint || &record == &records.back()) {
					lineEnds = true;
				}

				auto vertex = ofVec3f(record.x, record.y, record.z);

				if (lineEnds) {
					if (line.size() == 1) {
						ofMesh point;
						point.addVertex(line.getVertices()[0]);
						point.drawVertices();
					}
					else {
						line.draw();
					}
				}

				if (switchColor) {
					auto color = ColorPalette::X().getColor(record.colorIndex);
					ofSetColor(color);
					currentActiveColor = record.colorIndex;
				}

				if (lineStarts) {
					line.clear();
				}

				if (draws) {
					line.addVertex(vertex);
				}
			}
		}
		ofPopStyle();
	}

	//----------
	void Frame_Format1::draw() const {
		ofPolyline line;
		bool isBlanking = true;
		size_t currentActiveColor = -1;

		ofPushStyle();
		{
			for (const auto & record : this->records) {
				bool lineStarts = false;
				bool lineEnds = false;
				bool switchColor = false;
				bool draws = true;

				//color change
				if (record.colorIndex != currentActiveColor) {
					switchColor = true;
				}

				//blanking
				if (isBlanking) {
					if (record.statusCode & Records::StatusCode::Blanking) {
						//still blanking
						draws = false;
					}
					else {
						//not blanking any more
						lineStarts = true;
						isBlanking = false;
					}
				}
				else {
					if (record.statusCode & Records::StatusCode::Blanking) {
						//start blanking
						lineEnds = true;
						draws = false;
						isBlanking = true;
					}
					else {
						//still not blanking
					}
				}

				//end of frame
				if (record.statusCode & Records::StatusCode::LastPoint) {
					break;
				}

				auto vertex = ofVec3f(record.x, record.y, 0);

				if (lineEnds) {
					if (line.size() == 1) {
						ofMesh point;
						point.addVertex(line.getVertices()[0]);
						point.drawVertices();
					}
					else {
						line.draw();
					}
				}

				if (switchColor) {
					ofSetColor(ColorPalette::X().getColor(record.colorIndex));
				}

				if (lineStarts) {
					line.clear();
				}

				if (draws) {
					line.addVertex(vertex);
				}
			}
		}
		ofPopStyle();
	}

	//----------
	void Frame_Format2::draw() const {
		ColorPalette::X().clear();
		for (auto & record : this->records) {
			ColorPalette::X().addRecord(record);
		}
	}

	//----------
	void Frame_Format4::draw() const {
		ofMesh lines;
		lines.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINE_STRIP);

		for (auto & record : this->records) {
			ofColor color = record.getColor();
			
			if (record.statusCode & Records::StatusCode::Blanking) {
				color.a = 0;
			}

			lines.addVertex(ofVec3f(record.x, record.y, record.z));
			lines.addColor(color);
		}
		lines.draw();
	}

	//----------
	void Frame_Format5::draw() const {
		ofMesh lines;
		lines.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINE_STRIP);

		for (auto & record : this->records) {
			ofColor color = record.getColor();

			if (record.statusCode & Records::StatusCode::Blanking) {
				color.a = 0;
			}

			lines.addVertex(ofVec3f(record.x, record.y, 0.0f));
			lines.addColor(color);
		}
		lines.draw();
	}
}

template class ofxIldaFile::Frame_<ofxIldaFile::Records::Format0>;
template class ofxIldaFile::Frame_<ofxIldaFile::Records::Format1>;
template class ofxIldaFile::Frame_<ofxIldaFile::Records::Format2>;
template class ofxIldaFile::Frame_<ofxIldaFile::Records::Format4>;
template class ofxIldaFile::Frame_<ofxIldaFile::Records::Format5>;
