#include <cassert>
#include <coroutine>
#include <functional>
#include <generator>
#include <iostream>
#include <memory>
#include <optional>
#include <random>
#include <ranges>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>

std::generator<char> letters(char first)
{
	for (;; co_yield first++);
}

void generator_experiment()
{
	for (const char ch : letters('a') | std::views::take(26)) {
		std::cout << ch << ' ';
	}
	std::cout << '\n';
}

enum class Choice {
	Same,
	Change,
	Shrug
};

enum class Outcome {
	Lose,
	Win,
	Unset
};

using state_t = std::tuple<Outcome, Choice, Outcome>;
using last_choices_t = std::pair<Choice, Choice>;

template<>
struct std::hash<state_t>
{
	std::size_t operator()(state_t const& state) const noexcept
	{
		std::size_t h1 = std::hash<Outcome>{}(std::get<0>(state));
		std::size_t h2 = std::hash<Choice>{}(std::get<1>(state));
		std::size_t h3 = std::hash<Outcome>{}(std::get<2>(state));
		return h1 + (h2 << 1) + (h3 << 2);
	}
};

std::unordered_map<state_t, last_choices_t> initial_state()
{
	const auto unset = std::pair<Choice, Choice>{ Choice::Shrug,
		Choice::Shrug };
	return {
		{{Outcome::Lose, Choice::Same, Outcome::Lose}, unset},
		{{Outcome::Lose, Choice::Same, Outcome::Win}, unset},
		{{Outcome::Lose, Choice::Change, Outcome::Lose}, unset},
		{{Outcome::Lose, Choice::Change, Outcome::Win}, unset},
		{{Outcome::Win, Choice::Same, Outcome::Lose}, unset},
		{{Outcome::Win, Choice::Same, Outcome::Win}, unset},
		{{Outcome::Win, Choice::Change, Outcome::Lose}, unset},
		{{Outcome::Win, Choice::Change, Outcome::Win}, unset}
	};
}

class State
{
	std::unordered_map<state_t, last_choices_t>
		state_lookup = initial_state();

public:
	last_choices_t choices(const state_t& key) const {
		if (auto it = state_lookup.find(key); it != state_lookup.end())
		{
			return it->second;
		}
		else
		{
			return { Choice::Shrug, Choice::Shrug };
		}
	}

	void update(const state_t& key,
		const Choice& turn_changed)
	{
		if (auto it = state_lookup.find(key); it != state_lookup.end())
		{
			const auto [prev2, prev1] = it->second;
			last_choices_t value{ prev1, turn_changed };
			it->second = value;
		}
	}
};

Choice prediction_method(const last_choices_t& choices) {
	if (choices.first == choices.second)
	{
		return choices.first;
	}
	else
	{
		return Choice::Shrug;
	}
}

template<std::invocable<> T, typename U>
class MindReader {
	State state_table;
	T generator;
	U distribution;
	int prediction = flip();
	state_t state{
		Outcome::Unset,
		Choice::Shrug,
		Outcome::Unset
	};
	int previous_go = -1;
	int flip() {
		return distribution(generator);
	}
public:
	MindReader(T gen, U dis) : generator(gen), distribution(dis) {}
	int get_prediction() const {
		return prediction;
	}
	bool update_prediction(int player_choice)
	{
		bool guessing = false;
		Choice option =
			prediction_method(state_table.choices(state));
		switch (option)
		{
		case Choice::Same:
			prediction = player_choice;
			break;
		case Choice::Change:
			prediction = player_choice ^ 1;
			break;
		case Choice::Shrug:
			prediction = flip();
			guessing = true;
			break;
		default:
			break;
		}
		return guessing;
	}
	bool update(int player_choice)
	{
		const Choice turn_changed = player_choice == previous_go ?
			Choice::Same : Choice::Change;
		state_table.update(state, turn_changed);

		previous_go = player_choice;
		state = { std::get<2>(state),
			turn_changed,
			(player_choice != prediction) ? Outcome::Win : Outcome::Lose };

		return update_prediction(player_choice);
	}
};

std::optional<int> read_number(std::istream& in)
{
	std::string line;
	std::getline(in, line);
	if (line == "0")
	{
		return { 0 };
	}
	else if (line == "1")
	{
		return { 1 };
	}
	return {};
}

