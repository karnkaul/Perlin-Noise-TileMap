#pragma once
#include <noise/noise.h>
#include <noiseutils/noiseutils.h>

using namespace noise;
using namespace utils;

/**********************************************

Instantiate, then set bounds, then build map

**********************************************/

class NoiseGenerator
{
	private:
		float xMin, xMax, zMin, zMax;
		module::Perlin myModule;
		NoiseMap noiseMap;
		NoiseMapBuilderPlane heightMapBuilder;

	public:
		// Pseudo named parameter idiom.
		NoiseGenerator& setBounds(float xMin, float xMax, float zMin, float zMax);
		// Returns intance noiseMap.
		NoiseMap& buildMap(unsigned int rows, unsigned int columns, float seed);
};
