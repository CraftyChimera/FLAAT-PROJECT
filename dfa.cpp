#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
using namespace std;
// TODO: Add validation checks and Error Handling
void tokenize(string const &str, const char delim, vector<string> &out)
{
    std::stringstream ss(str);
    std::string s;
    while (std::getline(ss, s, delim))
        out.push_back(s);
}

int main()
{
    ifstream in;
    string input_line;
    vector<char> input_alphabet;
    vector<int> states, final_states;
    map<pair<int, char>, int> transition;
    int line = 0, initial_state = 0, current_state = 0;
    in.open("dfa_input.txt");
    while (in >> input_line)
    {
        line++;
        if (line == 1)
        {
            vector<string> temp;
            tokenize(input_line, ',', temp);
            for (auto &s : temp)
                input_alphabet.push_back(s[0]);
        }
        if (line == 2)
        {
            vector<string> temp;
            tokenize(input_line, ',', temp);
            for (auto &s : temp)
            {
                int x = s[0] - '0';
                states.push_back(x);
            }
        }
        if (line == 3)
        {
            initial_state = input_line[0] - '0';
        }
        if (line == 4)
        {
            vector<string> temp;
            tokenize(input_line, ',', temp);
            for (auto &s : temp)
            {
                int x = s[0] - '0';
                final_states.push_back(x);
            }
        }
        if (line > 4 && input_line != "")
        {
            vector<string> temp;
            tokenize(input_line, ',', temp);
            pair<int, char> lhs{temp[0][0] - '0', temp[1][0]};
            transition[lhs] = temp[2][0] - '0';
        }
    }
    current_state = initial_state;
    cout << "\nInput Alphabets\n";
    for (auto &s : input_alphabet)
        cout << s << " ";
    cout << "\nStates\n";
    for (auto &s : states)
        cout << s << " ";
    cout << "\nFinal States\n";
    for (auto &s : final_states)
        cout << s << " ";
    cout << "\nTransition Function\n";
    for (auto &s : transition)
        cout << s.first.first << "," << s.first.second << " -> " << s.second << "\n";
    cout << "\n";

    string input;
    cout << "Input String: ";
    cin >> input;
    for (size_t i = 0; i < input.size(); i++)
    {
        cout << "\n";
        cout << i + 1 << ":";
        string x(input.begin() + i, input.end());
        cout << "(" << x << ", " << current_state << ")";
        pair<int, char> lhs{current_state, input[i]};
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