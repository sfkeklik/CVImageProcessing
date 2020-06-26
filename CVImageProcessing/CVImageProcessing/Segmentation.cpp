#include <math.h>
#include <windows.h>
#include <time.h>

void kMeansClustering(int* labelHistogram, int* histogram, int& t1X, int& t1Y, int& t2X, int& t2Y) {


	int modifiedT1X = 70;
	int modifiedT1Y = 0;

	int modifiedT2X = 150;
	int modifiedT2Y = 0;

	int sumOfT1LabeledX = 0;
	int sumOfT1LabeledY = 0;

	int sumOfT2LabeledX = 0;
	int sumOfT2LabeledY = 0;

	int countT1 = 0;
	int countT2 = 0;

	while (true) {
		t1X = modifiedT1X;
		t1Y = modifiedT1Y;

		t2X = modifiedT2X;
		t2Y = modifiedT2Y;

		countT1 = 0;
		countT2 = 0;

		sumOfT1LabeledX = 0;
		sumOfT1LabeledY = 0;

		sumOfT2LabeledX = 0;
		sumOfT2LabeledY = 0;

		for (int i = 0; i < 256; i++) {
			if (sqrt(pow(histogram[i] - t1Y, 2) + pow(i - t1X, 2)) < sqrt(pow(histogram[i] - t2Y, 2) + pow(i - t2X, 2))) {
				labelHistogram[i] = t1X;
				sumOfT1LabeledX += i;
				sumOfT1LabeledY += histogram[i];
				countT1++;
			}
			else if (sqrt(pow(histogram[i] - t1Y, 2) + pow(i - t1X, 2)) >= sqrt(pow(histogram[i] - t2Y, 2) + pow(i - t2X, 2))) {
				labelHistogram[i] = t2X;
				sumOfT2LabeledX += i;
				sumOfT2LabeledY += histogram[i];
				countT2++;
			}
		}
		if (countT1 != 0) {
			modifiedT1X = (sumOfT1LabeledX / countT1);
			modifiedT1Y = sumOfT1LabeledY / countT1;
		}
		else {

			modifiedT1X = t1X;
			modifiedT1Y = t1Y;
		}


		if (countT2 != 0) {
			modifiedT2X = (sumOfT2LabeledX / countT2);
			modifiedT2Y = sumOfT2LabeledY / countT2;
		}
		else {
			modifiedT2X = t2X;
			modifiedT2Y = t2Y;
		}

		if ((t1X == modifiedT1X) && (t2X == modifiedT2X) && (t1Y == modifiedT1Y) && (t2Y == modifiedT2Y)) {

			break;
		}

	}




}


void kMeansClustering2(int* labelHistogram, int* histogram, int& k1, int& k2) {


	int newK1Mean = 0;
	int newK2Mean = 0;

	int modifiedK1 = 70;
	int modifiedK2 = 150;

	int sumOfK1Labeled = 0;
	int sumOfK2Labeled = 0;

	int countK1 = 0;
	int countK2 = 0;

	while (true) {

		k1 = modifiedK1;
		k2 = modifiedK2;

		newK1Mean = 0;
		newK2Mean = 0;

		countK1 = 0;
		countK2 = 0;

		sumOfK1Labeled = 0;
		sumOfK2Labeled = 0;


		for (int i = 0; i < 256; i++) {
			if (abs(i - k1) < abs(i - k2)) {
				labelHistogram[i] = k1;
				newK1Mean += i * histogram[i];

				sumOfK1Labeled += histogram[i];
				countK1++;
			}
			else if (abs(i - k1) >= abs(i - k2)) {
				labelHistogram[i] = k2;
				newK2Mean += i * histogram[i];

				sumOfK2Labeled += histogram[i];
				countK2++;
			}
		}
		if (countK1 != 0) {
			newK1Mean = newK1Mean / sumOfK1Labeled;
			modifiedK1 = newK1Mean;
		}
		else {

			modifiedK1 = k1;

		}


		if (countK2 != 0) {
			newK2Mean = newK2Mean / sumOfK2Labeled;
			modifiedK2 = newK2Mean;
		}
		else {
			modifiedK2 = k2;

		}

		if ((k1 == modifiedK1) && (k2 == modifiedK2)) {

			break;
		}

	}



}


