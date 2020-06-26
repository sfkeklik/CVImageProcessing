#include <math.h>
#include <iomanip>
#include <windows.h>
#include "EdgeDetection.h"
#define PI 3.14159265359

int* sobel(BYTE* raw_intensity, int height, int width, int* sobelMagnitude, float* sobelOrientation) {

	int* sobelX = new int[(height - 2)*(width - 2)];
	int* sobelY = new int[(height - 2)*(width - 2)];


	int* sobelMaskX = new int[9];
	sobelMaskX[0] = -1; sobelMaskX[1] = 0; sobelMaskX[2] = 1;
	sobelMaskX[3] = -2; sobelMaskX[4] = 0; sobelMaskX[5] = 2;
	sobelMaskX[6] = -1; sobelMaskX[7] = 0; sobelMaskX[8] = 1;
	
	int* sobelMaskY = new int[9];
	sobelMaskY[0] = -1; sobelMaskY[1] = -2; sobelMaskY[2] = -1;
	sobelMaskY[3] = 0; sobelMaskY[4] = 0; sobelMaskY[5] = 0;
	sobelMaskY[6] = 1; sobelMaskY[7] = 2; sobelMaskY[8] = 1;

	
	
	for(int row = 1; row < height - 1; row++)
		for (int col = 1; col < width - 1; col++) {

			int rawPos = row * width + col; // raw_intensity image position
			int sobelPos = (row - 1)*(width - 2) + col - 1; // sobelMasked image position

			sobelX[sobelPos] = raw_intensity[rawPos - width - 1] * sobelMaskX[0] +
							 raw_intensity[rawPos - width]     * sobelMaskX[1] +
							 raw_intensity[rawPos - width + 1] * sobelMaskX[2] +
							 raw_intensity[rawPos - 1]		   * sobelMaskX[3] +
							 raw_intensity[rawPos]             * sobelMaskX[4] +
							 raw_intensity[rawPos + 1]         * sobelMaskX[5] +
							 raw_intensity[rawPos + width - 1] * sobelMaskX[6] +
							 raw_intensity[rawPos + width]	   * sobelMaskX[7] +
							 raw_intensity[rawPos + width + 1] * sobelMaskX[8];

			sobelY[sobelPos] = raw_intensity[rawPos - width - 1] * sobelMaskY[0] +
							raw_intensity[rawPos - width]	  * sobelMaskY[1] +
							raw_intensity[rawPos - width + 1] * sobelMaskY[2] +
							raw_intensity[rawPos - 1]		  * sobelMaskY[3] + 
							raw_intensity[rawPos]			  * sobelMaskY[4] +
							raw_intensity[rawPos + 1]		  * sobelMaskY[5] +
							raw_intensity[rawPos + width - 1] * sobelMaskY[6] +
							raw_intensity[rawPos + width]	  * sobelMaskY[7] +
							raw_intensity[rawPos + width + 1] * sobelMaskY[8] ;

			sobelMagnitude[sobelPos] = abs(sobelX[sobelPos]) + abs(sobelY[sobelPos]);
			
			sobelOrientation[sobelPos] =  atan2(-sobelY[sobelPos] , sobelX[sobelPos]) * 180 / PI; // - y yapýlabilir

			

		}


	return sobelMagnitude;

}


