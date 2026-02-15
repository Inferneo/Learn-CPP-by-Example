#include "Smash.h"
#include <cassert>

void warm_up()
{
	std::map<std::string, std::string> dictionary;
	dictionary["assume"] = "take for granted, take to be the case";
	std::string new_value = dictionary["fictional"];
	for (const auto& item : dictionary)
	{
		std::cout << item.first << " : " << item.second << '\n';
	}
}

void structure_bindings()
{
	std::map<std::string, std::string> dictionary;
	dictionary["assume"] = "presume, take for granted";
	std::string new_word = dictionary["fictional"];
	for (const auto& [key, value] : dictionary) {
		std::cout << key << " : " << value << '\n';
	}
}

void check_properties()
{
	auto select_first = [](auto lb, auto ub, auto dest) {
		*dest = *lb;
		};
	auto [no_word, no_definition, no_offset] =
		select_overlapping_word_from_dictionary("class", {}, select_first);
	assert(no_word == "");
	assert(no_offset == -1);
}

void hard_coded_game() {
	std::map<std::string, std::string> keywords;
	keywords["char"] = "type for character representation which can be"
		" most efficiently processed on the target system";
	keywords["class"] = "user-defined type with private members by default";
	keywords["struct"] = "user-defined type with public members by default";
	keywords["vector"] = "sequential container supporting dynamic resizing";
	keywords["template"] = "family of classes or functions parameterized"
		" by one or more parameters";

	const std::map<std::string, std::string> dictionary{
		{"assume", "take for granted, take to be the case"},
		{"harsh", "coarse, large-grained or rough to the touch"},
		{"table", "piece of furniture"},
		{"tease", "mock, make fun of"},
		{"torch", "lit stick carried in one's hand"}
	};
	simple_answer_smash(keywords, dictionary);
}

int main() {
	check_properties();
	const auto dictionary = load_dictionary(R"(dictionary.csv)");
	const auto keywords = load_dictionary(R"(keywords.csv)");
	answer_smash(keywords, dictionary);
}

