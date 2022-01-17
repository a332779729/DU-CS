

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>	// open()
#include <unistd.h>	// pread()
#include <stdio.h>	// printf()
#include <stdint.h>	// uint16_t
#include <string.h>	// strncmp()
#include <stdlib.h>	// malloc()

#define DEBUG

#ifdef DEBUG
	#define debugp printf
#else
	#define debugp //
#endif


typedef enum {
	R_CHANNEL, G_CHANNEL, B_CHANNEL,
	RG_CHANNELS, GB_CHANNELS, RB_CHANNELS,
	GR_CHANNELS, BG_CHANNELS, BR_CHANNELS,
	RGB_CHANNELS, GBR_CHANNELS, GRB_CHANNELS,
	BGR_CHANNELS, RBG_CHANNELS, BRG_CHANNELS
} hiding_way;

const char *way_name[15] = {
	"r", "g", "b",
	"rg", "gb", "rb", "gr", "bg", "br",
	"rgb", "gbr", "grb", "bgr", "rbg", "brg"
};

typedef struct __attribute__((packed)) {
	char padding0[18];
	uint32_t width;
	uint32_t height;
	char padding1[2];
	uint16_t bpp;		// bits per pixel.
} translater_bmp_header;

typedef struct {
	uint32_t width;
	uint32_t height;
	uint16_t bpp;		// bytes per pixel.
	uint32_t aligned_width;	// bytes per row.
	char **pixels;
	char *filename;
} image;

char *get_n_hiding_bytes(image *img, int n_bytes, hiding_way way)
{
	uint32_t h = img->height;
	uint32_t w = img->width;
	uint16_t bpp = img->bpp;
	char **pixels = img->pixels;
	int x, y, r, g, b;
	int bpp_is_4 = bpp == 3 ? 0 : 1;

	int bit_index = 0;
	int end_index = n_bytes * 8;

	char *top_n_bytes = NULL;

	if (way < RG_CHANNELS && n_bytes > h * w) {
		goto out;
	} else if (way < RGB_CHANNELS && n_bytes > h * w * 2 / 8) {
		goto out;
	} else if (n_bytes > h * w * 3 / 8) {
		goto out;
	}

	top_n_bytes = malloc(n_bytes);
	for (x = 0; x < n_bytes; x++) {
		top_n_bytes[x] = 0;
	}

	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++) {
			r = pixels[y][x * bpp + bpp_is_4 + 2] & 0x01;
			g = pixels[y][x * bpp + bpp_is_4 + 1] & 0x01;
			b = pixels[y][x * bpp + bpp_is_4 + 0] & 0x01;

			switch (way) {
			case R_CHANNEL:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= r;
				if (bit_index++ == end_index)
					goto out;
				break;
			case G_CHANNEL:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= g;
				if (bit_index++ == end_index)
					goto out;
				break;
			case B_CHANNEL:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= b;
				if (bit_index++ == end_index)
					goto out;
				break;
			case RG_CHANNELS:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= r;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= g;
				bit_index += 2;
				if (bit_index == end_index)
					goto out;
				break;
			case GB_CHANNELS:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= g;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= b;
				bit_index += 2;
				if (bit_index == end_index)
					goto out;
				break;
			case RB_CHANNELS:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= r;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= b;
				bit_index += 2;
				if (bit_index == end_index)
					goto out;
				break;
			case GR_CHANNELS:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= g;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= r;
				bit_index += 2;
				if (bit_index == end_index)
					goto out;
				break;
			case BG_CHANNELS:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= b;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= g;
				bit_index += 2;
				if (bit_index == end_index)
					goto out;
				break;
			case BR_CHANNELS:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= b;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= r;
				bit_index += 2;
				if (bit_index == end_index)
					goto out;
				break;
			case RGB_CHANNELS:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= r;
				if (bit_index++ == end_index)
					goto out;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= g;
				if (bit_index++ == end_index)
					goto out;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= b;
				if (bit_index++ == end_index)
					goto out;
				break;
			case GBR_CHANNELS:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= g;
				if (bit_index++ == end_index)
					goto out;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= b;
				if (bit_index++ == end_index)
					goto out;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= r;
				if (bit_index++ == end_index)
					goto out;
				break;
			case GRB_CHANNELS:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= g;
				if (bit_index++ == end_index)
					goto out;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= r;
				if (bit_index++ == end_index)
					goto out;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= b;
				if (bit_index++ == end_index)
					goto out;
				break;
			case BGR_CHANNELS:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= b;
				if (bit_index++ == end_index)
					goto out;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= g;
				if (bit_index++ == end_index)
					goto out;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= r;
				if (bit_index++ == end_index)
					goto out;
				break;
			case RBG_CHANNELS:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= r;
				if (bit_index++ == end_index)
					goto out;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= b;
				if (bit_index++ == end_index)
					goto out;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= g;
				if (bit_index++ == end_index)
					goto out;
				break;
			case BRG_CHANNELS:
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= b;
				if (bit_index++ == end_index)
					goto out;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= r;
				if (bit_index++ == end_index)
					goto out;
				top_n_bytes[bit_index / 8] <<= 1;
				top_n_bytes[bit_index / 8] |= g;
				if (bit_index++ == end_index)
					goto out;
				break;
			default:
				goto out;
			}
		}
	}

