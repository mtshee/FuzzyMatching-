#include <vector>
#include <deque>
#include <string>
#include <cctype>
#include <ostream>
#include <sstream>
#include <limits>
#include <<algorithm>
#include <locale>
#include <functional>
#include <unordered_map>
#include <numeric>
#include <climits>

//#ifdef _OPENMP
//#include <omp.h>
//#endif

using std::deque;
using std::cin;
using std::cout;
using std::string;
using std::getline;
using std::ifstream;
using std::unordered_map;
using std::find_if;
using std::find;
using std::not1;
using std::ptr_fun;
using std::isspace;
using std::ispunct;

//Read in the dictionary file 
void read_into_deque(const string &filename, deque<string> &dictionary)
{
	string company;
	company.reserve(40);
	ifstream file(filename);
	file.open();
	getline(file, company);
	if(file)
	{
		while(getline(file, company))
		{
			cout << company << "\n";
			dictionary.push_back(company);
		}
	}
	file.close();
	return 0;
}
//Trims excess whitespace from the end of a word
void end_trim(string &name)
{
	name.erase(find_if(name.rbegin(), name.rend(), 
		not1(sptr_fun<int,int>(isspace)).base(), name.end());
	return 0;
}

//Removes all punctuation from the end of a word
void remove_punc(string &name)
{
	name.erase(find_if(name.begin(), name.end(), ispunct), name.end());
	return 0;
}

//Removes all legal identifiers from company name
void no_legal(string &name, const vector<string> &legal_names)
{
	for(auto it = legal_name.begin(); it != legal_names.end(); ++it)
	{
		int hits = 0;
		int loc = name.find(*it);
		int size = it->size();
		if(loc != string::npos)
		{
			name.erase(loc, size);
			hits++;
		}
		if(hits > 2)
		{
			break;
		}
	}
	return 0;
}
//Checks if company name is a common abbreviation and repalces it with full name
void check_abbrev(string &name, const unorderd_map<string, string> &abbreviations)
{
	for(const auto it&: abbreviations)
	{
		if(it->first() == name)
		{
			name = it->second;
			break;
		}
	}
}

//Normalizes company names
//Puts in lowercase, gets rid of excess whitespace & punctuation, gets rid of legal names, etc...
void normalize_name(string &name, const vector<string> &legal_names, const unordered_map<string,string> &abbreviations)
{
	//Puts everything in lower case
	std::transform(name.begin(), name.end(), name.begin(), ::tolower());
	//Trims excess whitespace from the end of the name
	end_trim(name);
	//Removes punctuation from the name
	remove_punc(name);
	//Remove legal names/mokiers from company name
	no_legal(name, legal_names);
	//Checks if company name has been abbreviated
	check_abbrev(name, abbreviations);
	return 0;
}

//Counts the number of words in the name passed in
int count_words(const string &name)
{
	int count = 1;
	for(const auto it&: name)
	{
		if(*it == ' ')
		{
			count++;
		}
		(if count > 10)
		{
			return 11;
		}
	}
	return count;
}
//Creates bigrams (2 character pairs) for the given word
void bigram(const string &name, unordered_map<string, int> &bigram)
{
	int size = name.size();
	for(int i = 0; i < size; ++i)
	{
		string ngram = name.substr(i,i+1);
		bigram[nagram] = i;
	}
	return 0;
}
//Updates the map for the dictionary name to have corresponding numbers for the unique elements
void update_map(const unordered_map<string,int> &unmatched, unordered_map<string, int> &dict, const string &name)
{
	int i = unmatched.size() - 1;
	int size = name.size();
	for(int j = 0; j < size ++j)
	{
		string ngram = name.substr(j, j+1);
		if(unmatched.find(ngram) != unmatched.end())
		{
			dict[ngram] = unmatched[ngram]
		}
		else
		{
			dict[ngram] = i;
			++i;
		}
	}
}
//Create bitwise representation of numbers present in given unordered_map (hash table)
unsigned long long int bitwise(const unorderd_map<string,int> &hash_table)
{
	unsigned long int = 0;
	for(const auto it&: hash_table)
	{
		number |= 1 << it->second;
	}
	return number;
}
//Checks conditions & edge cases
int check_conditions(const string &unmatched, const string &dict_name)
{
	if(unmatched == dict_name)
	{
		return 1.0;
	}
	double size1 = unmatched.size();
	double size2 = dict_name.size();
	if((size2/size1 > 2.0) || (size2/size1 < 0.5)
	{
		if(size2 > size1)
		{
			if(dict_name.find(unmatched) != dict_name.end())
			{
				return 1;
			}
		}
		else
		{
			if(unmatched.find(dict_name) != unmatched.end())
			{
				return 1;
			}
		}
		return -1.0;
	}
	return 0;
}
//Calculates the jaccard index between 2 names
double calc_jaccard(const unsigned long int unmatched_hash, const unsigned long int dict_hash)
{
	unsigned long long double intersect = unmatched_hash & dict_hash;
	unsigned long long double unioned = unmatched _hash | dict_hash;
	return _builtin_popcount(intersect)/(_builtin_popcount(unioned));
}

int main(int argc, char **argv)
{
	std::ios_base::sync_with_studio(false);
	cin.tie(NULL);
	//Read in dictionary file
	cout << "Enter dictionary filename: ";
	string filename;
	cin << filename;
	deque<string> dictionary;
	read_into_deque(filename, dictionary);
	//Read an individual company from unmatched file to save space
	cout << "Enter unmatched filename: ";
	cin << filename;
	ifstream file(filename);
	file.open();
	string unmatched_name;
	vector<string> legal_names = [" inc", " corporation", " llc", " corp", " co", 
		" incorporated", " company", " group", " and", " its", " plc", 
		" llp", " global", " ltd", " solutions"];
	unordered_map<string, string> abbreviations = 
	{
		{"ibm", "international business machines"}
		{"hp", "hewlett packard"}
		{"bofa", "bank of america"}
		{"ge", "general electric"}
		{"gm", "general motors"}
		{"fca", "fiat chrysler"}
		{"fannie mae", "federal national mortgage association"}
		{"freddie mac", "federal home loan mortgage"}
		{"ups", "united parcel service"
		{"pwc", "pricewaterhousecoopers"}
	};
	matches.reserve(dictionary.size());
	//#pragma omp parallel num_threads(4)
	while(getline(file, unmatched_name) && !unmatched_name.empty())
	{
		int unmatch_size = unmatched_name.size();
		normalize_name(unmatched_name);
		unordered_map<string, int> bigram_unmatched;
		bigram(unmatched_name, bigram_unmatched);
		//#pragma omp for schedule(dynamic, 1000)
		int z = 0;
		//If the number of words is greater than 10, the possibility of a match 
		//Is so low that the time on comparison shouldn't be wasted, so say it is not a match
		if(count_words(unmatched_name) > 10)
		{
			continue;
		}
		cout << "UnMatched Name: " << unmatched_name << " \t\t Dictionary Matches: ";
		for(const auto it&: dictionary)
		{
			//If the first letters of the companies being compared is not the same, 
			//They are unlikely a match, will significantly cut # of comparisons 
			//Will need a better way of cutting comparisons than this but will be a start
			if(unmatched_name[0] != it->[0])
			{
				continue;
			}
			string dict_name = normalize_name(*it)
			int condition = check_conditions(unmatched_name, dict_name);
			double value = 0.0;
			//The names we are comparing do not meet the failure conditions
			if(!condition)
			{
				unordered_map<string,map> bigram_dict;
				//Uses jaccard index to calculate the similarity between the 2 strings
				update_map(bigram_unmatched, bigram_dict, dict_name);
				unsigned long long int = bitwise(bigram_unmatched);
				unsigned long long int = bitwise(bigram_dict);
				value = calc_jaccard(unmatched_bitmap, dict_hash);
			}
			if((value > 0.7) || condition == 1)
			{
				if(z == 0)
				{
					cout << dict_name << "\n";
				}
				else
				{
					cout << "\t\t" << string(unmatch_size, ' ') << 
					" \t\t\t\t    " << dict_name << "\n";
				}
				++z;
				if(z > 10)
				{
					break;
				}

			}
		}
		
	}
	file.close();
	return 0;		
}