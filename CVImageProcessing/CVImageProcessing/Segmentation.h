#pragma once

void kMeansClustering(int* labelHistogram, int* histogram, int& t1X, int& t1Y, int& t2X, int& t2Y);
void kMeansClustering2(int* labelHistogram, int* histogram, int& k1,  int& k2);

int compare(int* distanceKi, int numberOfK);
int* kMeansClusteringKCluster(int* labelHistogram, int* histogram, int numberOfK);


BYTE* convertToBinary(BYTE* raw_intensity, int lenghtOfPictureArray);


//morphology
BYTE* dilation(BYTE* binaryImage, int height, int width);
BYTE* erosion(BYTE* binaryImage, int height, int width);

//morphology
BYTE* meanFiltering(BYTE* raw_intensity,int height, int width);
BYTE* closing(BYTE* binaryImage, int height, int width);
BYTE* opening(BYTE* binaryImage, int height, int width);


int* labelingObjects(BYTE* binaryImage, int height, int width,int& objectCount);
int* componentBorderExtract(int* labeledImage, int height, int width, int objectCount);
int* componentExtractWithBorder(int* objectBorder, BYTE* raw_intensity, int height, int width,  int objectIndex, int& objectLenght, int& objectHeight, int& objectWidth);
int* componentExtractWithBorder(int* objectBorder, int* labeledImage, int height, int width, int objectIndex, int& objectLenght, int& objectHeight, int& objectWidth);


//huMoments
int moment(int i, int j, int* object, int objectHeight, int objectWidth);
float centralMoment(int i, int j, int* object, int objectHeight, int objectWidth);
float normalizedCentralMoment(int i, int j, int* object, int objectHeight, int objectWidth);
float* huMoments(int* object, int objectHeight, int objectWidth); 
int compareWithEuclideanDistance(float* objectHuMoments, long float* clusterHuMoments, int clusterCount, float& minDistance);






BYTE* distributeColor(int indexOfCluster, int numberOfK);
void mahalanobisDistance(int* k3D, int* labelHistogram3D, int* histogram3D,int numberOfK);
int* kMeansClustering3D(int* labelHistogram3D, int* histogram3D,int numberOfK);