out:
	return top_n_bytes;
}

int get_max_count_hiding_bytes(image *img, hiding_way way)
{
	int h = img->height;
	int w = img->width;

	if (way < RG_CHANNELS) {
		return h * w / 8;
	} else if (way < RGB_CHANNELS) {
		return h * w * 2 / 8;
	} else {
		return h * w * 3 / 8;
	}
}

void try_get_hiding_jpg(image *img, hiding_way way)
{
	const char JPG_FOOTER[2] = {0xFF, 0xD9};

	int max_count_hiding_bytes = get_max_count_hiding_bytes(img, way);
	char *max_hiding_bytes = get_n_hiding_bytes(img, max_count_hiding_bytes, way);
	int i, finded;
	char *hiding_file_name = malloc(32);

	max_count_hiding_bytes -= 1;
	finded = 0;
	for (i = 2; i < max_count_hiding_bytes; i++) {
		if (max_hiding_bytes[i] == JPG_FOOTER[0]
			&& max_hiding_bytes[i + 1] == JPG_FOOTER[1]) {
			finded = 1;
			break;
		}
	}

	sprintf(hiding_file_name, "%s-%s%s", img->filename, way_name[way], ".jpg");

	if (finded) {
		printf("%s, from 0 -> %d\n", hiding_file_name, i + 1);
	} else {
		printf("Not finded.\n");
	}
}

void try_get_hiding_bmp(image *img, hiding_way way)
{
	int max_count_hiding_bytes = get_max_count_hiding_bytes(img, way);
	char *max_hiding_bytes = get_n_hiding_bytes(img, max_count_hiding_bytes, way);
	int i, finded;
	char *hiding_file_name = malloc(32);

	int bmp_size = max_hiding_bytes[2]; // in bytes.

	sprintf(hiding_file_name, "%s-%s%s", img->filename, way_name[way], ".bmp");
	printf("%s, from 0 -> %d\n", hiding_file_name, bmp_size);
}

void try_get_hiding_docx(image *img, hiding_way way)
{
	const char DOCX_FOOTER[4] = {0x50, 0x4B, 0x05, 0x06};

	int max_count_hiding_bytes = get_max_count_hiding_bytes(img, way);
	char *max_hiding_bytes = get_n_hiding_bytes(img, max_count_hiding_bytes, way);
	int i, finded;
	char *hiding_file_name = malloc(32);

	max_count_hiding_bytes -= 3;
	finded = 0;
	for (i = 2; i < max_count_hiding_bytes; i++) {
		if (max_hiding_bytes[i] == DOCX_FOOTER[0]
			&& max_hiding_bytes[i + 1] == DOCX_FOOTER[1]
			&& max_hiding_bytes[i + 2] == DOCX_FOOTER[2]
			&& max_hiding_bytes[i + 3] == DOCX_FOOTER[3]) {
			finded = 1;
			break;
		}
	}

	sprintf(hiding_file_name, "%s-%s%s", img->filename, way_name[way], ".docx");

	if (finded) {
		printf("%s, from 0 -> %d\n", hiding_file_name, i + 3);
	} else {
		printf("Not finded.\n");
	}
}

void try_get_hiding_pdf(image *img, hiding_way way)
{
	const char DOCX_FOOTER[5] = {'%', '%', 'E', 'O', 'F'};

	int max_count_hiding_bytes = get_max_count_hiding_bytes(img, way);
	char *max_hiding_bytes = get_n_hiding_bytes(img, max_count_hiding_bytes, way);
	int i, finded;
	char *hiding_file_name = malloc(32);

	max_count_hiding_bytes -= 4;
	finded = 0;
	for (i = 2; i < max_count_hiding_bytes; i++) {
		if (max_hiding_bytes[i] == DOCX_FOOTER[0]
			&& max_hiding_bytes[i + 1] == DOCX_FOOTER[1]
			&& max_hiding_bytes[i + 2] == DOCX_FOOTER[2]
			&& max_hiding_bytes[i + 3] == DOCX_FOOTER[3]
			&& max_hiding_bytes[i + 4] == DOCX_FOOTER[4]) {
			finded = 1;
			break;
		}
	}

	sprintf(hiding_file_name, "%s-%s%s", img->filename, way_name[way], ".pdf");

	if (finded) {
		printf("%s, from 0 -> %d\n", hiding_file_name, i + 3);
	} else {
		printf("Not finded.\n");
	}
}

void try_get_hiding_mp3(image *img, hiding_way way)
{
	// TODO
}

