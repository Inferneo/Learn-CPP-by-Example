#pragma once

#include <memory>
#include <vector>

namespace Race
{
	class Blob
	{
	public:
		virtual ~Blob() = default;
		Blob() = default;
		Blob(const Blob&) = delete;
		Blob& operator=(const Blob&) = delete;

		virtual void step() = 0;
		virtual int total_steps() const = 0;
	};

	class StepperBlob : public Blob
	{
		int y = 0;
	public:
		void step() override
		{
			y += 2;
		}
		int total_steps() const override
		{
			return y;
		}
	};

	template<typename T, typename U>
	class RandomBlob : public Blob
	{
		int y = 0;
		T generator;
		U distribution;
	public:
		RandomBlob(T gen, U dis)
			: generator(gen), distribution(dis)
		{
		}
		void step() override
		{
			y += static_cast<int>(distribution(generator));
		}
		int total_steps() const override
		{
			return y;
		}
	};

	void move_blobs(std::vector<Race::StepperBlob>&);
	void draw_blobs(const std::vector<Race::StepperBlob>&);
	void race(std::vector<Race::StepperBlob>&);

	void race(std::vector<std::unique_ptr<Blob>>&);
	void move_blobs(std::vector<std::unique_ptr<Blob>>&);
	void draw_blobs(const std::vector<std::unique_ptr<Blob>>&);

	std::vector<std::unique_ptr<Race::Blob>>
		create_blobs(int);
}
