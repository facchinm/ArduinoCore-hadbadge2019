#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "gloss/mach_defines.h"
#include "gloss/mach_interrupt.h"
#include "gloss/uart.h"
#include <stdio.h>
#include <lcd.h>
#include <sys/types.h>
#include <math.h>
#include <string.h>
#include "tinyusb/src/tusb.h"
#include "usb_descriptors.h"
#include "hexdump.h"
#include "fs.h"
#include "flash.h"
#include "loadapp.h"
#include "gloss/newlib_stubs.h"
#include "lodepng/lodepng.h"
#include "gfx_load.h"
#include "cache.h"
#include "user_memfn.h"
#include "badgetime.h"
#include "api/HardwareSerial.h"
#include "api/Print.h"

#ifdef __cplusplus

#ifndef __ARDUINO_UART_IMPLEMENTATION__
#define __ARDUINO_UART_IMPLEMENTATION__

class SerialUART : public arduino::HardwareSerial {
	public:
		void begin(unsigned long) {
			f = fopen("/dev/ttyUSB", "rw");
		}
		void begin(unsigned long baudrate, uint16_t config) {
			begin(config);
		}
		void end();
		int available(void);
		int peek(void);
		int read(void) {
			char c;
			fread(&c, 1, 1, f);
			return c;
		}
		void flush(void);
		size_t write(uint8_t c) {
			return fwrite(&c, 1, 1, f);
		}
		//size_t write(const uint8_t*, size_t);
		using arduino::Print::write; // pull in write(str) and write(buf, size) from Print
		operator bool();

		FILE* f = NULL;
};

extern SerialUART Serial;

#endif
#endif