BYTE* gaussianFilter(BYTE* raw_intensity, int height, int width) {
	
	int* filteredImage = new int[height*width];
	BYTE* gaussianImage = new BYTE[height*width];

	//Padding with unfiltered pixels
	for (int row = height - 2 ; row < height; row++)
		for (int col = 0; col < width; col++) {
			int rawPos = row * width + col; // raw_intensity image position
			gaussianImage[rawPos] = raw_intensity[rawPos];
		}

	for (int row = 0; row < 2; row++)
		for (int col = 0; col < width; col++) {
			int rawPos = row * width + col; // raw_intensity image position
			gaussianImage[rawPos] = raw_intensity[rawPos];
		}

	for (int col = 0; col < 2; col++)
		for (int row = 0; row < height; row++){
			int rawPos = row * width + col; // raw_intensity image position
			gaussianImage[rawPos] = raw_intensity[rawPos];
		}


	for (int col = width-2; col < width; col++)
		for (int row = 0; row < height; row++) {
			int rawPos = row * width + col; // raw_intensity image position
			gaussianImage[rawPos] = raw_intensity[rawPos];
		}




	// sum of mask values = 273
	int* gaussianMask = new int[25];
	gaussianMask[0] = 1;  gaussianMask[1] = 4;   gaussianMask[2] = 7;   gaussianMask[3] = 4;   gaussianMask[4] = 1;
	gaussianMask[5] = 4;  gaussianMask[6] = 16;  gaussianMask[7] = 26;  gaussianMask[8] = 16;  gaussianMask[9] = 4;
	gaussianMask[10] = 7; gaussianMask[11] = 26; gaussianMask[12] = 41; gaussianMask[13] = 26; gaussianMask[14] = 7;
	gaussianMask[15] = 4; gaussianMask[16] = 16; gaussianMask[17] = 26; gaussianMask[18] = 16; gaussianMask[19] = 4;
	gaussianMask[20] = 1; gaussianMask[21] = 4;  gaussianMask[22] = 7;  gaussianMask[23] = 4;  gaussianMask[24] = 1;
	



	for (int row = 2; row < height - 2; row++)
		for (int col = 2; col < width - 2; col++) {


			int rawPos = row * width + col; // raw_intensity image position
			

			filteredImage[rawPos] =

				raw_intensity[rawPos - 2 * width - 2] * gaussianMask[0] +
				raw_intensity[rawPos - 2 * width - 1] * gaussianMask[1] +
				raw_intensity[rawPos - 2 * width] * gaussianMask[2] +
				raw_intensity[rawPos - 2 * width + 1] * gaussianMask[3] +
				raw_intensity[rawPos - 2 * width + 2] * gaussianMask[4] +

				raw_intensity[rawPos - width - 2] * gaussianMask[5] +
				raw_intensity[rawPos - width - 1] * gaussianMask[6] +
				raw_intensity[rawPos - width] * gaussianMask[7] +
				raw_intensity[rawPos - width + 1] * gaussianMask[8] +
				raw_intensity[rawPos - width + 2] * gaussianMask[9] +


				raw_intensity[rawPos - 2] * gaussianMask[10] +
				raw_intensity[rawPos - 1] * gaussianMask[11] +
				raw_intensity[rawPos] * gaussianMask[12] +
				raw_intensity[rawPos + 1] * gaussianMask[13] +
				raw_intensity[rawPos + 2] * gaussianMask[14] +

				raw_intensity[rawPos + width - 2] * gaussianMask[15] +
				raw_intensity[rawPos + width - 1] * gaussianMask[16] +
				raw_intensity[rawPos + width] * gaussianMask[17] +
				raw_intensity[rawPos + width + 1] * gaussianMask[18] +
				raw_intensity[rawPos + width + 2] * gaussianMask[19] +

				raw_intensity[rawPos + 2 * width - 2] * gaussianMask[20] +
				raw_intensity[rawPos + 2 * width - 1] * gaussianMask[21] +
				raw_intensity[rawPos + 2 * width] * gaussianMask[22] +
				raw_intensity[rawPos + 2 * width + 1] * gaussianMask[23] +
				raw_intensity[rawPos + 2 * width + 2] * gaussianMask[24];

			filteredImage[rawPos] /= 273.0;
			gaussianImage[rawPos] = filteredImage[rawPos];
		}

	
	return gaussianImage;
}

