#pragma once

#include <algorithm>
#include <array>
#include <compare>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <variant>

namespace cards
{
	enum class Suit
	{
		Hearts,
		Diamonds,
		Clubs,
		Spades
	};

	class FaceValue
	{
	public:
		explicit FaceValue(int value) : value_(value)
		{
			if (value_ < 1 || value_ > 13)
			{
				throw std::invalid_argument(
					"Face value invalid"
				);
			}
		}
		int value() const
		{
			return value_;
		}
		auto operator<=>(const FaceValue&) const = default;
	private:
		int value_;
	};

	class Card
	{
	public:
		Card() = default;
		Card(FaceValue value, Suit suit) :
			value_(value),
			suit_(suit)
		{
		}
		FaceValue value() const { return value_; }
		Suit suit() const { return suit_; }
		auto operator<=>(const Card&) const = default;
	private:
		FaceValue value_{ 1 };
		Suit suit_{};
	};

	struct Joker
	{
	};

	std::ostream& operator<<(std::ostream& os, const Card& card);

	std::ostream& operator<<(std::ostream& os, const std::variant<Card, Joker>& card);

	std::string to_string(const Suit& suit);

	std::string to_string(const FaceValue& value);

	std::array<Card, 52> create_deck();

	Suit& operator++(Suit& suit);

	void shuffle_deck(std::array<std::variant<Card, Joker>, 54>& deck);

	bool is_guess_correct(
		char guess,
		const Card& current,
		const Card& next);

	bool is_guess_correct(
		char guess,
		const std::variant<Card, Joker>& current,
		const std::variant<Card, Joker>& next);

	void higher_lower_with_jokers();

	std::array<std::variant<Card, Joker>, 54> create_extended_deck();
}
