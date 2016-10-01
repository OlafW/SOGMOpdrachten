#include <iostream>
#include <fstream>
#include <string>

using std::string;

/*
    Small implementation of the solmization method of Guido d'Arezzo (c.q. 1026).
    Every vowel in a text corresponds to notes in a scale.
    The vowel sequence 'a e i o u' is mapped to the pitches of the double octave (g3 - g5).

    Input: text to be put to melody
    Output: notated melody in LilyPond format
*/

const int numSequence = 3;
const int numVowels = 5;
const char vowels[numVowels] = {'a', 'e', 'i', 'o', 'u'};
const int numDuration = 4;
const char duration[numDuration] = {'8', '4', '2', '1'};

const string vowelSequence[numSequence][numVowels] = {
    // a     e     i     o     u
    {"g,", "a,", "b,", "c,", "d,"},
    {"e", "f", "g", "a", "b"},
    {"c'", "d'", "e'", "f'", "g'"}
};

string solmization(string text) {
    string melody;

    // For every character in the text
    for (int n = 0; n < text.length(); n++) {
        char c = text[n];

        // If character is a vowel,
        // Choose a note based on character and random sequence index
        for (int v = 0; v < numVowels; v++) {
            if (c == vowels[v]) {
                int dur = 0;
                bool nextVowel = false;

                // Find the next vowel to calculate note duration
                for (int m = n+1; m < text.length()-1; m++) {
                    char c2 = text[m];

                    for (int v2 = 0; v2 < numVowels; v2++) {
                        if (c2 == vowels[v2]) {
                            int randomSeq = rand() % numSequence;
                            melody += vowelSequence[randomSeq][v] + duration[dur] + " ";

                            dur = 0;
                            nextVowel = true;
                        }
                        if (nextVowel) break;
                    }
                    if (nextVowel) break;
                    else {
                        if (c2 != ' ' && dur < numDuration-1) dur++;
                    }
                }
            }
        }
    }
    return melody;
}


int main(int argc, char** argv) {
    srand(time(NULL));

    string text;
    if (argc == 2) text = argv[1];
    else text = "ut queant laxis resonare";
    string melody = solmization(text);

    // Write to LilyPond file
    std::ofstream lilyPondFile;
    lilyPondFile.open("solmization.ly");

    lilyPondFile << "\\version \"2.16.0\" \n\n";
    lilyPondFile << "{ \n";
    lilyPondFile << "\t" << "\\clef \"bass\" \n";
    lilyPondFile << "\t" << melody << "\n";
    lilyPondFile << "} \n";
    lilyPondFile.close();

    return 0;
}

/*
make solmization
solmization
open solmization.ly
*/
