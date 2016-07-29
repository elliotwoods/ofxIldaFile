#pragma once

#include <stdint.h>

static int16_t changeEndianness16(int16_t val)
{
	return (val << 8) |          // left-shift always fills with zeros
		((val >> 8) & 0x00ff); // right-shift sign-extends, so force to zero
}

static uint16_t changeEndianness16U(uint16_t val)
{
	return (val << 8) |          // left-shift always fills with zeros
		((val >> 8) & 0x00ff); // right-shift sign-extends, so force to zero
}

static void swapEndian(int16_t & value) {
	value = changeEndianness16(value);
}

static void swapEndian(uint16_t & value) {
	value = changeEndianness16U(value);
}