int compare(int* distanceKi, int numberOfK) {

	int min = distanceKi[0];
	int minIndex = 0;
	for (int i = 0; i < numberOfK; i++) {
		if (min > distanceKi[i]) {
			min = distanceKi[i];
			minIndex = i;
		}

	}

	return minIndex;
}


int* kMeansClusteringKCluster(int* labelHistogram, int* histogram, int numberOfK) {

	int* k = new int[numberOfK];


	int* kMean = new int[numberOfK];


	int* modifiedK = new int[numberOfK];
	//memset(modifiedK, rand()%256, numberOfK); // Intialized Thresholds. if assing same th value it will be error.

	long* sumOfKLabeled = new long[numberOfK];




	int* countK = new int[numberOfK];


	int* distanceK = new int[256 * numberOfK];
	memset(distanceK, 0, 256 * numberOfK);

	srand(time(NULL));
	for (int i = 0; i < numberOfK; i++) {
		k[i] = 0;
		kMean[i] = 0;
		sumOfKLabeled[i] = 0;
		countK[i] = 0;
		modifiedK[i] = rand() % 256; // Intialized Thresholds. if assing same threshold value it will be error.

		while (histogram[modifiedK[i]] == 0) {
			modifiedK[i] = rand() % 256;
		}


	}


	while (true) {



		for (int j = 0; j < numberOfK; j++) {

			k[j] = modifiedK[j];


			kMean[j] = 0;


			countK[j] = 0;


			sumOfKLabeled[j] = 0;


			for (int i = 0; i < 256; i++) {
				distanceK[256 * j + i] = abs(i - k[j]);
			}

		}

		int* distanceKi = new int[numberOfK]; // distanceKi -> distance Array for i 'th pixel  value

		for (int i = 0; i < 256; i++) {


			for (int j = 0; j < numberOfK; j++) {
				distanceKi[j] = distanceK[256 * j + i]; // distanceKi -> distance Array for i 'th pixel value
			}
			int minIndex = compare(distanceKi, numberOfK); // compare() -> returns index of min distance cluster 
			labelHistogram[i] = k[minIndex];
			kMean[minIndex] += i * histogram[i];
			sumOfKLabeled[minIndex] += histogram[i];
			countK[minIndex]++;

		}

		for (int i = 0; i < numberOfK; i++) {

			if (countK[i] != 0) {
				kMean[i] /= sumOfKLabeled[i];
				modifiedK[i] = kMean[i];
			}
			else {

				modifiedK[i] = k[i];

			}


		}


		boolean breakCondition = true;
		for (int i = 0; i < numberOfK; i++) {
			if ((k[i] == modifiedK[i])) {
				breakCondition = breakCondition && true;
			}
			else {
				breakCondition = breakCondition && false;
			}
		}


		if (breakCondition == true)
			break;

	}


	delete kMean;
	delete modifiedK;
	delete sumOfKLabeled;
	delete distanceK;
	delete countK;

	return k;

}




BYTE* convertToBinary(BYTE* raw_intensity, int lenghtOfPictureArray) {

	BYTE* binaryImage = new BYTE[lenghtOfPictureArray];

	for (int i = 0; i < lenghtOfPictureArray; i++) {

		if (raw_intensity[i] == 255) {

			binaryImage[i] = 1;
		}
		else if (raw_intensity[i] == 0) {
			binaryImage[i] = 0;

		}

	}

	return binaryImage;
}

