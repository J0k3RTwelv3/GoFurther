#include <iostream>
#include <chrono>

#include "LevelGenerator.h"
#include "ClassicLevelWriter.h"
#include "GroundLineGenerationAlgorithm.h"

int main(int argc, char** argv)
{
	unsigned int linesToGenerate = 1000000;
	
	LevelGenerator* levelGenrator = new LevelGenerator(
		new ClassicLevelWriter("C:\\Users\\bedwa\\AppData\\Roaming\\17Studio\\Draw Rider\\Documents\\userlevels\\outlevel"),
		new GroundLineGenerationAlgorithm({ -250.0, 250.0 }, 1000, {0.31, 0.31, 0.31}, {0.16, 0.16, 0.16})
	);
	
	auto startTime = std::chrono::high_resolution_clock::now();
	levelGenrator->Generate(linesToGenerate / 2, linesToGenerate / 2);
	auto endTime = std::chrono::high_resolution_clock::now();

	auto totalTime = std::chrono::duration<double, std::milli>(endTime - startTime);

	std::cout << "It took " << std::to_string(totalTime.count()) << " milliseconds to generate " << std::to_string(linesToGenerate) << " lines.\n";

	delete levelGenrator;
}