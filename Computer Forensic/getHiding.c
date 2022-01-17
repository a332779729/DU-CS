// getHidding.c

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>	// open()
#include <unistd.h>	// pread()
#include <stdio.h>	// printf()
#include <stdint.h>	// uint16_t
#include <string.h>	// strncmp()
#include <stdlib.h>	// malloc()

typedef unsigned char byte;

#define BMP_HEADER_SIZE 54

const byte HEADER_JPG[3] = {0xFF, 0xD8, 0xFF};
const byte HEADER_BMP[2] = {0x42, 0x4D};
const byte HEADER_DOCX[8] = {0x50, 0x4B, 0x03, 0x04, 0x14, 0x00, 0x06, 0x00};
const byte HEADER_PDF[4] = {0x25, 0x50, 0x44, 0x46};
const byte HEADER_MP3[3] = {0x49, 0x44, 0x33};

typedef struct __attribute__((packed)) {
	byte padding0[18];
	uint32_t width;
	uint32_t height;
	byte padding1[2];
	uint16_t bytes_per_pixel;
	uint32_t aligned_width;
} bmp_header_info;

typedef union __attribute__((packed)) {
	byte padding[BMP_HEADER_SIZE];
	bmp_header_info info;
} bmp_header;

typedef enum {
	R_CHANNEL,
	G_CHANNEL,
	B_CHANNEL,
	RG_CHANNELS,
	GB_CHANNELS,
	RB_CHANNELS,
	GR_CHANNELS,
	BG_CHANNELS,
	BR_CHANNELS,
	RGB_CHANNELS,
	GBR_CHANNELS,
	GRB_CHANNELS,
	BGR_CHANNELS,
	RBG_CHANNELS,
	BRG_CHANNELS
} hiding_way;

