#pragma once

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <random>

std::pair<std::string, int> find_overlapping_word(
	std::string,
	const std::map<std::string, std::string>&);

void simple_answer_smash(
	const std::map<std::string, std::string>&,
	const std::map<std::string, std::string>&
);

std::string str_tolower(std::string);

std::multimap<std::string, std::string>
load_dictionary(const std::string&);

template<typename T>
std::tuple<std::string, std::string, int>
select_overlapping_word_from_dictionary(std::string word,
	const std::multimap<std::string, std::string>& dictionary,
	T select_function)
{
	size_t offset = 1;
	while (offset < word.size())
	{
		auto stem = word.substr(offset);
		auto lb = dictionary.lower_bound(stem);
		auto beyond_stem = stem;
		beyond_stem += ('z' + 1);
		auto ub = dictionary.upper_bound(beyond_stem);
		if (lb != dictionary.end() &&
			lb != ub)
		{
			std::vector<std::pair<std::string, std::string>> dest;
			select_function(lb, ub, std::back_inserter(dest));
			auto found = dest[0].first;
			auto definition = dest[0].second;
			return { found, definition, offset };
		}
		++offset;
	}
	return { "", "", -1 };
}

void answer_smash(
	const std::multimap<std::string, std::string>&,
	const std::multimap<std::string, std::string>&
);