float* gaussianFilter(float* raw_intensity, int height, int width) {
	int* filteredImage = new int[height*width];
	float* gaussianImage = new float[height*width];

	//Padding with unfiltered pixels
	for (int row = height - 2; row < height; row++)
		for (int col = 0; col < width; col++) {
			int rawPos = row * width + col; // raw_intensity image position
			gaussianImage[rawPos] = raw_intensity[rawPos];
		}

	for (int row = 0; row < 2; row++)
		for (int col = 0; col < width; col++) {
			int rawPos = row * width + col; // raw_intensity image position
			gaussianImage[rawPos] = raw_intensity[rawPos];
		}

	for (int col = 0; col < 2; col++)
		for (int row = 0; row < height; row++) {
			int rawPos = row * width + col; // raw_intensity image position
			gaussianImage[rawPos] = raw_intensity[rawPos];
		}


	for (int col = width - 2; col < width; col++)
		for (int row = 0; row < height; row++) {
			int rawPos = row * width + col; // raw_intensity image position
			gaussianImage[rawPos] = raw_intensity[rawPos];
		}




	// sum of mask values = 273
	int* gaussianMask = new int[25];
	gaussianMask[0] = 1;  gaussianMask[1] = 4;   gaussianMask[2] = 7;   gaussianMask[3] = 4;   gaussianMask[4] = 1;
	gaussianMask[5] = 4;  gaussianMask[6] = 16;  gaussianMask[7] = 26;  gaussianMask[8] = 16;  gaussianMask[9] = 4;
	gaussianMask[10] = 7; gaussianMask[11] = 26; gaussianMask[12] = 41; gaussianMask[13] = 26; gaussianMask[14] = 7;
	gaussianMask[15] = 4; gaussianMask[16] = 16; gaussianMask[17] = 26; gaussianMask[18] = 16; gaussianMask[19] = 4;
	gaussianMask[20] = 1; gaussianMask[21] = 4;  gaussianMask[22] = 7;  gaussianMask[23] = 4;  gaussianMask[24] = 1;




	for (int row = 2; row < height - 2; row++)
		for (int col = 2; col < width - 2; col++) {


			int rawPos = row * width + col; // raw_intensity image position


			filteredImage[rawPos] =

				raw_intensity[rawPos - 2 * width - 2] * gaussianMask[0] +
				raw_intensity[rawPos - 2 * width - 1] * gaussianMask[1] +
				raw_intensity[rawPos - 2 * width] * gaussianMask[2] +
				raw_intensity[rawPos - 2 * width + 1] * gaussianMask[3] +
				raw_intensity[rawPos - 2 * width + 2] * gaussianMask[4] +

				raw_intensity[rawPos - width - 2] * gaussianMask[5] +
				raw_intensity[rawPos - width - 1] * gaussianMask[6] +
				raw_intensity[rawPos - width] * gaussianMask[7] +
				raw_intensity[rawPos - width + 1] * gaussianMask[8] +
				raw_intensity[rawPos - width + 2] * gaussianMask[9] +


				raw_intensity[rawPos - 2] * gaussianMask[10] +
				raw_intensity[rawPos - 1] * gaussianMask[11] +
				raw_intensity[rawPos] * gaussianMask[12] +
				raw_intensity[rawPos + 1] * gaussianMask[13] +
				raw_intensity[rawPos + 2] * gaussianMask[14] +

				raw_intensity[rawPos + width - 2] * gaussianMask[15] +
				raw_intensity[rawPos + width - 1] * gaussianMask[16] +
				raw_intensity[rawPos + width] * gaussianMask[17] +
				raw_intensity[rawPos + width + 1] * gaussianMask[18] +
				raw_intensity[rawPos + width + 2] * gaussianMask[19] +

				raw_intensity[rawPos + 2 * width - 2] * gaussianMask[20] +
				raw_intensity[rawPos + 2 * width - 1] * gaussianMask[21] +
				raw_intensity[rawPos + 2 * width] * gaussianMask[22] +
				raw_intensity[rawPos + 2 * width + 1] * gaussianMask[23] +
				raw_intensity[rawPos + 2 * width + 2] * gaussianMask[24];

			filteredImage[rawPos] /= 273.0;
			gaussianImage[rawPos] = filteredImage[rawPos];
		}


	return gaussianImage;
}



