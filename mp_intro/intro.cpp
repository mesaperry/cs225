#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
	cs225::PNG image;
	image.readFromFile(inputFile);
	unsigned width = image.width();
	unsigned height = image.height();
	unsigned adj_height = height/2;
	if (height%2==1) { //if odd
		adj_height -= 1;
	}
	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < adj_height; y++) {
			unsigned oppo_x = width-x-1;
			unsigned oppo_y = height-y-1;

			cs225::HSLAPixel & pixel_1 = image.getPixel(x, y);
			cs225::HSLAPixel & pixel_2 = image.getPixel(oppo_x, oppo_y);
			cs225::HSLAPixel temp = pixel_1;
			pixel_1 = pixel_2;
			pixel_2 = temp;
		}
	}
	image.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
	cs225::PNG png(width, height);
	double hue_bot = 290;
	double hue_top = 30;
	double hue_range = hue_top - hue_bot;
	if (hue_range < 0) {
		hue_range += 360;
	}
	double hue_diff = hue_range / width;

	for (unsigned x = 0; x < width; x++) {
		for (unsigned y = 0; y < height; y++) {
			cs225::HSLAPixel & pixel = png.getPixel(x, y);
			double hue = hue_bot + hue_diff*x;
			if (hue > 360) {
				hue -= 360;
			}
			pixel.h = hue;
			pixel.s = 1;
			pixel.l = .5;
			pixel.a = 1;
		}
	}

	return png;
}
