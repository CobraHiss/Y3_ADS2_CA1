#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <array>
using namespace std;

/****************************************************************************************
*    Title: Vigenère cipher / Cryptanalysis
*    Author: Unknown Good Samaritan
*    Date: 07/04/2016
*    Code Version: N/A
*    Availability: https://rosettacode.org/wiki/Vigen%C3%A8re_cipher/Cryptanalysis#C.2B.2B
*****************************************************************************************/

typedef array<pair<char, double>, 26> FreqArray;

class VigenereDecryption
{
private:
	array<double, 26> encryption;
	array<double, 26> decryption;
	FreqArray freq;

	// Update the freqs array
	FreqArray& frequency(const string& input)
	{

		for (char c = 'A'; c <= 'Z'; ++c)
			freq[c - 'A'] = make_pair(c, 0);

		for (size_t i = 0; i < input.size(); ++i)
			freq[input[i] - 'A'].second++;

		return freq;
	}

	double correlation(const string& input)
	{
		double result = 0.0;
		frequency(input);

		sort(freq.begin(), freq.end(), [](pair<char, double> u, pair<char, double> v)->bool
		{ return u.second < v.second; });

		for (size_t i = 0; i < 26; ++i)
			result += freq[i].second * decryption[i];

		return result;
	}

public:
	VigenereDecryption(const array<double, 26>& targetFreqs)
	{
		encryption = targetFreqs;
		decryption = encryption;
		sort(decryption.begin(), decryption.end());
	}

	pair<string, string> analyze(string input)
	{
		string cleaned;
		for (size_t i = 0; i < input.size(); ++i)
		{
			if (input[i] >= 'A' && input[i] <= 'Z')
				cleaned += input[i];
			else if (input[i] >= 'a' && input[i] <= 'z')
				cleaned += input[i] + 'A' - 'a';
		}

		size_t bestLength = 0;
		double bestCorr = -100.0;

		// Assume that if there are less than 20 characters
		// per column, the key's too long to guess
		for (size_t i = 2; i < cleaned.size() / 20; ++i)
		{
			vector<string> pieces(i);
			for (size_t j = 0; j < cleaned.size(); ++j)
				pieces[j % i] += cleaned[j];

			// The correlation increases artificially for smaller
			// pieces/longer keys, so weigh against them a little
			double corr = -0.5*i;
			for (size_t j = 0; j < i; ++j)
				corr += correlation(pieces[j]);

			if (corr > bestCorr)
			{
				bestLength = i;
				bestCorr = corr;
			}
		}

		if (bestLength == 0)
			return make_pair("Text is too short to analyze", "");

		vector<string> pieces(bestLength);
		for (size_t i = 0; i < cleaned.size(); ++i)
			pieces[i % bestLength] += cleaned[i];

		vector<FreqArray> freqs;
		for (size_t i = 0; i < bestLength; ++i)
			freqs.push_back(frequency(pieces[i]));

		string key = "";
		for (size_t i = 0; i < bestLength; ++i)
		{
			sort(freqs[i].begin(), freqs[i].end(), [](pair<char, double> u, pair<char, double> v)->bool
			{ return u.second > v.second; });

			size_t m = 0;
			double mCorr = 0.0;
			for (size_t j = 0; j < 26; ++j)
			{
				double corr = 0.0;
				char c = 'A' + j;
				for (size_t k = 0; k < 26; ++k)
				{
					int d = (freqs[i][k].first - c + 26) % 26;
					corr += freqs[i][k].second * encryption[d];
				}

				if (corr > mCorr)
				{
					m = j;
					mCorr = corr;
				}
			}

			key += m + 'A';
		}

		string result = "";
		for (size_t i = 0; i < cleaned.size(); ++i)
			result += (cleaned[i] - key[i % key.length()] + 26) % 26 + 'A';

		return make_pair(result, key);
	}
};

int main()
{
	ifstream ifs("Ciphertext.txt");
	string input((istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	array<double, 26> english = {
		0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
		0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
		0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
		0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
		0.01974, 0.00074 };

	VigenereDecryption va(english);
	pair<string, string> output = va.analyze(input);

	cout << "Decrypted Key: " << output.second << endl << endl;
	cout << "Decrypted Text: " << output.first << endl;

	system("pause");
}