int* nonMaximaSuppression(int height, int width, int* sobelMagnitude, float* sobelOrientation) {
	
	int* nonMaxSupImage = new int[(height - 2)*(width - 2)];
	
	for (int row = 0; row < (height - 2); row++)
		for (int col = 0; col < (width - 2); col++) {
			int pos = row * (width - 2) + col; //Image Position
			nonMaxSupImage[pos] = sobelMagnitude[pos];
		}

	for (int row = 0; row < height-2; row++)
		for (int col = 0; col < width-2; col++) {

			int pos = row * (width-2) + col; //Image Position


			//Non Maxima Suppression
			if ((isgreater(sobelOrientation[pos], -22.5) && islessequal(sobelOrientation[pos], 22.5)) ||
				(isgreater(sobelOrientation[pos], -180.0) && islessequal(sobelOrientation[pos], -157.5)) ||
				(isgreater(sobelOrientation[pos], 157.5) && islessequal(sobelOrientation[pos], 180.0))) { // 0 and 180 angle 

				if((pos + 1 > 0) && (pos + 1 < (width - 2)*(height - 2)))
					if (sobelMagnitude[pos] < sobelMagnitude[pos + 1]) {
					
						nonMaxSupImage[pos] = 0;
					}



				if((pos - 1 > 0) && (pos - 1 < (width - 2)*(height - 2)))
					if (sobelMagnitude[pos] < sobelMagnitude[pos - 1]) {
						nonMaxSupImage[pos] = 0;
					} 

			}
			else if ((isgreater(sobelOrientation[pos], 22.5) && islessequal(sobelOrientation[pos], 67.5)) ||
					(isgreater(sobelOrientation[pos], -157.5) && islessequal(sobelOrientation[pos], -112.5))) { // 45 and -135 angle

				if((pos - (width - 2) + 1 > 0) && (pos - (width - 2) + 1 < (width - 2)*(height - 2)))
					if (sobelMagnitude[pos] < sobelMagnitude[pos - (width - 2 ) + 1]) {
						nonMaxSupImage[pos] = 0;
					}
				if((pos + (width - 2) - 1 > 0) && (pos + (width - 2) - 1 < (width - 2)*(height - 2)))
					if (sobelMagnitude[pos] < sobelMagnitude[pos + (width - 2) - 1]) {
						nonMaxSupImage[pos] = 0;
					}

			}
			else if ((isgreater(sobelOrientation[pos], 67.5) && islessequal(sobelOrientation[pos], 112.5)) ||
					(isgreater(sobelOrientation[pos], -112.5) && islessequal(sobelOrientation[pos], -67.5))) {// 90 and -90 angle

				if((pos + (width - 2) > 0) && (pos + (width - 2) < (width - 2)*(height - 2)))
					if (sobelMagnitude[pos] < sobelMagnitude[pos + (width - 2)]) {
						nonMaxSupImage[pos] = 0;
					}

				if((pos - (width - 2) > 0) && (pos - (width - 2) < (width - 2)*(height - 2)))
					if (sobelMagnitude[pos] < sobelMagnitude[pos - (width - 2)]) {
						nonMaxSupImage[pos] = 0;
					}

			}
			else if ((isgreater(sobelOrientation[pos], 112.5) && islessequal(sobelOrientation[pos], 157.5)) ||
					(isgreater(sobelOrientation[pos], -67.5) && islessequal(sobelOrientation[pos], -22.5))) { // 135 and -45 angle

				if((pos + (width - 2) + 1 > 0) && (pos + (width - 2) + 1 < (width - 2)*(height - 2)))
					if (sobelMagnitude[pos] < sobelMagnitude[pos + (width - 2) + 1]) {
						nonMaxSupImage[pos] = 0;
					}

				if((pos - (width - 2) - 1 > 0) && (pos - (width - 2) - 1 < (width - 2)*(height - 2)))
					if (sobelMagnitude[pos] < sobelMagnitude[pos - (width - 2) - 1]) {
						nonMaxSupImage[pos] = 0;
					}
			}


		}

	return nonMaxSupImage;
}