byte *get_first_n_bytes_from_r_channel(byte *pixels, bmp_header_info *header, int n)
{	
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r = 0;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
			}
			r &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;
			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_g_channel(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r = 0;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 2];
			}
			r &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;
			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_b_channel(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r = 0;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;
			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_rg_channels(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r, g, b;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
				g = pixels[(y * aligned_width + x * bpp) + 1];
				b = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
				g = pixels[(y * aligned_width + x * bpp) + 2];
				b = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			g &= 0x1;
			b &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;

			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= g;

			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_gb_channels(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r, g, b;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
				g = pixels[(y * aligned_width + x * bpp) + 1];
				b = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
				g = pixels[(y * aligned_width + x * bpp) + 2];
				b = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			g &= 0x1;
			b &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= g;

			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= b;

			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_rb_channels(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r, g, b;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
				g = pixels[(y * aligned_width + x * bpp) + 1];
				b = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
				g = pixels[(y * aligned_width + x * bpp) + 2];
				b = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			g &= 0x1;
			b &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;

			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= b;

			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_gr_channels(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r, g, b;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
				g = pixels[(y * aligned_width + x * bpp) + 1];
				b = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
				g = pixels[(y * aligned_width + x * bpp) + 2];
				b = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			g &= 0x1;
			b &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= g;

			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;

			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_bg_channels(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r, g, b;
	byte *first_n_bytes = malloc(n * sizeof(byte));

	for (int j = 0; j < n; j++) {
		first_n_bytes[j] = 0;
	}

	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
				g = pixels[(y * aligned_width + x * bpp) + 1];
				b = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
				g = pixels[(y * aligned_width + x * bpp) + 2];
				b = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			g &= 0x1;
			b &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= b;

			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= g;

			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_br_channels(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r, g, b;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
				g = pixels[(y * aligned_width + x * bpp) + 1];
				b = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
				g = pixels[(y * aligned_width + x * bpp) + 2];
				b = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			g &= 0x1;
			b &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= b;

			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;

			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}


byte *get_first_n_bytes_from_rgb_channels(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r, g, b;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
				g = pixels[(y * aligned_width + x * bpp) + 1];
				b = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
				g = pixels[(y * aligned_width + x * bpp) + 2];
				b = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			g &= 0x1;
			b &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;
			if (bit_index == end_index) {
				goto out;
			}
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= g;
			if (bit_index == end_index) {
				goto out;
			}
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= b;
			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_gbr_channels(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r, g, b;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
				g = pixels[(y * aligned_width + x * bpp) + 1];
				b = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
				g = pixels[(y * aligned_width + x * bpp) + 2];
				b = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			g &= 0x1;
			b &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= g;
			if (bit_index == end_index) {
				goto out;
			}
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= b;
			if (bit_index == end_index) {
				goto out;
			}
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;
			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_grb_channels(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r, g, b;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
				g = pixels[(y * aligned_width + x * bpp) + 1];
				b = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
				g = pixels[(y * aligned_width + x * bpp) + 2];
				b = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			g &= 0x1;
			b &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= g;
			if (bit_index == end_index) {
				goto out;
			}
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;
			if (bit_index == end_index) {
				goto out;
			}
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= b;
			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_bgr_channels(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r, g, b;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
				g = pixels[(y * aligned_width + x * bpp) + 1];
				b = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
				g = pixels[(y * aligned_width + x * bpp) + 2];
				b = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			g &= 0x1;
			b &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= b;
			if (bit_index == end_index) {
				goto out;
			}
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= g;
			if (bit_index == end_index) {
				goto out;
			}
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;
			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_rbg_channels(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r, g, b;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
				g = pixels[(y * aligned_width + x * bpp) + 1];
				b = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
				g = pixels[(y * aligned_width + x * bpp) + 2];
				b = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			g &= 0x1;
			b &= 0x1;
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;
			if (bit_index == end_index) {
				goto out;
			}
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= b;
			if (bit_index == end_index) {
				goto out;
			}
			bit_index += 1;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= g;
			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}

byte *get_first_n_bytes_from_brg_channels(byte *pixels, bmp_header_info *header, int n)
{
	uint32_t height = header->height;
	uint32_t width = header->width;
	uint32_t bpp = header->bytes_per_pixel;
	uint32_t aligned_width = header->aligned_width;

	if (n > height * width * bpp)
		return NULL;
	
	byte r, g, b;
	byte *first_n_bytes = malloc(n * sizeof(byte));
	int bit_index = 0;
	int end_index = n * 8;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (bpp == 3) {
				r = pixels[(y * aligned_width + x * bpp) + 0];
				g = pixels[(y * aligned_width + x * bpp) + 1];
				b = pixels[(y * aligned_width + x * bpp) + 2];
			} else if (bpp == 4) {
				r = pixels[(y * aligned_width + x * bpp) + 1];
				g = pixels[(y * aligned_width + x * bpp) + 2];
				b = pixels[(y * aligned_width + x * bpp) + 3];
			}
			r &= 0x1;
			g &= 0x1;
			b &= 0x1;
			bit_index++;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= b;
			if (bit_index == end_index) {
				goto out;
			}
			bit_index++;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= r;
			if (bit_index == end_index) {
				goto out;
			}
			bit_index++;
			first_n_bytes[bit_index / 8] <<= 1;
			first_n_bytes[bit_index / 8] |= g;
			if (bit_index == end_index) {
				goto out;
			}
		}
	}
out:
	return first_n_bytes;
}


byte *get_n_hiding_bytes(byte *pixels, bmp_header_info *header, int n, hiding_way way)
{
	byte *rt = NULL;
	switch (way) {
		case R_CHANNEL:
			rt = get_first_n_bytes_from_r_channel(pixels, header, n);
			break;
		case G_CHANNEL:
			rt = get_first_n_bytes_from_g_channel(pixels, header, n);
			break;
		case B_CHANNEL:
			rt = get_first_n_bytes_from_b_channel(pixels, header, n);
			break;
		case RG_CHANNELS:
			rt = get_first_n_bytes_from_rg_channels(pixels, header, n);
			break;
		case GB_CHANNELS:
			rt = get_first_n_bytes_from_gb_channels(pixels, header, n);
			break;
		case RB_CHANNELS:
			rt = get_first_n_bytes_from_rb_channels(pixels, header, n);
			break;
		case GR_CHANNELS:
			rt = get_first_n_bytes_from_gr_channels(pixels, header, n);
			break;
		case BG_CHANNELS:
			rt = get_first_n_bytes_from_bg_channels(pixels, header, n);
			break;
		case BR_CHANNELS:
			rt = get_first_n_bytes_from_br_channels(pixels, header, n);
			break;
		case RGB_CHANNELS:
			rt = get_first_n_bytes_from_rgb_channels(pixels, header, n);
			break;
		case GBR_CHANNELS:
			rt = get_first_n_bytes_from_gbr_channels(pixels, header, n);
			break;
		case GRB_CHANNELS:
			rt = get_first_n_bytes_from_grb_channels(pixels, header, n);
			break;
		case BGR_CHANNELS:
			rt = get_first_n_bytes_from_bgr_channels(pixels, header, n);
			break;
		case RBG_CHANNELS:
			rt = get_first_n_bytes_from_rbg_channels(pixels, header, n);
			break;
		case BRG_CHANNELS:
			rt = get_first_n_bytes_from_brg_channels(pixels, header, n);
			break;
		default:
			break;
	}

	return rt;
}

int try_get_hiding_jpg(byte *pixels, bmp_header_info *header, hiding_way way)
{
	const byte FOOTER_JPG[2] = {0xFF, 0xD9};
	uint32_t width = header->width;
	uint32_t count_pixels = header->height * header->width;
	byte *hiding_bytes = NULL;
	uint32_t i = 0;

	hiding_bytes = get_n_hiding_bytes(pixels, header, count_pixels, way);
	if (hiding_bytes == NULL) {
		return -1;
	}

	for (i = 0; i < count_pixels; i++) {
		if (hiding_bytes[i] == FOOTER_JPG[0]
			&& hiding_bytes[i + 1] == FOOTER_JPG[1]) {
			break;
		}
	}

	if (i == count_pixels) {
		return -1;
	} else {
		printf("Get jpg: 0 -> %u\n", i);
	}

	// TODO
	return 0;
}

int try_get_hiding_bmp(byte *pixels, bmp_header_info *header, hiding_way way)
{
	// TODO
	return 0;
}

int try_get_hiding_docx(byte *pixels, bmp_header_info *header, hiding_way way)
{
	// TODO
	return 0;
}

int try_get_hiding_pdf(byte *pixels, bmp_header_info *header, hiding_way way)
{
	// TODO
	return 0;
}

int try_get_hiding_mp3(byte *pixels, bmp_header_info *header, hiding_way way)
{
	// TODO
	return 0;
}

int check_first_8_bytes(byte *first_8_bytes, byte *pixels, bmp_header_info *header, hiding_way way)
{
	if (strncmp(first_8_bytes, HEADER_JPG, sizeof(HEADER_JPG)) == 0) {
		printf("DEBUG: Try to get a hiding jpn.\n");
		try_get_hiding_jpg(pixels, header, way);
	} else if (strncmp(first_8_bytes, HEADER_BMP, sizeof(HEADER_BMP)) == 0) {
		printf("DEBUG: Try to get a hiding bmp.\n");
		try_get_hiding_bmp(pixels, header, way);
	} else if (strncmp(first_8_bytes, HEADER_DOCX, sizeof(HEADER_DOCX)) == 0) {
		printf("DEBUG: Try to get a hiding docx.\n");
		try_get_hiding_docx(pixels, header, way);
	} else if (strncmp(first_8_bytes, HEADER_PDF, sizeof(HEADER_PDF)) == 0) {
		printf("DEBUG: Try to get a hiding pdf.\n");
		try_get_hiding_pdf(pixels, header, way);
	} else if (strncmp(first_8_bytes, HEADER_MP3, sizeof(HEADER_MP3)) == 0) {
		printf("DEBUG: Try to get a hiding mp3.\n");
		try_get_hiding_mp3(pixels, header, way);
	}
	return 0;
}

int test_single_r_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, R_CHANNEL);
	check_first_8_bytes(first_8_bytes, pixels, header, R_CHANNEL);

	return 0;
}

int test_single_g_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, G_CHANNEL);
	check_first_8_bytes(first_8_bytes, pixels, header, G_CHANNEL);
	test_single_r_channel(pixels, header);

	return 0;
}

int test_single_b_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, B_CHANNEL);
	check_first_8_bytes(first_8_bytes, pixels, header, B_CHANNEL);
	test_single_g_channel(pixels, header);

	return 0;
}

int test_rg_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, RG_CHANNELS);
	check_first_8_bytes(first_8_bytes, pixels, header, RG_CHANNELS);
	test_single_b_channel(pixels, header);

	return 0;
}

