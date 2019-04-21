
#include "lsystem.h"
#include <stack>
#include <memory>
#include <iostream>

/*
Provided utilities:

- Dice class (utils/misc.h)
	Produces random values uniformly distributed between 0 and 1
	Example:
		Dice d;
		double random_val = d.roll();

- write_string_to_file (utils/misc.h)
	Write string data into a text file.
	Example:
		write_string_to_file("ala ma kota!", "ala.txt");
*/

std::string LindenmayerSystemDeterministic::expandSymbol(unsigned char const& sym) {
	/*============================================================
		TODO 1.1
		For a given symbol in the sequence, what should it be replaced with after expansion?
		The rules are in this->rules, see lsystem.h for details.
	*/

	// If a symbol have a key entry in the rules map, return its value. Otherwise return the symbol with no changement.
	if (rules.find(sym) != rules.end()) {
		return rules.find(sym)->second;
	} else {
		return {char(sym)}; // this constructs string from char
	}

	/*
	You may find useful:
		map.find: Iterator to an element with key equivalent to key. If no such element is found, past-the-end (see end()) iterator is returned.
		http://en.cppreference.com/w/cpp/container/unordered_map/find
	============================================================
	*/
}

std::string LindenmayerSystem::expandOnce(std::string const& symbol_sequence) {
	/*============================================================
		TODO 1.2
		Perform one iteration of grammar expansion on `symbol_sequence`.
		Use the expandSymbol method
	*/
	std::string expanded_seq;

	for (auto symbol : symbol_sequence) {
		expanded_seq.append(expandSymbol(symbol));
	}

	return expanded_seq;

	//============================================================
}

std::string LindenmayerSystem::expand(std::string const& initial, uint32_t num_iters) {
	/*============================================================
		TODO 1.3
		Perform `num_iters` iterations of grammar expansion (use expandOnce)
	*/
	std::string new_seq = initial;

	for (int i(0); i < num_iters; ++i) {
		new_seq = expandOnce(new_seq);
	}

	return new_seq;

	//============================================================
}

std::vector<Segment> LindenmayerSystem::draw(std::string const& symbols) {
	/*============================================================
		TODO 2.1
		Build line segments according to the sequence of symbols
		The initial position is (0, 0) and the initial direction is "up" (0, 1)
		Segment is std::pair<vec2, vec2>
		
	*/
	std::vector<Segment> lines;
	vec2 position = vec2(0,0);
	vec2 direction = vec2(0,1);

	// Stack to keep in memory positions & directions when using []
	std::vector<vec2> positions_stack;
	std::vector<vec2> directions_stack;


	double radii_angle = deg2rad(rotation_angle_deg);
	// Rotation matrix for +
	mat2 rotation_plus = mat2(cos(radii_angle), -sin(radii_angle), 
								sin(radii_angle), cos(radii_angle));
	// Rotation matrix for -
	mat2 rotation_minus = mat2(cos(radii_angle), sin(radii_angle), 
								-sin(radii_angle), cos(radii_angle));

	for (const char symbol : symbols) {

		switch (symbol) {
			case '+' :
				direction = rotation_plus * direction;
				break;
			case '-' :
				direction = rotation_minus * direction;
				break;
			case '[' :
				positions_stack.push_back(position);
				directions_stack.push_back(direction);
				break;
			case ']' :
				position = positions_stack.back();
				direction = directions_stack.back();
				positions_stack.pop_back();
				directions_stack.pop_back();
				break;
			default :
				vec2 new_position = position + direction; // Knowing that direction is always a unit vector
				lines.push_back(Segment(position, new_position));
				position = new_position;
				break;
		}
	}
	return lines;
	
	//============================================================
}

std::string LindenmayerSystemStochastic::expandSymbol(unsigned char const& sym) {
	/*============================================================
		TODO 4.1
		For a given symbol in the sequence, what should it be replaced with after expansion?
		(stochastic case)
		The rules are in this->rules, but now these are stochastic rules because this method belongs to the LindenmayerSystemStochastic class, see lsystem.h for details.
	*/
	return {char(sym)};

	//============================================================
}

void LindenmayerSystemDeterministic::addRuleDeterministic(unsigned char sym, std::string const& expansion) {
	rules[sym] = expansion;
}

void LindenmayerSystemStochastic::addRuleStochastic(unsigned char sym, std::vector<StochasticRule> expansions_with_ps) {
	rules[sym] = expansions_with_ps;
}