int hysteresisThreshold2(int pos, int width, int height,int* normalizedMagnitude, float* sobelOrientation, int& recursionCount ) {
	
	if (recursionCount >= 5000) {
		recursionCount = 0;
		
		return 1;
	}

	if (normalizedMagnitude[pos] == 0 ) {
		
		return 0;

	}
	else if (normalizedMagnitude[pos] == 1) {
		
		return 1;
	}
	else {
		
		float* edgeDirection = new float;
		*edgeDirection = 0;
		if (isless(sobelOrientation[pos] - 90.0, -180.0)) {
			*edgeDirection = 360 - abs(sobelOrientation[pos] - 90.0);
		}
		else *edgeDirection = sobelOrientation[pos] - 90.0;


		if ((pos - 1 > 0) && (pos - 1 < (width - 2)*(height - 2)) && 
			(isgreater(*edgeDirection, -22.5) && islessequal(*edgeDirection, 22.5))) {// 0 angle

			if (normalizedMagnitude[pos - 1] == 1) {
				normalizedMagnitude[pos] = 1;
				delete edgeDirection;
				return 1;
			}
			else if (normalizedMagnitude[pos - 1] == 0) {

				normalizedMagnitude[pos] = 0;
				delete edgeDirection;
				return 0;
			}
			else  {
				recursionCount++;
				delete edgeDirection;
				normalizedMagnitude[pos] = hysteresisThreshold2((pos - 1),width, height, normalizedMagnitude, sobelOrientation, recursionCount);
				return normalizedMagnitude[pos];
			}

		}
		else if ((pos + 1 > 0) && (pos + 1 < (width - 2)*(height - 2)) && ((isgreater(*edgeDirection, -180.0) && isless(*edgeDirection, -157.5)) ||
				(isgreater(*edgeDirection, 157.5) && islessequal(*edgeDirection, 180.0)))) { // 180 angle

			if (normalizedMagnitude[pos + 1] == 1) {
				normalizedMagnitude[pos] = 1;
				delete edgeDirection;
				return 1;
			}
			else if (normalizedMagnitude[pos + 1] == 0) {

				normalizedMagnitude[pos] = 0;
				delete edgeDirection;
				return 0;

			}
			else {
				recursionCount++;
				delete edgeDirection;
				normalizedMagnitude[pos] = hysteresisThreshold2((pos + 1), width, height, normalizedMagnitude,sobelOrientation, recursionCount);
				return normalizedMagnitude[pos];
			}

		}
		else if ((pos - (width - 2) + 1 > 0) && (pos - (width - 2) + 1 < (width - 2)*(height - 2)) && 
			(isgreater(*edgeDirection, 22.5) && islessequal(*edgeDirection, 67.5))) { // 45 angle

			if (normalizedMagnitude[pos - (width - 2) + 1] == 1) {
				normalizedMagnitude[pos] = 1;
				delete edgeDirection;
				return 1;
			}
			else if (normalizedMagnitude[pos - (width - 2) + 1] == 0) {

				normalizedMagnitude[pos] = 0;
				delete edgeDirection;
				return 0;
			}
			else {
				recursionCount++;
				delete edgeDirection;
				normalizedMagnitude[pos] = hysteresisThreshold2((pos - (width - 2) + 1), width, height, normalizedMagnitude, sobelOrientation, recursionCount);

				return normalizedMagnitude[pos];
			}

		}
		else if ((pos + (width - 2) + 1 > 0) && (pos + (width - 2) + 1 < (width - 2)*(height - 2)) && 
				(isgreater(*edgeDirection, -67.5) && islessequal(*edgeDirection, -22.5))) { // -45 angle

			

			if (normalizedMagnitude[pos + (width - 2) + 1] == 1) {
				normalizedMagnitude[pos] = 1;
				delete edgeDirection;
				return 1;
			}
			else if (normalizedMagnitude[pos + (width - 2) + 1] == 0) {
				delete edgeDirection;
				normalizedMagnitude[pos] = 0;
				return 0;

			}
			else{
				
				recursionCount++;
				delete edgeDirection;
				normalizedMagnitude[pos] = hysteresisThreshold2((pos + (width - 2) + 1), width, height,normalizedMagnitude, sobelOrientation, recursionCount);
				return normalizedMagnitude[pos];
			}

		}
		else if ((pos - (width - 2) > 0) && (pos - (width - 2) < (width - 2)*(height - 2)) &&
			(isgreater(*edgeDirection, 67.5) && islessequal(*edgeDirection, 112.5))) { // 90 angle

			

			if ( normalizedMagnitude[pos - (width - 2)] == 1) {
				delete edgeDirection;
				normalizedMagnitude[pos] = 1;
				return 1;
			}
			else if ( normalizedMagnitude[pos - (width - 2)] == 0) {
				delete edgeDirection;
				normalizedMagnitude[pos] = 0;
				return 0;

			}
			else {
				recursionCount++;
				delete edgeDirection;
				normalizedMagnitude[pos] = hysteresisThreshold2((pos - (width - 2)), width, height, normalizedMagnitude, sobelOrientation, recursionCount);
				return normalizedMagnitude[pos];

			}

		}
		else if ((pos + (width - 2) > 0) && (pos + (width - 2) < (width - 2)*(height - 2)) && 
				(isgreater(*edgeDirection, -112.5) && islessequal(*edgeDirection, -67.5))) { // -90 angle


			if (normalizedMagnitude[pos + (width - 2)] == 1) {
				delete edgeDirection;
				normalizedMagnitude[pos] = 1;
				return 1;
			}
			else if (normalizedMagnitude[pos + (width - 2)] == 0) {
				delete edgeDirection;
				normalizedMagnitude[pos] = 0;
				return 0;

			}
			else {
				recursionCount++;
				delete edgeDirection;
				normalizedMagnitude[pos] = hysteresisThreshold2((pos + (width - 2)), width, height, normalizedMagnitude, sobelOrientation, recursionCount);
				return normalizedMagnitude[pos];
			}

		}
		else if ((pos - (width - 2) - 1 > 0) && (pos - (width - 2) - 1 < (width - 2)*(height - 2)) && 
				(isgreater(*edgeDirection, 112.5) && islessequal(*edgeDirection, 157.5))) {// 135 angle

			

			if (normalizedMagnitude[pos - (width - 2) - 1] == 1) {
				delete edgeDirection;
				normalizedMagnitude[pos] = 1;
				return 1;
			}
			else if (normalizedMagnitude[pos - (width - 2) - 1] == 0) {
				delete edgeDirection;
				normalizedMagnitude[pos] = 0;
				return 0;

			}
			else {
				recursionCount++;
				delete edgeDirection;
				normalizedMagnitude[pos] = hysteresisThreshold2((pos - (width - 2) - 1), width, height, normalizedMagnitude, sobelOrientation, recursionCount);
				return normalizedMagnitude[pos];
			}





		}
		else if ((pos + (width - 2) - 1 > 0) && (pos + (width - 2) - 1 < (width - 2)*(height - 2)) && 
				(isgreater(*edgeDirection, -157.5) && islessequal(*edgeDirection, -112.5))) { // -135 angle

			if (normalizedMagnitude[pos + (width - 2) - 1] == 1) {
				normalizedMagnitude[pos] = 1;
				delete edgeDirection;
				return 1;
			}
			else if (normalizedMagnitude[pos + (width - 2) - 1] == 0) {
				delete edgeDirection;
				normalizedMagnitude[pos] = 0;
				return 0;

			}
			else {
				recursionCount++;
				delete edgeDirection;
				normalizedMagnitude[pos] = hysteresisThreshold2((pos + (width - 2) - 1), width, height, normalizedMagnitude, sobelOrientation, recursionCount);
				return normalizedMagnitude[pos];
			}

		}
		


	}
}
	