int test_gb_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, GB_CHANNELS);
	check_first_8_bytes(first_8_bytes, pixels, header, GB_CHANNELS);
	test_rg_channel(pixels, header);

	return 0;
}

int test_rb_channel(byte *pixels, bmp_header_info *header) 
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, RB_CHANNELS);
	check_first_8_bytes(first_8_bytes, pixels, header, RB_CHANNELS);
	test_gb_channel(pixels, header);

	return 0;
}

int test_gr_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, GR_CHANNELS);
	check_first_8_bytes(first_8_bytes, pixels, header, GR_CHANNELS);
	test_rb_channel(pixels, header);

	return 0;
}

int test_bg_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, BG_CHANNELS);
	check_first_8_bytes(first_8_bytes, pixels, header, BG_CHANNELS);
	test_gr_channel(pixels, header);

	return 0;
}

int test_br_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, BR_CHANNELS);
	check_first_8_bytes(first_8_bytes, pixels, header, BR_CHANNELS);
	test_bg_channel(pixels, header);

	return 0;
}

int test_rgb_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, RGB_CHANNELS);
	check_first_8_bytes(first_8_bytes, pixels, header, RGB_CHANNELS);
	test_br_channel(pixels, header);

	return 0;
}

int test_gbr_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, GBR_CHANNELS);
	check_first_8_bytes(first_8_bytes, pixels, header, GBR_CHANNELS);
	test_rgb_channel(pixels, header);

	return 0;
}

