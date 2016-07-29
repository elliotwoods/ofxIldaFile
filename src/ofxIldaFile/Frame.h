#pragma once

#include "Records.h"

#include "ofRectangle.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace ofxIlda {
	class Frame : ofBaseDraws {
		public:
			enum Format : uint8_t {
				Format_0 = 0, // 3D coordinates with indexed color
				Format_1 = 1, // 2D coordinates with indexed color
				Format_2 = 2, // Color palette
				Format_4 = 4, // 3D coordinates with true color
				Format_5 = 5  // 2D coordinates with true color
			};

			struct Header {
				char title[4] = { 'I', 'L', 'D', 'A' }; // "ILDA"
				uint8_t reserved1[3] = { 0, 0 }; // Reserved
				Format format; // Format Code
				char name[8] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }; // Frame or Color Palette Name
				char companyName[8] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }; // Company Name
				uint16_t recordCount = 0; // Number of Records
				uint16_t frameNumber = 0; // Frame or Color Palette Number
				uint16_t totalFrames = 1; // Total Frames in Sequence or 0
				uint8_t projectorNumber = 0; // Projector Number
				uint8_t reserved2 = 0;

				void swapEndian();
			};

			Frame();
			void setHeader(const Header &);
			const Header & getHeader() const;

			virtual void readRecords(istream &, size_t numberOfRecords) = 0; // returns number of records written
			virtual size_t writeRecords(ostream &) const = 0;

			virtual void draw() const = 0;
			void draw(const ofRectangle & bounds, bool flipY = true) const;

			//--
			//ofBaseDraws
			//--
			//
			void draw(float x, float y, float w, float h) const override;
			float getHeight() const override;
			float getWidth() const override;
			//
			//--

	protected:
			Header header;
	};

	template<typename RecordType>
	class Frame_ : public Frame {
	public:
		typedef RecordType Record;

		const vector<Record> & getRecords() const;

		const Record & getRecord(size_t index) const;
		void addRecord(const Record &);

		void readRecords(istream &, size_t numberOfRecords) override;
		size_t writeRecords(ostream &) const override; // returns number of records written
	protected:
		void updateHeader();
		vector<Record> records;
	};

	// 3D Coordinates with Indexed Color
	class Frame_Format0 : public Frame_<Records::Format0> {
	public:
		void draw() const override;
	};

	// 2D Coordinates with Indexed Color
	class Frame_Format1 : public Frame_<Records::Format1> {
	public:
		void draw() const override;
	};

	// Color Palette
	class Frame_Format2 : public Frame_<Records::Format2> {
	public:
		void draw() const override;
	};

	// 3D Coordinates with True Color
	class Frame_Format4 : public Frame_<Records::Format4> {
	public:
		void draw() const override;
	};

	// 2D Coordinates with True Color
	class Frame_Format5 : public Frame_<Records::Format5> {
	public:
		void draw() const override;
	};
}