float* zScoreCalculate(int height, int width, int* sobelMagnitude, float* sobelOrientation) {
	//Double Thresholds Starting

	unsigned int sumOfMagnitude = 0;
	int memberCount = 0;
	for (int row = 0; row < height - 2; row++)
		for (int col = 0; col < width - 2; col++) {

			int pos = row * (width - 2) + col;

			sumOfMagnitude += sobelMagnitude[pos];
			if (sobelMagnitude[pos] != 0) {
				memberCount++;
			}
		}
	double meanMagnitude = sumOfMagnitude / memberCount;

	sumOfMagnitude = 0;
	for (int row = 0; row < height - 2; row++)
		for (int col = 0; col < width - 2; col++) {

			int pos = row * (width - 2) + col;

			sumOfMagnitude += pow(sobelMagnitude[pos] - meanMagnitude, 2);

		}

	double derivationMagnitude = sqrt(sumOfMagnitude / memberCount);


	float* zScoreMagnitude = new float[(height - 2)*(width - 2)];

	

	for (int row = 0; row < height - 2; row++)
		for (int col = 0; col < width - 2; col++) {

			int pos = row * (width - 2) + col;

			zScoreMagnitude[pos] = (sobelMagnitude[pos] - (float)meanMagnitude) / (float)derivationMagnitude; // zScore yerine baþka bir normalizasyon iþlemi yap.
			int a = 0;
		}

	return zScoreMagnitude;
}

void hysteresisThreshold(int pos, int width, int height, int* normalizedMagnitude, int& recursionCount) {


	/*if (recursionCount >= 1000) {
		recursionCount = 0;
		return ;
	}*/

	for (int i = -1; i <= 1; i++) 
		for (int j = -1; j <= 1; j++) {
			if((pos + i * (width - 2) + j > 0) && (pos + i * (width - 2) + j < (width - 2)*(height - 2)))
				if (normalizedMagnitude[pos + i * (width - 2) + j] == 2) { // '2' pointing weak edges
					
					normalizedMagnitude[pos + i * (width - 2) + j] = 1;
					recursionCount++;
					hysteresisThreshold(pos + i * (width - 2) + j, width, height, normalizedMagnitude, recursionCount);
				}
		}


}

