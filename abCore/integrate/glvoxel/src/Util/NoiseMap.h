#pragma once

#include <array>

#include "VoxelGL.h"

#include "ChunkData.h" // need a place to store all shared data
#include "fastnoiselite/FastNoiseLite.h"

class NoiseMap {
public:
	NoiseMap(int seed, unsigned int gain, float freq);
	~NoiseMap();

	// move
	void Reseed(); // move to noise class
	void Generate(); // move to noise class

	// Inline Functions
	inline unsigned int GetGain() const { return m_Gain; }
	inline float GetFreq() const { return m_Freq; }
	inline void SetGain(unsigned int gain) { m_Gain = gain; }
	inline void SetFreq(float freq) { m_Freq = freq; }
private:

public:

private:
	bool m_Regenerate;
	unsigned int m_Gain;
	float m_Freq;

	FastNoiseLite m_Noise;
	std::array<uint32_t, CHUNKDATA::MAXBLOCKCOUNT> m_NoiseData;
	std::array<uint32_t, CHUNKDATA::MAXCHUNKCOUNT> m_NoiseSeedTable; // working?
	std::array<float, CHUNKDATA::MAXCHUNKCOUNT> m_NoiseFreqTable;

};