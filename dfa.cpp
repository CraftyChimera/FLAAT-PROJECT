#include "dfa_util.h"
using namespace std;
void tokenize(string const &str, const char delim, vector<string> &out)
{
    stringstream ss(str);
    string s;
    while (getline(ss, s, delim))
        out.push_back(s);
}

int main()
{
    ifstream in;
    string input_line;
    vector<char> input_alphabet;
    vector<int> states, final_states;
    map<pair<int, char>, int> transition;
    int line = 0, initial_state = 0;
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
                int x = stoi(s);
                states.push_back(x);
            }
        }
        if (line == 3)
        {
            initial_state = stoi(input_line);
        }
        if (line == 4)
        {
            vector<string> temp;
            tokenize(input_line, ',', temp);
            for (auto &s : temp)
            {
                int x = stoi(s);
                final_states.push_back(x);
            }
        }
        if (line > 4 && input_line != "")
        {
            vector<string> temp;
            tokenize(input_line, ',', temp);
            pair<int, char> lhs{stoi(temp[0]), temp[1][0]};
            transition[lhs] = stoi(temp[2]);
        }
    }
    int x = dfa_simulator(initial_state, input_alphabet, final_states, states, transition);
    return x;
}