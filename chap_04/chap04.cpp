#include <chrono>
#include <format>
#include <iostream>
#include <optional>
#include <ratio>
#include <string>
#include <thread>

void duration_to_end_of_year() {
	std::chrono::time_point now = std::chrono::system_clock::now();
	constexpr auto year = 2026;
	auto new_years_eve = std::chrono::year_month_day(
		std::chrono::year(year),
		std::chrono::month(12),
		std::chrono::day(31));
	auto event = std::chrono::sys_days(new_years_eve);
	std::chrono::duration dur = event - now;
	std::cout << dur << " until event\n";
}

void durations() {
	using namespace std::chrono;
	auto nearly_a_day = hours{ 23 };
	days a_day = duration_cast<days>(nearly_a_day);
	hours round_trip = a_day;
	std::cout << nearly_a_day << " cast to " << a_day
		<< " and cast back to " << round_trip << '\n';
}

void defining_a_duration() {
	using namespace std::chrono;
	using centuries = duration<long long,
		std::ratio_multiply<years::period, std::hecto>>;
	centuries two_hundred_years = centuries(2);
	seconds sec = two_hundred_years;
	hours hrs = two_hundred_years;
	days day_count = duration_cast<days>(two_hundred_years);
	std::cout << "Two centuries is approximately " << day_count << '\n';
}

template<typename T>
concept Quacks = requires(T t) {
	t.Quack();
};

template<typename T>
	requires Quacks<T>
void must_be_a_duck(T x) {
	x.Quack();
};

void also_must_be_a_duck(Quacks auto x) {
	x.Quack();
};

void countdown() {
	using namespace std::chrono;
	time_point now = system_clock::now();

	const auto ymd = year_month_day{ floor<days>(now) };

	auto this_year = ymd.year();
	auto new_years_eve = this_year / December / 31;

	auto event = sys_days(new_years_eve);
	duration dur = event - now;
	std::cout << duration_cast<days>(dur) << " until event \n";
}

void pay_day() {
	using namespace std::chrono;

	time_point now = system_clock::now();
	const auto ymd = year_month_day{ floor<days>(now) };
	auto pay_day = ymd.year() / ymd.month() / Friday[last];
	auto event = sys_days(pay_day);
	duration dur = event - now;
	std::cout << duration_cast<days>(dur) << " until pay_day \n";
}

constexpr std::chrono::system_clock::duration
countdown(std::chrono::system_clock::time_point start) {
	using namespace std::chrono;

	auto days_only = floor<days>(start);

	const auto ymd = year_month_day{ days_only };

	auto this_year = ymd.year();
	auto new_years_eve = this_year / December / last;

	auto event = sys_days(new_years_eve);
	return event - start;
}

void check_properties() {
	using namespace std::chrono;
	constexpr auto new_years_eve = 2026y / December / last;
	constexpr auto one_day_away = sys_days{ new_years_eve } - 24h;
	constexpr auto result = countdown(one_day_away);
	static_assert(duration_cast<days>(result) == days(1));
}

std::optional<std::chrono::year_month_day> read_date(std::istream& in) {
	using namespace std::string_literals;
	auto format_str = "%Y-%m-%d"s;
	std::chrono::year_month_day date;
	if (in >> std::chrono::parse(format_str, date))
	{
		return date;
	}
	in.clear();
	std::cout << "Invalid format. Expected " << format_str << '\n';
	return {};
}

constexpr std::chrono::system_clock::duration
countdown_to(std::chrono::system_clock::time_point now,
	std::chrono::year_month_day date) {
	using namespace std::chrono;
	auto event = sys_days(date);
	return event - now;
}

std::chrono::system_clock::duration
countdown_in_local_time(std::chrono::system_clock::time_point now,
	std::chrono::year_month_day date) {
	using namespace std::chrono;
	auto sys_event = zoned_time(current_zone(),
		local_days{ date }).get_sys_time();
	return sys_event - now;
}

int main() {
	using namespace std::chrono;
	std::cout << "Enter a date\n";
	std::string str;
	std::cin >> str;
	std::istringstream in(str);
	std::optional<year_month_day> event_date = read_date(in);
	if (event_date)
	{
		auto dur = countdown_to(std::chrono::system_clock::now(), event_date.value());
		std::cout << std::format("{} until {:%F}\n",
			duration_cast<days>(dur),
			event_date.value());
	}
	//check_properties();
	//for (int i = 0; i < 5; ++i) {
	//	std::this_thread::sleep_for(5000ms);
	//	auto dur = countdown(system_clock::now());
	//	std::cout << duration_cast<seconds>(dur) << " until event\n";
	//}
}