BYTE* meanFiltering(BYTE* raw_intensity, int height, int width) {

	BYTE* paddedRawImage = new BYTE[(height + 2)*(width + 2)];

	for (int i = 0; i < (height + 2)*(width + 2); i++) paddedRawImage[i] = 0;



	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++) {
			paddedRawImage[(row + 1)*(width + 2) + col + 1] = raw_intensity[row*width + col];
		}



	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++) {

			int rawPos = row * width + col; // raw_intensity image position
			int paddedRawPos = (row + 1)*(width + 2) + col + 1; // paddedRawImage matrix position

			int mean =
				(paddedRawImage[paddedRawPos - (width + 2) - 1] + paddedRawImage[paddedRawPos - (width + 2)] + paddedRawImage[paddedRawPos - (width + 2) + 1] +
					paddedRawImage[paddedRawPos - 1] + paddedRawImage[paddedRawPos] + paddedRawImage[paddedRawPos + 1] +
					paddedRawImage[paddedRawPos + (width + 2) - 1] + paddedRawImage[paddedRawPos + (width + 2)] + paddedRawImage[paddedRawPos + (width + 2) + 1]) / 9;

			raw_intensity[rawPos] = (BYTE)mean;

		}



	return raw_intensity;





}




BYTE* dilation(BYTE* binaryImage, int height, int width) {

	BYTE* paddedBinaryImage = new BYTE[(height + 2)*(width + 2)];

	for (int i = 0; i < (height + 2)*(width + 2); i++) paddedBinaryImage[i] = 0;



	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++) {
			paddedBinaryImage[(row + 1)*(width + 2) + col + 1] = binaryImage[row*width + col];
		}

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++) {

			int binPos = row * width + col; // binary image position
			int paddedBinaryPos = (row + 1)*(width + 2) + col + 1; // paddedBinaryImage matrix position

			if (paddedBinaryImage[paddedBinaryPos] == 1) {

				binaryImage[binPos - width - 1] = 1;
				binaryImage[binPos - width] = 1;
				binaryImage[binPos - width + 1] = 1;

				binaryImage[binPos - 1] = 1;
				binaryImage[binPos + 1] = 1;


				binaryImage[binPos + width - 1] = 1;
				binaryImage[binPos + width] = 1;
				binaryImage[binPos + width + 1] = 1;

			}

		}



	return binaryImage;

}


BYTE* erosion(BYTE* binaryImage, int height, int width) {

	BYTE* paddedBinaryImage = new BYTE[(height + 2)*(width + 2)];

	for (int i = 0; i < (height + 2)*(width + 2); i++) paddedBinaryImage[i] = 0;



	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++) {
			paddedBinaryImage[(row + 1)*(width + 2) + col + 1] = binaryImage[row*width + col];
		}


	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++) {

			int binPos = row * width + col; // binary image position
			int paddedBinaryPos = (row + 1)*(width + 2) + col + 1; // paddedLabeledImage matrix position


			if (paddedBinaryImage[paddedBinaryPos] == 1) {

				if (paddedBinaryImage[paddedBinaryPos - (width + 2) - 1] == 1 && paddedBinaryImage[paddedBinaryPos - (width + 2)] == 1 && paddedBinaryImage[paddedBinaryPos - (width + 2) + 1] == 1
					&& paddedBinaryImage[paddedBinaryPos - 1] == 1 && paddedBinaryImage[paddedBinaryPos + 1] == 1 && paddedBinaryImage[paddedBinaryPos + (width + 2) - 1] == 1
					&& paddedBinaryImage[paddedBinaryPos + (width + 2)] == 1 && paddedBinaryImage[paddedBinaryPos + (width + 2) + 1] == 1
					) {

					binaryImage[binPos] = 1;


				}
				else {

					binaryImage[binPos] = 0;

				}



			}

		}



	return binaryImage;

}




BYTE* closing(BYTE* binaryImage, int height, int width) {

	dilation(binaryImage, height, width);
	erosion(binaryImage, height, width);
	return binaryImage;
}


BYTE* opening(BYTE* binaryImage, int height, int width) {

	erosion(binaryImage, height, width);
	dilation(binaryImage, height, width);
	return binaryImage;

}



