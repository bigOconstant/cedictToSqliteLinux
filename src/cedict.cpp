#include "cedict.h"
#include <algorithm>
#include <sstream>
#include <iterator>
#include <regex>
#include <functional>
#include <numeric>
#include <algorithm>
// Look for u values replace u: with ü
cedict::cedict() {
	this->Traditional = "";
	this->Simplified = "";
	this->PinyinNumbered = "";
	this->Pinyin = "";
	
}

cedict::cedict(std::string Traditional, std::string Simplified, std::string PinyinNumbered, std::string Pinyin) {

	this->Traditional = Traditional;
	this->Simplified = Simplified;
	this->PinyinNumbered = PinyinNumbered;
	this->Pinyin = Pinyin;
	

};

cedict::cedict(const cedict& c2) {
	Traditional = c2.Traditional;
	Simplified = c2.Simplified;
	PinyinNumbered = c2.PinyinNumbered;
	Pinyin = c2.Pinyin;
	//Definition = c2.Definition;
}

std::string cedict::getTraditional() {
	return this->Traditional;
}
int cedict::getId() {
	return this->Id;
}
std::string cedict::getSimplified() {
	return this->Simplified;
}
std::string cedict::getPinyin() {
	return this->Pinyin;
}
std::string cedict::getPinyinNumbered() {
	return this->PinyinNumbered;
}
std::vector<std::string> cedict::getDefinitions() {
	return this->Definitions;
}

void cedict::setId(int input) {
	this->Id = input;
}

void cedict::setTraditional(std::string input) {
	this->Traditional = input;
}

void cedict::setSimplified(std::string input) {
	this->Simplified = input;
}

void cedict::setPinyinNumbered(std::string input) {
	this->PinyinNumbered = input;
}
void cedict::addDefinition(std::string input) {
	this->Definitions.push_back(input);
}

void cedict::setBasicPinyin(std::string str){
	str.erase(std::remove(str.begin(), str.end(), '1'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '2'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '3'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '4'), str.end());
	str.erase(std::remove(str.begin(), str.end(), '5'), str.end());
	this->BasicPinyin = str;

}
std::string cedict::getBasicPinyin(){
	return this->BasicPinyin;
}

int detectTone(std::string input){
	if(input.find("1") != std::string::npos){
		return 1;
	}
	if(input.find("2") != std::string::npos){
		return 2;
	}
	if(input.find("3") != std::string::npos){
		return 3;
	}
	if(input.find("4") != std::string::npos){
		return 4;
	}
	if(input.find("5") != std::string::npos){
		return 5;
	}
	return 0;
}


void cedict::setPinyin(std::string input) {

	std::istringstream iss(input);
	std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>{}};

	std::vector<std::string> output;// = "";
	for(auto it = tokens.begin(); it < tokens.end(); ++it){
		output.push_back(convertToTones(*it));
		
	}

	std::string combined;
	int counter = 0;
	for(auto it = output.begin(); it < output.end(); ++it){
		combined += *it;
		if(counter< combined.length()){
			combined += " ";
		}
	}

	this->Pinyin = combined;
}

std::string cedict::convertToTones(std::string input) {
	std::string atones[5] = {"ā", "á", "ǎ", "à", "a"};
	std::string etones [5] = {"ē", "é", "ě", "è", "e"};
	std::string itones [5] = {"ī", "í", "ǐ", "ì", "i"};
	std::string otones [5] = {"ō", "ó", "ǒ", "ò", "o"};
	std::string udottones [5] = {"ǖ", "ǘ", "ǚ", "ǜ", "ü"};



	// Look for u values replace u: with ü
	std::regex_replace(input, std::regex("u:"), "ü");

//replace a or e with its tone because thats one of the easiest
	//A and e trump all other vowels and always take the tone mark.
	// There are no Mandarin syllables in Hanyu Pinyin that contain both a and e.


	if((input.find("a") != std::string::npos) || (input.find("A") != std::string::npos) || (input.find("e") != std::string::npos) || (input.find("E") != std::string::npos) ) {
		int tone =detectTone(input);
		if(tone != 0){
			std::string str = "a";
			input = std::regex_replace(input, std::regex("a"), atones[tone-1]);
			input = std::regex_replace(input, std::regex("e"), etones[tone-1]);
		}

	}
	//In the combination ou, o takes the mark.
	else if ((input.find("ou") != std::string::npos) || (input.find("Ou") != std::string::npos)){
		int tone =detectTone(input);
		if(tone != 0){
			std::string str = "o";
			input = std::regex_replace(input, std::regex("o"), otones[tone-1]);
			
		}
	}

	//Last case, we have to assign the tone mark to the last vowel of the word
	//We will just loop through to find the last vowel and replace it.
    //TODO
	else{
		int positiontobereplaced = 0;
		std::string voweltoreplace = "";
		bool vowelexist = false;

		for(auto it = input.begin(); it < input.end(); ++it){
			switch(*it){
				case 'i':
				case 'o':
				case 'u':
				case 'I':
				case 'O':
				case 'U':
					positiontobereplaced = std::distance(input.begin(), it);
					voweltoreplace = *it;
					vowelexist = true;
					break;	
			}
		}
		if(vowelexist){
			int tone =detectTone(input);


			if(voweltoreplace == "i"){
						
						input.replace(positiontobereplaced,std::string("i").length(),itones[tone-1]);
			}
			else if(voweltoreplace == "o"){
              input.replace(positiontobereplaced,std::string("o").length(),otones[tone-1]);
			}
			else if(voweltoreplace == "u"){
              input.replace(positiontobereplaced,std::string("u").length(),udottones[tone-1]);
			}
			else if(voweltoreplace == "i"){
              input.replace(positiontobereplaced,std::string("I").length(),itones[tone-1]);
			}
			else if(voweltoreplace == "O"){
              input.replace(positiontobereplaced,std::string("O").length(),otones[tone-1]);
			}
			else if(voweltoreplace == "U"){
               input.replace(positiontobereplaced,std::string("u").length(),udottones[tone-1]);
			}

		}

		}
	
	input.erase(std::remove(input.begin(), input.end(), '1'), input.end());
	input.erase(std::remove(input.begin(), input.end(), '2'), input.end());
	input.erase(std::remove(input.begin(), input.end(), '3'), input.end());
	input.erase(std::remove(input.begin(), input.end(), '4'), input.end());
	input.erase(std::remove(input.begin(), input.end(), '5'), input.end());
	return input;
}

void cedict::setDefinitions(std::string input) {
	std::stringstream ss(input);
    std::string token;
	char c = '/';
    input.erase(0, 1);
    input.erase(input.size() - 1);
    input.erase(input.size() - 1);

    std::string definition = "";

    
    for (auto it = input.cbegin() ; it != input.cend(); ++it) {
        if((*it) == '/'){
            this->addDefinition(definition);
            definition = "";
        }else{
            definition += (*it);
        }
		
	}
}
void cedict::printDefinitions(){
	for(auto it = this->Definitions.begin(); it < this->Definitions.end(); ++it){
		std::cout<<*it<<std::endl;
	}
}

