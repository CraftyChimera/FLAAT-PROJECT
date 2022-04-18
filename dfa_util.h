#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int dfa_simulator(int initial_state, vector<char> input_alphabet, vector<int> final_states, vector<int> states, map<pair<int, char>, int> transition)
{
    int current_state = initial_state;
    cout << "\nInput Alphabets\n";
    for (auto &s : input_alphabet)
        cout << s << " ";
    cout << "\nStates\n";
    for (auto &s : states)
        cout << s << " ";
    cout << "\nInitial State\n"
         << initial_state << "\n";
    cout << "\nFinal States\n";
    for (auto &s : final_states)
        cout << s << " ";
    cout << "\nTransition Function\n";
    for (auto &s : transition)
        cout << s.first.first << "," << s.first.second << " -> " << s.second << "\n";
    cout << "\n";

    string input;
    cout << "Input String: ";
    getline(cin, input);
    for (size_t i = 0; i < input.size(); i++)
    {
        cout << "\n";
        cout << i + 1 << ":";
        string x(input.begin() + i, input.end());
        cout << "(" << x << ", " << current_state << ")";
        pair<int, char> lhs{current_state, input[i]};
        if (find(input_alphabet.begin(), input_alphabet.end(), input[i]) == input_alphabet.end())
        {
            cout << "\nInvalid Character found\n";
            return 22;
        }
        if (transition.find(lhs) != transition.end())
            current_state = transition[lhs];
        cout << "\n";
    }
    cout << "\n";
    cout << input.size() + 1 << ":( , " << current_state << ")";
    cout << "\n\n";
    if (find(final_states.begin(), final_states.end(), current_state) != final_states.end())
        cout << "String is accepted by DFA\n";
    else
        cout << "String is not accepted by DFA\n";
    return 0;
}