int* labelingObjects(BYTE* binaryImage, int height, int width, int& objectCount) {

	int* paddedLabeledImage = new int[(height + 2)*(width + 2)];
	int* labeledImage = new int[height*width];
	int componentCounter = 0;
	int lastComponentCount = 0;

	for (int i = 0; i < (height + 2)*(width + 2); i++) paddedLabeledImage[i] = 0;



	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++) {
			paddedLabeledImage[(row + 1)*(width + 2) + col + 1] = binaryImage[row*width + col];
		}


	int a = 0;
	int d = 0;
	int b = 0;
	int c = 0;

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++) {

			int binPos = row * width + col; // binary image position
			int labeledPos = (row + 1)*(width + 2) + col + 1; // paddedLabeledImage matrix position



			// Computer Vision book page 97 algorithm
			a = paddedLabeledImage[labeledPos];
			d = paddedLabeledImage[labeledPos - (width + 2) - 1];
			b = paddedLabeledImage[labeledPos - 1];
			c = paddedLabeledImage[labeledPos - (width + 2)];





			if (a != 0) {

				if (d != 0) {

					//a = d;
					paddedLabeledImage[labeledPos] = paddedLabeledImage[labeledPos - (width + 2) - 1];
				}
				else if (b != 0) {
					if (c != 0) {
						if (b == c) {
							//a = b;
							paddedLabeledImage[labeledPos] = paddedLabeledImage[labeledPos - 1];

						}
						else {




							// back update function
							if (c < b) {

								for (int i = 0; i < labeledPos; i++) {
									if (paddedLabeledImage[i] == b) paddedLabeledImage[i] = c;
								}

							}
							else if (c > b) {

								for (int i = 0; i < labeledPos; i++) {
									if (paddedLabeledImage[i] == c) paddedLabeledImage[i] = b;
								}

							}

							//a = b;
							paddedLabeledImage[labeledPos] = paddedLabeledImage[labeledPos - 1];

							lastComponentCount--;
						}

					}
					else {
						//a = b;
						paddedLabeledImage[labeledPos] = paddedLabeledImage[labeledPos - 1];
					}

				}
				else if (c != 0) {

					//a = c;
					paddedLabeledImage[labeledPos] = paddedLabeledImage[labeledPos - (width + 2)];
				}
				else {
					componentCounter++;
					lastComponentCount++;

					//a = componentCounter;
					paddedLabeledImage[labeledPos] = componentCounter;
				}

			}

		}



	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++) {
			labeledImage[row*width + col] = paddedLabeledImage[(row + 1)*(width + 2) + col + 1];
		}

	objectCount = lastComponentCount;
	return labeledImage;

} //Finished


int* componentBorderExtract(int* labeledImage, int height, int width, int objectCount) {

	int label = 1;
	int* labelArray = new int[objectCount];
	for (int i = 0; i < objectCount; i++)
		labelArray[i] = 0;

	// Distinct the labeledImage's values & keep in labelArray
	int labelArrayIndex = 1;
	labelArray[0] = 1;
	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++) {
			if (labeledImage[row*width + col] != 0)
			{

				int i = 0;
				int distinctCount = 0;
				for (i = 0; i < labelArrayIndex; i++) {
					if (labeledImage[row*width + col] != labelArray[i])
						distinctCount++;
				}

				if (distinctCount == labelArrayIndex  ) {

					labelArray[labelArrayIndex] = labeledImage[row*width + col];
					labelArrayIndex++;

				}
			}
		}


	// topRow takes the lowest row value
	// downRow takes the biggest row value
	// leftCol takes the lowest col value
	// rightCol takes the biggest col value

	int topRow = 0, downRow = 0, leftCol = 0, rightCol = 0;
	int* objectsBorders = new int[objectCount * 4];


	for (int i = 0; i < objectCount; i++) {

		topRow = height;
		downRow = 0;
		leftCol = width;
		rightCol = 0;

		for (int row = 0; row < height; row++)
			for (int col = 0; col < width; col++) {

				if (labeledImage[row*width + col] == labelArray[i]) {


					if (topRow > row) topRow = row;

					if (downRow < row) downRow = row;

					if (leftCol > col) leftCol = col;

					if (rightCol < col) rightCol = col;

				}

			}


		//Keeping borders in objectsBorders

		objectsBorders[i * 4] = topRow;
		objectsBorders[i * 4 + 1] = downRow;
		objectsBorders[i * 4 + 2] = leftCol;
		objectsBorders[i * 4 + 3] = rightCol;


	}



	return objectsBorders;
}