void pennies_game()
{
	int player_wins = 0;
	int turns = 0;
	std::mt19937 gen{ std::random_device{}() };
	std::uniform_int_distribution dist(0, 1);

	std::cout << "Select 0 or 1 at random and press enter.\n";
	std::cout << "If the computer predicts your guess it wins.\n";
	while (true)
	{
		const int prediction = dist(gen);

		auto input = read_number(std::cin);
		if (!input)
		{
			break;
		}
		const int player_choice = input.value();

		++turns;
		std::cout << "You pressed " << player_choice <<
			" , I guessed " << prediction << '\n';

		if (player_choice != prediction)
		{
			++player_wins;
		}
	}
	std::cout << "You win " << player_wins << '\n'
		<< "I win " << turns - player_wins << '\n';
}

void mind_reader()
{
	int player_wins = 0;
	int turns = 0;
	int guessing = 0;

	std::mt19937 gen{ std::random_device{}() };
	std::uniform_int_distribution dist(0, 1);
	MindReader mr(gen, dist);

	std::cout << "Select 0 or 1 at random and press enter.\n";
	std::cout << "If the computer predicts your guess it wins.\n";
	std::cout << "and it can now read your mind.\n";
	while (true)
	{
		const int prediction = mr.get_prediction();

		auto input = read_number(std::cin);
		if (!input)
		{
			break;
		}
		const int player_choice = input.value();

		++turns;
		std::cout << "You pressed " << player_choice <<
			" , I guessed " << prediction << '\n';

		if (player_choice != prediction)
		{
			++player_wins;
		}
		if (mr.update(player_choice)) {
			++guessing;
		}
	}
	std::cout << "You win " << player_wins << '\n'
		<< "Machine guessed " << guessing << " times" << '\n'
		<< "Machine won " << turns - player_wins << '\n';
}


template<typename Promise>
struct coro_deleter
{
	void operator() (Promise* promise) const noexcept
	{
		auto handle = std::coroutine_handle<Promise>::from_promise(
			*promise
		);
		if (handle)
		{
			handle.destroy();
		}
	}
};

template<typename T>
using promise_ptr = std::unique_ptr<T, coro_deleter<T>>;

struct Task {
	struct promise_type {
		std::pair<int, int> choice_and_prediction;

		Task get_return_object() {
			return Task(this);
		}
		std::suspend_never initial_suspend() noexcept
		{
			return {};
		}
		std::suspend_always final_suspend() noexcept
		{
			return {};
		}
		void unhandled_exception() {}
		std::suspend_always yield_value(std::pair<int, int> got) {
			choice_and_prediction = got;
			return {};
		}

		void return_void() {}
	};

	std::pair<int, int> choice_and_prediction()
	{
		return promise->choice_and_prediction;
	}

	bool done() const
	{
		auto handle =
			std::coroutine_handle<promise_type>::from_promise(*promise);
		return handle.done();
	}

	void next()
	{
		auto handle =
			std::coroutine_handle<promise_type>::from_promise(*promise);
		return handle();
	}

private:
	promise_ptr<promise_type> promise;
	Task(promise_type* p) : promise(p) {}
};

Task coroutine_game()
{
	std::mt19937 gen{ std::random_device{}() };
	std::uniform_int_distribution dist{ 0, 1 };
	MindReader mr(gen, dist);
	while (true)
	{
		auto input = read_number(std::cin);
		if (!input)
		{
			co_return;
		}
		int player_choice = input.value();
		co_yield{ player_choice, mr.get_prediction() };
		mr.update(player_choice);
	}
}

void coroutine_mind_reader()
{
	int player_wins = 0;
	int turns = 0;
	

	std::cout << "Select 0 or 1 at random and press enter.\n";
	std::cout << "If the computer predicts your guess it wins.\n"
		<< "and it can now read your mind.\n";

	Task game = coroutine_game();

	while (!game.done())
	{
		auto [player_choice, prediction] =
			game.choice_and_prediction();

		++turns;
		std::cout << "You pressed " << player_choice <<
			" , I guessed " << prediction << '\n';

		if (player_choice != prediction)
		{
			++player_wins;
		}
		game.next();
	}
	std::cout << "You win " << player_wins << '\n'
		<< "I win " << turns - player_wins << '\n';
}

void check_properties()
{
	std::unordered_map<state_t, last_choices_t> states = initial_state();
	for (size_t bucket = 0; bucket < states.bucket_count(); ++bucket)
	{
		assert(states.bucket_size(bucket) <= 1);
	}
}

int main() {
	//mind_reader();
	//generator_experiment();
	coroutine_mind_reader();
}