const unsigned char HEADER_JPG[3] = {0xFF, 0xD8, 0xFF};
const unsigned char HEADER_BMP[2] = {0x42, 0x4D};
const unsigned char HEADER_DOCX[8] = {0x50, 0x4B, 0x03, 0x04, 0x14, 0x00, 0x06, 0x00};
const unsigned char HEADER_PDF[4] = {0x25, 0x50, 0x44, 0x46};
const unsigned char HEADER_MP3[3] = {0x49, 0x44, 0x33};

void check_top_8_bytes(unsigned char *top_8_bytes, image *img, hiding_way way)
{
	debugp("DEBUG: %3s: ", way_name[way]);
	for (int i = 0; i < 8; i++) {
		debugp("%2x ", top_8_bytes[i]);
	}
	debugp("\n");

	if (strncmp(top_8_bytes, HEADER_JPG, sizeof(HEADER_JPG)) == 0) {
		debugp("DEBUG: Try to get a hiding jpn.\n");
		try_get_hiding_jpg(img, way);

	} else if (strncmp(top_8_bytes, HEADER_BMP, sizeof(HEADER_BMP)) == 0) {
		debugp("DEBUG: Try to get a hiding bmp.\n");
		try_get_hiding_bmp(img, way);

	} else if (strncmp(top_8_bytes, HEADER_DOCX, sizeof(HEADER_DOCX)) == 0) {
		debugp("DEBUG: Try to get a hiding docx.\n");
		try_get_hiding_docx(img, way);

	} else if (strncmp(top_8_bytes, HEADER_PDF, sizeof(HEADER_PDF)) == 0) {
		debugp("DEBUG: Try to get a hiding pdf.\n");
		try_get_hiding_pdf(img, way);

	} else if (strncmp(top_8_bytes, HEADER_MP3, sizeof(HEADER_MP3)) == 0) {
		debugp("DEBUG: Try to get a hiding mp3.\n");
		try_get_hiding_mp3(img, way);
	}
}

int testing_all_possibles(image *img)
{
	char *top_8_bytes = NULL;
	hiding_way all_ways[15] = {
		R_CHANNEL, G_CHANNEL, B_CHANNEL,
		RG_CHANNELS, GB_CHANNELS, RB_CHANNELS,
		GR_CHANNELS, BG_CHANNELS, BR_CHANNELS,
		RGB_CHANNELS, GBR_CHANNELS, GRB_CHANNELS,
		BGR_CHANNELS, RBG_CHANNELS, BRG_CHANNELS
	};
	int i = 0;

	for (i = 0; i < 15; i++) {
		top_8_bytes = get_n_hiding_bytes(img, 8, all_ways[i]);
		check_top_8_bytes(top_8_bytes, img, all_ways[i]);
	}

	return 0;
}

// Make sure the length of name_to is bigger than name_froms'.
void filename_copy(char *name_to, char *name_from)
{
	int i;

	if (name_to == NULL || name_from == NULL)
		return;

	for (i = 0; ; i++) {
		if (name_from[i] == '\0') {
			name_to[i] = '\0';
			break;
		}
		name_to[i] = name_from[i];
	}
}

void remove_extension(char *filename, int length)
{
	int i;

	for (i = 0; i < length; i++) {
		if (filename[i] == '\0') {
			break;
		} else if (filename[i] == '.') {
			filename[i] = '\0';
		}
	}
}

int main(int argc, char **argv)
{
	char *target_bmp_name;
	int fd;
	int n_readed;
	image *img;
	int y, height, aligned_width;
	off_t fd_offset;

	if (argc > 1) {
		target_bmp_name = argv[1];
	} else {
		target_bmp_name = "lena0.bmp";
	}

	fd = open(target_bmp_name, O_RDONLY);
	if (fd < 0) {
		printf("open() error!\n");
		return -1;
	}

	translater_bmp_header *header = malloc(sizeof(*header));
	n_readed = pread(fd, header, sizeof(*header), 0);
	if (n_readed != sizeof(*header)) {
		printf("ERROR: pread() failed!\n");
		return -2;
	}

	img = malloc(sizeof(*img));
	img->width = header->width;
	img->height = header->height;
	img->bpp = header->bpp / 8;	// bits => bytes.
	img->aligned_width = img->width * img->bpp;

	img->filename = malloc(32);
	filename_copy(img->filename, target_bmp_name);
	remove_extension(img->filename, 32);

	height = img->height;
	aligned_width = img->aligned_width;
	fd_offset = 54;
	img->pixels = malloc(height * sizeof(char *));
	for (y = height - 1; y >= 0; y--) {
		img->pixels[y] = malloc(aligned_width);
		n_readed = pread(fd, img->pixels[y], aligned_width, fd_offset);
		if (n_readed != aligned_width) {
			printf("Error: pread() failed!\n");
			return -2;
		}
		fd_offset += aligned_width;
	}

	testing_all_possibles(img);

	// TODO: memory free.
	return 0;
}
