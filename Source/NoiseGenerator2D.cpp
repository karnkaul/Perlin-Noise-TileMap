#include "NoiseGenerator2D.h"

NoiseGenerator & NoiseGenerator::setBounds(float xMin, float xMax, float zMin, float zMax)
{
	this->xMin = xMin;
	this->xMax = xMax;
	this->zMax = zMax;
	this->zMin = zMin;
	return *this;
}

NoiseMap & NoiseGenerator::buildMap(unsigned int rows, unsigned int columns, float seed)
{
	myModule.SetSeed(seed);
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(noiseMap);
	heightMapBuilder.SetDestSize(rows, columns);
	heightMapBuilder.SetBounds(xMin, xMax, zMin, zMax);
	heightMapBuilder.Build();
	return noiseMap;
}
