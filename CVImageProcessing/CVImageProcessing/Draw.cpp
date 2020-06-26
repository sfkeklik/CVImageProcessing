
#include <windows.h>
#include <math.h>


void drawCircle(int x, int y, int radius, int width, BYTE* raw_intensity) {



	for (float angle = 0; angle <= 360;) {

		raw_intensity[y * 512 + x] = 0;
		float x1 = x - cos(angle)*radius - 1;
		float y1 = y - sin(angle)*radius - 1;


		int pixelLocation = y1 * width + x1;


		raw_intensity[pixelLocation] = BYTE(255);
		angle += 0.1;

	}



}


void drawCircle2(int x, int y, int radius, int width, BYTE* display_image) {


	for (float angle = 0; angle <= 360;) {

		display_image[y * 512 + x] = 0;
		float x1 = x - cos(angle)*radius - 1;
		float y1 = y - sin(angle)*radius - 1;


		int pixelLocation = y1 * width + x1;


		display_image[pixelLocation] = BYTE(255);
		angle += 0.1;

	}


}