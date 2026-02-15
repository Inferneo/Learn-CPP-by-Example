#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>

#include "Race.h"

void Race::draw_blobs(const std::vector<std::unique_ptr<Blob>>& blobs)
{
	const int bag_height = 3;
	const int race_height = 8;

	for (int y = race_height; y >= 0; y--)
	{
		std::string output = y >= bag_height ? "  " : "| ";
		for (const auto& blob : blobs)
		{
			if (blob->total_steps() >= y)
			{
				output += "* ";
			}
			else
			{
				output += "  ";
			}
		}
		output += y >= bag_height ? "  " : " |";
		std::cout << output << '\n';
	}
	const int edges = 3;
	std::cout << std::string(blobs.size() * 2 + edges, '-') << '\n';
}

void Race::move_blobs(std::vector<std::unique_ptr<Blob>>& blobs)
{
	for (auto& blob : blobs)
	{
		blob->step();
	}
}

void Race::race(std::vector<std::unique_ptr<Blob>>& blobs)
{
	using namespace std::chrono;
	const int max = 3;
	std::cout << "\x1B[2J\x1B[H";
	for (int i = 0; i < max; ++i) {
		draw_blobs(blobs);
		move_blobs(blobs);
		std::this_thread::sleep_for(1000ms);
		std::cout << "\x1B[2J\x1B[H";
	}
	draw_blobs(blobs);
}

std::vector<std::unique_ptr<Race::Blob>> Race::create_blobs(int number)
{
	using namespace Race;
	std::vector<std::unique_ptr<Blob>> blobs;
	std::random_device rd;
	for (int i = 0; i < number / 2; ++i) {
		blobs.emplace_back(std::make_unique<StepperBlob>());
		blobs.emplace_back(
			std::make_unique<
			RandomBlob<std::default_random_engine,
			std::uniform_int_distribution<int>>
			>
			(
				std::default_random_engine(rd()),
				std::uniform_int_distribution{ 0, 4 }
			)
		);
	}
	return blobs;
}