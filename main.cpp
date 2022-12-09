#include <iostream>
#include <random>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;

// Takes in a string, removes all valid characters, and if anything remains - they must be invalid characters
bool invalid_char_in(string str) {
    for (char i : "roygbp") {
        str.erase( remove(str.begin(), str.end(), i), str.end() );
    }

    if (str.length() != 0) {
        return true;
    }
    return false;
}

uint8_t lesser_of(uint8_t a, uint8_t b) {
    if (a <= b) {
        return a;
    } else {
        return b;
    }
}

int main() {
    // Prints opening instructions regarding syntax
    // Note: this means that the actual game rules and strategies must be found elsewhere!
    cout << "MASTERMIND Game\n\nGuesses include 4 pegs and 10 guesses max before losing.\nSyntax guidelines:\n"
                 "\t* Peg colors are red(r), orange(o), yellow(y), green(g), blue(b), and purple(p).\n"
                 "\t* Example guesses are \"gryy\" or \"borb\".\n"
                 "\t* Result pegs are white(W) for right color wrong spot and black(B) for right color right spot.\n"
                 "\t* Example results are \"2B, 1W\" or \"3B, 0W\".\n" << endl;

    // Variables for the secret code
    char secret[4];
    string reveal_secret;
    // This count and the later "guess_count" both count quantities of each color present,
    // according to the pattern {'r', 'o', 'y', 'g', 'b', 'p'}
    uint8_t secret_count[6] = {0, 0, 0, 0, 0, 0};

    // The computer (the "CodeMaker") generating a random secret code
    {
        // Used to translate random numbers to corresponding characters to keep the distribution uniform
        map<uint8_t, char> rand_to_char = {{0, 'r'}, {1, 'o'}, {2, 'y'},
                                           {3, 'g'}, {4, 'b'}, {5, 'p'}};

        // Mechanisms needed to generate randomness
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> d(0, 5);
        uint8_t rand_num;

        // Populates secret variables
        for (char &i: secret) {
            rand_num = d(gen);
            secret_count[rand_num]++;
            i = rand_to_char[rand_num];
            reveal_secret += i;
        }
    }

    // Used to translate characters to indices that correspond to the guess_count and color_matched
    // Essentially the reverse of the rand_to_char seen above
    map<char, uint8_t> translate_char = {{'r', 0}, {'o', 1}, {'y', 2},
                                         {'g', 3}, {'b', 4}, {'p', 5}};

    // Variables for user input and guesses
    string input;
    char guess[4];
    uint8_t guess_count[6];

    // Variables for controlling the board and the outcomes
    string board = "\nBoard:\n";
    uint8_t black;
    uint8_t white;
    uint8_t color_matched[6];

    // This is needed to reset the guess_count and color_matched each round.
    uint8_t reset[6] = {0, 0, 0, 0, 0, 0};

    // The main loop of the game
    for (uint8_t n = 1; n <= 10; n++) {
        // Each loop begins by printing the current state of the board
        cout << board;

        // This block ensures the user enters a valid input before proceeding
        {
            bool invalid_input = true;
            while (invalid_input) {
                cout << "\nGuess " + to_string(n) + ": ";
                cin >> input;

                if (input.length() != 4) {
                    cout << "Invalid guess: must be 4 letters long";
                    continue;
                }
                if (invalid_char_in(input)) {
                    cout << "Invalid guess: invalid character(s) used";
                    continue;
                }
                invalid_input = false;
            }
        }

        // Resets game evaluation variables before evaluating
        memcpy(guess_count, reset, sizeof guess_count);
        memcpy(color_matched, reset, sizeof color_matched);
        black = 0;
        white = 0;

        // Turns the user's input into values the program can efficiently read
        for (int i = 0; i < 4; i++) {
            guess[i] = input[i];
            guess_count[translate_char[input[i]]]++;
        }

        // Matches color counts to get a preliminary idea of white peg count
        for (int i = 0; i < 6; i++) {
            color_matched[i] = lesser_of(guess_count[i], secret_count[i]);
        }

        // Matches guess to secret one-to-one to get black peg count and decrements the color_matched accordingly
        for (int i = 0; i < 4; i++) {
            if (guess[i] == secret[i]) {
                black++;
                color_matched[translate_char[guess[i]]]--;
            }
        }

        // Calculates white peg count according to the remaining color_matched values
        for (unsigned char i : color_matched) {
            white += i;
        }

        // Updates the board with the new result
        board += to_string(n) + ".\t" + input + "\t" + to_string(black) + "B, " + to_string(white) + "W\n";

        // Checks if the user won
        if (black == 4) {
            cout << board << "\nYou win!" << endl;
            break;
        }

        // Checks if the user lost
        if (n == 10) {
            cout << board << "\nMax guesses reached. You lose.\nThe code was: " + reveal_secret << endl;
        }
    }

    return 0;
}