int* cannyEdgeDetector(BYTE* raw_intensity, int height, int width, int* sobelMagnitude, float* sobelOrientation) {

	int* cannyEdgeImage = new int[(height-2)*(width-2)];

	//Non Maxima Suppression Finished
	int* nonMaxImage;
	nonMaxImage = nonMaximaSuppression(height, width, sobelMagnitude, sobelOrientation);

	

	//finding max member of sobelMagnitude
	int max = sobelMagnitude[0];
	for (int row = 0; row < height - 2; row++)
		for (int col = 0; col < width - 2; col++) {

			int pos = row * (width - 2) + col;
			if (sobelMagnitude[pos] > max) {

				max = sobelMagnitude[pos];
			}
			
		}

	float lowThreshold = 0.3;
	float highThreshold = 0.2;
	highThreshold = max * highThreshold;
	lowThreshold = highThreshold * lowThreshold;



	int lowCount = 0;
	int highCount = 0;
	int weakCount = 0;



	

	int* doubleThreshold = new int[(height - 2)*(width - 2)];
	for (int row = 0; row < height - 2; row++)
		for (int col = 0; col < width - 2; col++) {

			int pos = row * (width - 2) + col;

			doubleThreshold[pos] = nonMaxImage[pos];

			if (islessequal(doubleThreshold[pos], lowThreshold)) {

				doubleThreshold[pos] = 0;
				lowCount++;
			}
			else if (isgreaterequal(doubleThreshold[pos], highThreshold)) {

				doubleThreshold[pos] = 1;
				highCount++;
			}
			else {
				doubleThreshold[pos] = 2; // weak pixels
				weakCount++;
			}
		}



	


	

	
	int* hysteresisImage = new int[(height - 2)*(width - 2)];


	int* strongEdgePos = new int[highCount];
	int* weakEdgePos = new int[weakCount];
	int* lowEdgePos = new int[lowCount];

	int strongEdgeIndex = 0;
	int weakEdgeIndex = 0;
	int lowEdgeIndex = 0;

	for (int row = 0; row < (height - 2); row++)
		for (int col = 0; col < (width - 2); col++) {

			int pos = row * (width - 2) + col;

			if (doubleThreshold[pos] == 0) {
				
				lowEdgePos[lowEdgeIndex] = pos;
				lowEdgeIndex++;

			}else if (doubleThreshold[pos] == 1) {

				strongEdgePos[strongEdgeIndex] = pos;
				strongEdgeIndex++;

			}else if (doubleThreshold[pos] == 2) {

				weakEdgePos[weakEdgeIndex] = pos;
				weakEdgeIndex++;

			}

			hysteresisImage[pos] = doubleThreshold[pos];
		}

	int recursionCount = 0;


	for (int i = 0; i < highCount; i++) {

		int pos = strongEdgePos[i];
		hysteresisThreshold(pos, width, height, hysteresisImage, recursionCount);
		
	}

	for (int i = 0; i < weakCount; i++) {

		int pos = weakEdgePos[i];
		if (hysteresisImage[pos] == 2)
			hysteresisImage[pos] = 0;

	}



	//for (int row = 0; row < (height - 2) ; row++)
	//	for (int col = 0; col < (width - 2) ; col++) {

	//		int pos = row * (width - 2) + col;
	//		 
	//		if (doubleThreshold[pos] == 1) {
	//			hysteresisThreshold(pos, width, height, doubleThreshold, hysteresisImage, recursionCount);
	//		}

	//		/*	if (doubleThreshold[pos] == 2) {
	//			hysteresisThreshold2(pos, width, height, hysteresisImage, sobelOrientation, recursionCount);
	//		}*/
	//		
	//		

	//
	//	}

	



	for (int row = 0; row < height - 2; row++)
		for (int col = 0; col < width - 2; col++) {
			int pos = row * (width - 2) + col;

			cannyEdgeImage[pos] = hysteresisImage[pos];

				
		}

	return cannyEdgeImage;
}




int angleQuantization(float angle) {
	int quantizationedAngle;

	quantizationedAngle = angle;

	/*if (quantizationedAngle % 10 <= 5) {
		quantizationedAngle /= 10;
		quantizationedAngle *= 10;
	}else if (quantizationedAngle % 10 > 5) {
		quantizationedAngle += (10 - quantizationedAngle % 10);
	}*/
	if (quantizationedAngle % 1 > 0) {
		quantizationedAngle /= 1;
		quantizationedAngle *= 1;
	}
	return quantizationedAngle;
}


int distanceQuantization(float distance) {

	int quantizationedDistance;

	quantizationedDistance = distance;

	if (quantizationedDistance % 3 > 0) {
		quantizationedDistance /= 3;
		quantizationedDistance *= 3;
	}
	return quantizationedDistance;

}

float* distanceQuantization(float* distance,int height, int width) {

	gaussianFilter(distance, height - 2, width - 2);
	return gaussianFilter(distance, height-2,width-2);

}


