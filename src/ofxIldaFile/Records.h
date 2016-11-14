#pragma once

#include "Endian.h"

#include "ofBaseTypes.h"
#include <stdint.h>

namespace ofxIldaFile {
	namespace Records {
		enum StatusCode : uint8_t {

			NoStatus = 0,
			Blanking = 1 << 6,
			LastPoint = 1 << 7,
			BlankingLastPoint = Blanking | LastPoint
		};

		// 3D Coordinates with Indexed Color
		struct Format0 {
			int16_t x = 0;
			int16_t y = 0;
			int16_t z = 0;
			StatusCode statusCode = StatusCode::NoStatus;
			uint8_t colorIndex = 57; // white

			void swapEndian();
		};

		// 2D Coordinates with Indexed Color
		struct Format1 {
			int16_t x = 0;
			int16_t y = 0;
			StatusCode statusCode = StatusCode::NoStatus;
			uint8_t colorIndex = 57;

			void swapEndian();
		};

		// Color Palette
		struct Format2 {
			uint8_t red;
			uint8_t green;
			uint8_t blue;

			void swapEndian();
		};

		// 3D Coordinates with True Color
		struct Format4 {
			int16_t x = 0;
			int16_t y = 0;
			int16_t z = 0;
			StatusCode statusCode = StatusCode::NoStatus;
			uint8_t blue = 255;
			uint8_t green = 255;
			uint8_t red = 255;

			void swapEndian();
			ofColor getColor() const;
		};

		// 2D Coordinates with True Color
		struct Format5 {
			int16_t x = 0;
			int16_t y = 0;
			StatusCode statusCode = StatusCode::NoStatus;
			uint8_t blue = 255;
			uint8_t green = 255;
			uint8_t red = 255;

			void swapEndian();
			ofColor getColor() const;
		};
	}
}