int test_grb_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, GRB_CHANNELS);
	check_first_8_bytes(first_8_bytes, pixels, header, GRB_CHANNELS);
	test_gbr_channel(pixels, header);

	return 0;
}

int test_bgr_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, B_CHANNEL);
	check_first_8_bytes(first_8_bytes, pixels, header, B_CHANNEL);
	test_grb_channel(pixels, header);

	return 0;
}

int test_rbg_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, RGB_CHANNELS);
	check_first_8_bytes(first_8_bytes, pixels, header, RGB_CHANNELS);
	test_bgr_channel(pixels, header);

	return 0;
}

int test_brg_channel(byte *pixels, bmp_header_info *header)
{
	byte *first_8_bytes = NULL;

	first_8_bytes = get_n_hiding_bytes(pixels, header, 8, BRG_CHANNELS);
	check_first_8_bytes(first_8_bytes, pixels, header, BRG_CHANNELS);
	test_rbg_channel(pixels, header);

	return 0;
}

int main(int argc, char **argv)
{
	char *target_bmp_path;
	int fd;

	if (argc > 1) {
		target_bmp_path = argv[1];
	} else {
		target_bmp_path = "./lena0.bmp";
	}

	fd = open(target_bmp_path, O_RDONLY);
	if (fd < 0) {
		printf("open() error!\n");
		return -1;
	}

	bmp_header *header = malloc(BMP_HEADER_SIZE);
	bmp_header_info *info = &header->info;
	int n_readed = pread(fd, header, BMP_HEADER_SIZE, 0);
	if (n_readed != BMP_HEADER_SIZE) {
		printf("pread() error!\n");
		return -2;
	}

	info->bytes_per_pixel /= 8;
	if (info->bytes_per_pixel != 3 && info->bytes_per_pixel != 4) {
		printf("Unsupported file types.\n");
		return 0;
	}
	
	uint32_t aligned_width = (info->width * info->bytes_per_pixel + 3) & (~3);
	info->aligned_width = aligned_width;

	uint32_t count = info->height * aligned_width;
	byte *pixels = malloc(count);
	n_readed = pread(fd, pixels, count, BMP_HEADER_SIZE);
	if (n_readed != count) {
		printf("pread() error!\n");
		return -2;
	}

	test_brg_channel(pixels, info);

	close(fd);
	return 0;
}