int* houghTransformWithOrientation(int* edgeImage, int height, int width, float* sobelOrientation, int lineCount, int& pixelLocationOfLineLenght,int*& mostSignificantLine) {

	float* distance = new float[(height-2)*(width-2)];


	// Max Distance Lenght
	float maxDistance = round(sqrt((height - 2)*(height - 2)+ (width - 2)* (width - 2)));

	// this hough matrix's X axis is Orientation , Y axis is Distance
	// pos = 
	
	//row is Distance, col is Orientation
	int* houghSpace = new int[maxDistance * 180];
	for (int i = 0; i < maxDistance * 180; i++) { // memset(houghSpace,0);
		houghSpace[i] = 0;
	}

	int* houghPosPointer = new int[(height - 2)*(width - 2)]; //its points Hough Space Position to Edge Image Pos
	for(int row = 0; row < height-2; row++)
		for (int col = 0; col < width - 2; col++) {
			int edgePos = row * (width - 2) + col; //Edge Image pos
			if (edgeImage[edgePos] == 255) {

				// burada quantalama yapmak lazým hem distance için hem açý için

				distance[edgePos] = round(abs(row * sin(-1*sobelOrientation[edgePos] * PI / 180.0) + col * cos(sobelOrientation[edgePos] * PI / 180.0))); // calculate d = r*sin(theta) + c*cos(theta) with round
				distance[edgePos] = distanceQuantization(distance[edgePos]);
				if (isgreater(-1*sobelOrientation[edgePos], 90)) {
					int houghPos = distance[edgePos] * 180 + angleQuantization(round(-1*sobelOrientation[edgePos] - 90));
					houghSpace[houghPos]++;
					houghPosPointer[edgePos] = houghPos;
				}
				else if (isless(-1*sobelOrientation[edgePos], -90)) {
					int houghPos = distance[edgePos] * 180 + angleQuantization(round(-1*sobelOrientation[edgePos] + 270));
					houghSpace[houghPos]++;
					houghPosPointer[edgePos] = houghPos;
				}
				else {
					int houghPos = distance[edgePos] * 180 + angleQuantization(round(-1*sobelOrientation[edgePos] + 90));
					houghSpace[houghPos]++;
					houghPosPointer[edgePos] = houghPos;
				}
			}
			else {
				distance[edgePos] = -1; // meaning its not an edge
				houghPosPointer[edgePos] = -1; //meaning its not an edge
			}

		}



	//distanceQuantization(distance, height, width);
	//distanceQuantization(distance, height, width);

	//for (int row = 0; row < height - 2; row++)
	//	for (int col = 0; col < width - 2; col++) {
	//		int edgePos = row * (width - 2) + col; //Edge Image pos
	//		if (edgeImage[edgePos] == 255) {

	//			if (isgreater(sobelOrientation[edgePos], 90)) {
	//				int houghPos = distance[edgePos] * 180 + angleQuantization(round(sobelOrientation[edgePos] - 90));
	//				houghSpace[houghPos]++;
	//				houghPosPointer[edgePos] = houghPos;
	//			}
	//			else if (isless(sobelOrientation[edgePos], -90)) {
	//				int houghPos = distance[edgePos] * 180 + angleQuantization(round(sobelOrientation[edgePos] + 270));
	//				houghSpace[houghPos]++;
	//				houghPosPointer[edgePos] = houghPos;
	//			}
	//			else {
	//				int houghPos = distance[edgePos] * 180 + angleQuantization(round(sobelOrientation[edgePos] + 90));
	//				houghSpace[houghPos]++;
	//				houghPosPointer[edgePos] = houghPos;
	//			}
	//		}
	//		else {
	//			distance[edgePos] = -1; // meaning its not an edge
	//			houghPosPointer[edgePos] = -1; //meaning its not an edge
	//		}


	//	}





	//finding Most significant n lines
	mostSignificantLine = new int[lineCount];
	for (int i = 0; i < lineCount; i++)
		mostSignificantLine[i] = 0;


	float thresholdRatio = 0.2;
	int threshold = 0;
	int max = 0;
	for (int line = 0; line < lineCount; line++) {
		for (int dis = 0; dis < maxDistance; dis++) {
			for (int angle = -90; angle < 90; angle++) {

				int houghPos = dis * 180 + (angle + 90);
				if (houghSpace[houghPos] > max && houghSpace[houghPos] > threshold) {
					max = houghSpace[houghPos];
					mostSignificantLine[line] = houghPos; // We find Hough Positions, we will use for draw line 
				}

			}
		}

		//if (line == 0) { // Setting Threshold for to be Line 
		//	threshold = thresholdRatio * max;
		//}
		houghSpace[mostSignificantLine[line]] = 0; // we need to set zero for find second biggest number.
		max = 0;
	}


	int linePixelCount = 0;
	for (int line = 0; line < lineCount; line++) {
		for (int i = 0; i < (height - 2)*(width - 2); i++) {
			if (houghPosPointer[i] == mostSignificantLine[line]) {
				linePixelCount++;
			}
		}
	}

	int* linePixelLocation = new int[linePixelCount];
	pixelLocationOfLineLenght = linePixelCount;
	int pixelLocationIndex = 0 ;
	for (int line = 0; line < lineCount; line++) {
		for (int edgePos = 0; edgePos < (height - 2)*(width - 2); edgePos++) {
			if (houghPosPointer[edgePos] == mostSignificantLine[line]) {
				linePixelLocation[pixelLocationIndex] = edgePos;
				pixelLocationIndex++;
			}
		}
	}




	return linePixelLocation;
}


