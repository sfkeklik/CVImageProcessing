#pragma once

int* sobel(BYTE* raw_intensity, int height, int width, int* sobelMagnitude, float* sobelOrientation);

BYTE* gaussianFilter(BYTE* raw_intensity, int height, int width);

float* gaussianFilter(float* raw_intensity, int height, int width);

int* nonMaximaSuppression(int height, int width, int* sobelMagnitude, float* sobelOrientation);

float* zScoreCalculate(int height, int width, int* sobelMagnitude, float* sobelOrientation);

void hysteresisThreshold(int pos,int width,int height,int* normalizedMagnitude,int& recursionCount);

int hysteresisThreshold2(int pos, int width, int height, int* normalizedMagnitude, float* sobelOrientation, int& recursionCount);

int* cannyEdgeDetector(BYTE* raw_intensity,int height, int width, int* sobelMagnitude, float* sobelOrientation);

int angleQuantization(float angle);

int distanceQuantization(float distance);

float* distanceQuantization(float* distance, int height, int width);


int* houghTransformWithOrientation(int* edgeImage, int height, int width, float* sobelOrientation, int lineCount, int& pixelLocationOfLineLenght, int*& mostSignificantLine);
