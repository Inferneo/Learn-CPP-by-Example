#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <execution>
#include <format>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <random>
#include <ranges>
#include <string>
#include <variant>
#include <vector>

struct Hold {};
struct Nudge {};
struct Spin {};

using Reel = std::vector<int>;
using options = std::variant<Hold, Nudge, Spin>;

constexpr std::vector<int> make_triangle_numbers(int count)
{
	std::vector<int> numbers(count);
	std::iota(numbers.begin(), numbers.end(), 1);
	std::partial_sum(numbers.begin(), numbers.end(), numbers.begin());
	return numbers;
}

void check_properties() {
	const int count = 20;
	const auto triangle_numbers = make_triangle_numbers(count);
	std::vector<int> diffs(count);
	std::adjacent_difference(triangle_numbers.begin(),
		triangle_numbers.end(), diffs.begin());
	std::vector<int> numbers(count);
	std::iota(numbers.begin(), numbers.end(), 1);
	assert(numbers == diffs);

	std::adjacent_difference(diffs.begin(), diffs.end(), diffs.begin());

	assert(std::all_of(diffs.begin(), diffs.end(),
		[](int x) { return x == 1; }));
	assert(std::count(std::execution::par, diffs.begin(), diffs.end(), 1)
		== count);

	for (size_t i = 0; i < triangle_numbers.size(); ++i) {
		const int n = i + 1;
		assert(triangle_numbers[i] == n * (n + 1) / 2);
	}

	assert(std::all_of(triangle_numbers.begin(), triangle_numbers.end(),
		[n = 0](int x) mutable {++n; return x == n * (n + 1) / 2; }));
}

void demo_further_properties()
{
	const int count = 20;
	const auto triangle_numbers = make_triangle_numbers(count);
	std::vector<char> odd_or_even;
	std::ranges::transform(triangle_numbers,
		std::back_inserter(odd_or_even),
		[](int i) {return i % 2 ? '.' : '*'; });
	std::ranges::copy(odd_or_even,
		std::ostream_iterator<char>(std::cout, " "));
	std::cout << '\n';

	std::map<int, size_t> last_digits;
	for (int number : triangle_numbers)
	{
		++last_digits[number % 10];
	}
	std::cout <<
		"Tallies of the final digits of the first 20 triangle numbers\n";
	for (const auto& [key, value] : last_digits)
	{
		std::cout << key << " : " << value << '\n';
	}
}

template<std::invocable<std::vector<Reel>::iterator,
	std::vector<Reel>::iterator> T>
constexpr std::vector<Reel> make_reels(int numbers,
	int number_of_reels,
	T shuffle)
{
	std::vector<Reel> reels(number_of_reels,
		make_triangle_numbers(numbers));

	for (auto& reel : reels)
	{
		shuffle(reel.begin(), reel.end());
	}
	return reels;
}

void show_reels(std::ostream& os,
	const Reel& left,
	const Reel& middle,
	const Reel& right) {
	os << std::format(" {:>3} {:>3} {:>3}\n",
		left.back(), middle.back(), right.back());
	os << std::format("-{:>3} {:>3} {:>3}-\n", left[0], middle[0], right[0]);
	os << std::format(" {:>3} {:>3} {:>3}\n", left[1], middle[1], right[1]);
}

template<typename... Ts>
auto add(const Ts&... tail)
{
	return (... + tail);
}

std::map<int, size_t>
frequencies(std::convertible_to<int> auto ... numbers)
{
	std::map<int, size_t> counter{};
	for (int i : {static_cast<int>(numbers)...})
	{
		counter[i]++;
	}
	return counter;
}

int calculate_payout(int left, int middle, int right)
{
	std::map<int, size_t> counter = frequencies(left, middle, right);
	auto it = std::max_element(counter.begin(), counter.end(),
		[](auto it1, auto it2) {
			return it1.second < it2.second; });
	if (it != counter.end())
	{
		int digit = it->first;
		size_t count = it->second;
		if (digit == 3 || digit == 8)
		{
			constexpr std::array value = { 0, 0, 10, 250 };
			return value[count];
		}
		else {
			constexpr std::array value = { 0, 0, 1, 15 };
			return value[count];
		}
	}
	return 0;
}