int* componentExtractWithBorder(int* objectBorder, BYTE* raw_intensity, int height, int width, int objectIndex, int& objectLenght, int& objectHeight, int& objectWidth) {

	int topBorder = objectBorder[objectIndex * 4];			// top
	int downBorder = objectBorder[objectIndex * 4 + 1];		// down
	int leftBorder = objectBorder[objectIndex * 4 + 2];		// left
	int rightBorder = objectBorder[objectIndex * 4 + 3];	// right

	objectLenght = (downBorder - topBorder + 1)*(rightBorder - leftBorder + 1);
	objectHeight = (downBorder - topBorder + 1);
	objectWidth = (rightBorder - leftBorder + 1);
	int* object = new int[objectLenght];

	int index = 0;
	for (int row = topBorder; row <= downBorder; row++)
		for (int col = leftBorder; col <= rightBorder; col++) {
/*
			if (labeledImage[row*width + col] > 0) {
				object[index] = 1;

			}else object[index] = 0;*/
			
			object[index] = raw_intensity[row*width + col];


			index++;

		}

	return object;
}

int* componentExtractWithBorder(int* objectBorder, int* labeledImage, int height, int width, int objectIndex, int& objectLenght, int& objectHeight, int& objectWidth) {

	int topBorder = objectBorder[objectIndex * 4];			// top
	int downBorder = objectBorder[objectIndex * 4 + 1];		// down
	int leftBorder = objectBorder[objectIndex * 4 + 2];		// left
	int rightBorder = objectBorder[objectIndex * 4 + 3];	// right

	objectLenght = (downBorder - topBorder + 1)*(rightBorder - leftBorder + 1);
	objectHeight = (downBorder - topBorder + 1);
	objectWidth = (rightBorder - leftBorder + 1);
	int* object = new int[objectLenght];

	int index = 0;
	for (int row = topBorder; row <= downBorder; row++)
		for (int col = leftBorder; col <= rightBorder; col++) {
			
			if (labeledImage[row*width + col] > 0) {
				object[index] = 1;

			}else object[index] = 0;

			index++;

		}

	return object;
}


int moment(int i, int j, int* object, int objectHeight, int objectWidth) {

	int objectMoment = 0;

	for (int row = 0; row < objectHeight; row++)
		for (int col = 0; col < objectWidth; col++) {
			objectMoment += pow(row, i)*pow(col, j)*object[row*objectWidth + col];
		}

	return objectMoment;

}

float centralMoment(int i, int j, int* object, int objectHeight, int objectWidth) {


	float centoridCol = moment(1, 0, object, objectHeight, objectWidth) / moment(0, 0, object, objectHeight, objectWidth);
	float centoridRow = moment(0, 1, object, objectHeight, objectWidth) / moment(0, 0, object, objectHeight, objectWidth);
	float objectCentralMoment = 0;


	for (int row = 0; row < objectHeight; row++)
		for (int col = 0; col < objectWidth; col++) {
			objectCentralMoment += pow((row - centoridRow), i)*pow((col - centoridCol), j)*object[row*objectWidth + col];
		}

	return objectCentralMoment;

}

float normalizedCentralMoment(int i, int j, int* object, int objectHeight, int objectWidth) {


	float power = (i + j) / 2 + 1;

	float normalizedMoment = centralMoment(i, j, object, objectHeight, objectWidth) / pow(moment(0, 0, object, objectHeight, objectWidth), power);

	return normalizedMoment;
}