void triangle_machine_spins_only()
{
	constexpr int numbers = 20;
	constexpr size_t number_of_reels = 3u;
	std::random_device rd;
	std::mt19937 gen{ rd() };
	auto shuffle = [&gen](auto begin, auto end)
		{ std::shuffle(begin, end, gen); };
	std::vector<Reel> reels = make_reels(numbers, number_of_reels, shuffle);
	std::uniform_int_distribution dist(1, numbers - 1);
	int credit = 1;
	while (true)
	{
		show_reels(std::cout, reels[0], reels[1], reels[2]);
		const int payout = calculate_payout(reels[0][0] % 10,
			reels[1][0] % 10,
			reels[2][0] % 10);
		--credit;
		credit += payout;
		std::cout << "won " << payout
			<< " credit  = " << credit << '\n';

		std::string response;
		std::getline(std::cin, response);
		if (response != "")
		{
			break;
		}
		for (auto& reel : reels)
		{
			std::rotate(reel.begin(), reel.begin() + dist(gen), reel.end());
		}
	}

}

constexpr std::optional<std::vector<options>>
parse_enter(const std::string& response)
{
	if (response.empty())
	{
		return std::vector<options>{Spin{}, Spin{}, Spin{}};
	}
	else
	{
		return {};
	}
}

std::optional<std::vector<options>> get_enter()
{
	std::cout << "Enter to play\n";
	std::string response;
	std::getline(std::cin, response);
	auto got = parse_enter(response);
	if (!got)
	{
		std::cout << "Are you sure you want to quit? "
			"Press Enter to keep playing.\n";
		std::getline(std::cin, response);
		got = parse_enter(response);
	}
	return got;
}

constexpr std::optional<options> map_input(char c)
{
	switch (c)
	{
	case 'h':
		return Hold{};
		break;
	case 'n':
		return Nudge{};
		break;
	case 's':
		return Spin{};
		break;
	}
	return {};
}

constexpr std::optional<std::vector<options>>
parse_input(const std::string& response)
{
	std::vector<options> choice;
	for (char c : response)
	{
		auto first = map_input(c);
		if (first)
		{
			choice.push_back(first.value());
		}
		else
		{
			return {};
		}
	}
	return choice.empty() ?
		std::vector<options>{Spin{}, Spin{}, Spin{}} : choice;
}

std::optional<std::vector<options>>
get_input(size_t expected_length)
{
	std::cout << "Hold (h), spin (s), nudge (n) or Enter for spins\n";
	std::string response;
	std::getline(std::cin, response);
	auto got = parse_input(response);
	if (!got || response.length() > expected_length)
	{
		std::cout << "Are you sure you want to quit?\n";
		std::getline(std::cin, response);
		got = parse_input(response);
	}
	return got;
}

template <typename ...Ts>
struct Overload : Ts... {
	using Ts::operator()...;
};
template<typename ...Ts>
Overload(Ts...) -> Overload<Ts...>;

template<typename T>
void move_reel(Reel& reel, options opt, T random_fn) {
	auto RollMethod = Overload{
		[](Hold) {},
		[&reel](Nudge) {
			std::rotate(reel.begin(),
				reel.begin() + 1,
				reel.end());
	},
	[&reel, &random_fn](Spin) {
			std::rotate(reel.begin(),
				reel.begin() + random_fn(),
				reel.end());
	}
	};
	std::visit(RollMethod, opt);
}

void triangle_machine()
{
	constexpr int numbers = 20;
	constexpr size_t number_of_reels = 3u;
	std::random_device rd;
	std::mt19937 gen{ rd() };
	auto shuffle = [&gen](auto begin, auto end) {
		std::shuffle(begin, end, gen);
		};
	std::vector<Reel> reels = make_reels(numbers, number_of_reels,
		shuffle);
	std::uniform_int_distribution dist{ 1, numbers - 1 };
	auto random_fn = [&gen, &dist]() { return dist(gen); };
	int credit = 2;
	while (true)
	{
		show_reels(std::cout, reels[0], reels[1], reels[2]);
		const int won = calculate_payout(reels[0][0] % 10,
			reels[1][0] % 10,
			reels[2][0] % 10);
		credit -= 2;
		credit += won;
		std::cout << "won " << won << "\tcredit = " << credit << '\n';

		std::optional<std::vector<options>> choice = won ?
			get_enter() : get_input(number_of_reels);
		if (!choice)
		{
			break;
		}

		for (auto [reel, option] :
			std::views::zip(reels, choice.value()))
		{
			move_reel(reel, option, random_fn);
		}
	}
}

int main()
{
	//demo_further_properties();
	//triangle_machine_spins_only();
	triangle_machine();
}