//Checked
float* huMoments(int* object, int objectHeight, int objectWidth) {

	float* objectHuMoments = new float[7];

	objectHuMoments[0] = normalizedCentralMoment(2, 0, object, objectHeight, objectWidth) + normalizedCentralMoment(0, 2, object, objectHeight, objectWidth);

	objectHuMoments[1] = pow((normalizedCentralMoment(2, 0, object, objectHeight, objectWidth) - normalizedCentralMoment(0, 2, object, objectHeight, objectWidth)), 2) +
						 4 * pow(normalizedCentralMoment(1, 1, object, objectHeight, objectWidth), 2);

	objectHuMoments[2] = pow((normalizedCentralMoment(3, 0, object, objectHeight, objectWidth) - 3 * normalizedCentralMoment(1, 2, object, objectHeight, objectWidth)), 2) +
						 pow((3 * normalizedCentralMoment(2, 1, object, objectHeight, objectWidth) - normalizedCentralMoment(0, 3, object, objectHeight, objectWidth)), 2);

	objectHuMoments[3] = pow((normalizedCentralMoment(3, 0, object, objectHeight, objectWidth) +  normalizedCentralMoment(1, 2, object, objectHeight, objectWidth)), 2) +
						 pow((normalizedCentralMoment(2, 1, object, objectHeight, objectWidth) + normalizedCentralMoment(0, 3, object, objectHeight, objectWidth)), 2);

	objectHuMoments[4] = (normalizedCentralMoment(3, 0, object, objectHeight, objectWidth) - 3 * normalizedCentralMoment(1, 2, object, objectHeight, objectWidth)) *
						 (normalizedCentralMoment(3, 0, object, objectHeight, objectWidth) + normalizedCentralMoment(1, 2, object, objectHeight, objectWidth)) *
						 (
								pow((normalizedCentralMoment(3, 0, object, objectHeight, objectWidth) + normalizedCentralMoment(1, 2, object, objectHeight, objectWidth)), 2) -
								3 * pow((normalizedCentralMoment(2, 1, object, objectHeight, objectWidth) + normalizedCentralMoment(0, 3, object, objectHeight, objectWidth)), 2)
						 ) +
						 (3 * normalizedCentralMoment(2, 1, object, objectHeight, objectWidth) - normalizedCentralMoment(0, 3, object, objectHeight, objectWidth)) *
						 (
								3 * pow((normalizedCentralMoment(3, 0, object, objectHeight, objectWidth) + normalizedCentralMoment(1, 2, object, objectHeight, objectWidth)), 2) -
								pow((normalizedCentralMoment(2, 1, object, objectHeight, objectWidth) + normalizedCentralMoment(0, 3, object, objectHeight, objectWidth)), 2)
						 );

	objectHuMoments[5] = (normalizedCentralMoment(2, 0, object, objectHeight, objectWidth) - normalizedCentralMoment(0, 2, object, objectHeight, objectWidth)) *
						 (
								pow((normalizedCentralMoment(3, 0, object, objectHeight, objectWidth) + normalizedCentralMoment(1, 2, object, objectHeight, objectWidth)), 2) -
								pow((normalizedCentralMoment(2, 1, object, objectHeight, objectWidth) + normalizedCentralMoment(0, 3, object, objectHeight, objectWidth)), 2) +
								4 * normalizedCentralMoment(1, 1, object, objectHeight, objectWidth) *
								(normalizedCentralMoment(3, 0, object, objectHeight, objectWidth) + normalizedCentralMoment(1, 2, object, objectHeight, objectWidth)) *
								(normalizedCentralMoment(2, 1, object, objectHeight, objectWidth) + normalizedCentralMoment(0, 3, object, objectHeight, objectWidth))
						 );

	objectHuMoments[6] = (3 * normalizedCentralMoment(2, 1, object, objectHeight, objectWidth) - normalizedCentralMoment(0, 3, object, objectHeight, objectWidth)) *
						 (normalizedCentralMoment(3, 0, object, objectHeight, objectWidth) + normalizedCentralMoment(1, 2, object, objectHeight, objectWidth)) *
						 (
								pow((normalizedCentralMoment(3, 0, object, objectHeight, objectWidth) + normalizedCentralMoment(1, 2, object, objectHeight, objectWidth)), 2) -
								3 * pow((normalizedCentralMoment(2, 1, object, objectHeight, objectWidth) + normalizedCentralMoment(0, 3, object, objectHeight, objectWidth)), 2)
						 ) +
						 (normalizedCentralMoment(3, 0, object, objectHeight, objectWidth) - 3 * normalizedCentralMoment(1, 2, object, objectHeight, objectWidth)) *
						 (normalizedCentralMoment(2, 1, object, objectHeight, objectWidth) + normalizedCentralMoment(0, 3, object, objectHeight, objectWidth)) *
						 (
								3 * pow((normalizedCentralMoment(3, 0, object, objectHeight, objectWidth) + normalizedCentralMoment(1, 2, object, objectHeight, objectWidth)), 2) -
								pow((normalizedCentralMoment(2, 1, object, objectHeight, objectWidth) + normalizedCentralMoment(0, 3, object, objectHeight, objectWidth)), 2)
						 );



	return objectHuMoments;
} 

int compareWithEuclideanDistance(float* objectHuMoments,long float* clusterHuMoments, int clusterCount, float& minDistance) {

	float* euclidianDistance = new float[clusterCount];
	int estimateClusterIndex = 0;
	for (int i = 0; i < clusterCount; i++) {

		euclidianDistance[i] = pow(clusterHuMoments[i * 7] - objectHuMoments[0], 2) +
		pow(clusterHuMoments[i * 7 + 1] - objectHuMoments[1], 2) +
		pow(clusterHuMoments[i * 7 + 2] - objectHuMoments[2], 2) +
		pow(clusterHuMoments[i * 7 + 3] - objectHuMoments[3], 2) +
		pow(clusterHuMoments[i * 7 + 4] - objectHuMoments[4], 2) +
		pow(clusterHuMoments[i * 7 + 5] - objectHuMoments[5], 2) +
		pow(clusterHuMoments[i * 7 + 6] - objectHuMoments[6], 2);

		euclidianDistance[i] = sqrt(euclidianDistance[i]);
		
	}

	float min = euclidianDistance[0];
	for (int i = 0; i < clusterCount; i++) {
		if (isless(euclidianDistance[i], min)) {
			min = euclidianDistance[i];
			estimateClusterIndex = i;
		}
	}

	minDistance = min;
	return estimateClusterIndex;
}






//NOT COMPLETE
BYTE* distributeColor(int indexOfCluster, int numberOfK) {
	BYTE* color = new BYTE[3];



	return color;
} 



void mahalanobisDistance(int* k3D, int* labelHistogram3D, int* histogram3D, int numberOfK) {
	int x, y, z, count = 0;
	long result = 0;
	int distanceToCenterX;
	int distanceToCenterY;
	int distanceToCenterZ;

	int ortX;
	int ortY;
	int ortZ;



	for (int i = 0; i < 256 * 256 * 256; i++) {

		if (histogram3D[i] != 0) {
			x = ((i / 256) / 256) % 256; // -> (x,y,z) dimentions calculate x	
			ortX += x;

			y = (i / 256) % 256; // -> (x,y,z) dimentions calculate y	
			ortY += y;
			z = i % 256; // -> (x,y,z) dimentions calculate z
			ortZ += z;
			count++;
		}

	}

	ortX = ortX / count;
	ortY = ortY / count;
	ortZ = ortZ / count;


	int* distanceKi3D = new int[numberOfK];

	for (int j = 0; j < 256 * 256 * 256; j++) {

		for (int i = 0; i < numberOfK; i++) {

			if (histogram3D[j] != 0) {
				x = ((j / 256) / 256) % 256; // -> (x,y,z) dimentions calculate x	probably blue 
				y = (j / 256) % 256; // -> (x,y,z) dimentions calculate y	probably green
				z = j % 256; // -> (x,y,z) dimentions calculate z	probably red 

				distanceToCenterX = x - k3D[i * 3];
				distanceToCenterX = distanceToCenterX / sqrt(pow(x - ortX, 2) / count);


				distanceToCenterY = y - k3D[i * 3 + 1];
				distanceToCenterY = distanceToCenterY / sqrt(pow(y - ortY, 2) / count);

				distanceToCenterZ = z - k3D[i * 3 + 2];
				distanceToCenterZ = distanceToCenterZ / sqrt(pow(z - ortZ, 2) / count);

				result = pow(distanceToCenterX, 2) + pow(distanceToCenterY, 2) + pow(distanceToCenterZ, 2);

				result = sqrt(pow(result, 2));

				/*mhlnbDistance[i * 256 * 256 * 256 + j] = result;

				distanceKi3D[i] = mhlnbDistance[i * 256 * 256 * 256 + j];*/
				distanceKi3D[i] = result;

			}
			else if (histogram3D[j] == 0) {
				labelHistogram3D[j] = -1;

				continue;
			}


			int minIndex = compare(distanceKi3D, numberOfK); // compare() -> returns index of min distance cluster 
			labelHistogram3D[j] = minIndex; // there is minimum distances index of cluster in the label histogram.



		}




	}



}

int* kMeansClustering3D(int* labelHistogram3D, int* histogram3D, int numberOfK) {

	int* k3D = new int[numberOfK * 3];


	int* kMean3D = new int[numberOfK * 3];


	int* modifiedK3D = new int[numberOfK * 3];
	//memset(modifiedK, rand()%256, numberOfK); // Intialized Thresholds. if assing same th value it will be error.

	int* sumOfKLabeled3D = new int[numberOfK];




	int* countK3D = new int[numberOfK];





	srand(time(NULL));
	for (int i = 0; i < numberOfK * 3; i++) {
		k3D[i] = 0;
		kMean3D[i] = 0;
		modifiedK3D[i] = rand() % 256; // Intialized Thresholds. if assing same threshold value it will be error.
		sumOfKLabeled3D[i%numberOfK] = 0;
		countK3D[i%numberOfK] = 0;
	}


	while (true) {



		mahalanobisDistance(k3D, labelHistogram3D, histogram3D, numberOfK); // Mahalanobis distance calculeted and labelHistogram3D is filled with real labels
		for (int j = 0; j < numberOfK * 3; j++) {

			k3D[j] = modifiedK3D[j];


			kMean3D[j] = 0;


			countK3D[j%numberOfK] = 0;


			sumOfKLabeled3D[j%numberOfK] = 0;


		}


		int minIndex;
		for (int i = 0; i < 256 * 256 * 256; i++) {
			if (labelHistogram3D[i] == -1) continue; //if (r,g,b) value didnt been in the bmp picture.
			minIndex = labelHistogram3D[i]; // there is minimum distances index of cluster in the label histogram.

			int x = ((i / 256) / 256) % 256; // -> (x,y,z) dimentions calculate x	probably blue 
			int y = (i / 256) % 256; // -> (x,y,z) dimentions calculate y	probably green
			int z = i % 256; // -> (x,y,z) dimentions calculate z	probably red 

			kMean3D[minIndex] += x * histogram3D[i];
			kMean3D[minIndex + 1] += y * histogram3D[i];
			kMean3D[minIndex + 2] += z * histogram3D[i];


			sumOfKLabeled3D[minIndex] += histogram3D[i];
			countK3D[minIndex]++;
		}

		for (int i = 0; i < numberOfK; i++) {

			if (countK3D[i] != 0) {

				kMean3D[i] /= sumOfKLabeled3D[i];
				kMean3D[i + 1] /= sumOfKLabeled3D[i];
				kMean3D[i + 2] /= sumOfKLabeled3D[i];

				modifiedK3D[i] = kMean3D[i];
				modifiedK3D[i + 1] = kMean3D[i + 1];
				modifiedK3D[i + 2] = kMean3D[i + 2];
			}
			else {

				modifiedK3D[i] = k3D[i];
				modifiedK3D[i + 1] = k3D[i + 1];
				modifiedK3D[i + 2] = k3D[i + 2];

			}


		}


		boolean breakCondition = true;
		for (int i = 0; i < numberOfK; i++) {
			if ((k3D[i] == modifiedK3D[i] && k3D[i + 1] == modifiedK3D[i + 1] && k3D[i + 2] == modifiedK3D[i + 2])) {
				breakCondition = breakCondition && true;
			}
			else {
				breakCondition = breakCondition && false;
			}
		}


		if (breakCondition == true)
			break;

	}


	//deleting from memory garbage collecting
	delete kMean3D;
	delete modifiedK3D;
	delete sumOfKLabeled3D;
	delete countK3D;


	return k3D;


}
