#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

string Dterm(long long int x, int k) {
    string vec, s = ")";
    while (x != 0) { vec += ('0' + x % 2); x /= 2; }
    while (vec.length() < k) {
        vec += '0';
    }
    reverse(vec.begin(), vec.end());


    for (int i = k, j = 0; i >= 0; --i) {
        if (vec[i] == '1') s = char('a' + i) + s;
        if (vec[i] == '0') { s = char('a' + i) + s; s = '!' + s; }
        if (i != 0 && i != k) { s = " \\/ " + s; }
    }

    s = '(' + s;

    return s;
}


string SKNF(string x) {
    string s;

    for (int i = 0; i < x.length(); i++) {
        if (x[i] == '0') {
            s += Dterm((x.length() - 1) - i, 1 + int(log2(x.length() - 0.5)));

            if (x.find('0', i + 1) != -1) { s += " /\\ "; }
        }
    }
    return s;
}


int main()
{
    setlocale(LC_ALL, "rus");
    ifstream in("input.txt");
    ofstream out("output.txt");

    vector <string> m;
    string s;
    for (int i = 0; i < 30; i++) {
        if (i == 14) {
            cout << "                                                    СКНФ Построены" << "                                                    " << endl;
        }
        else {
            cout << "                                                                                                                       " << endl;
        }
    }

    while (!in.eof()) {
        getline(in, s);
        m.push_back(s);
    }

    for (int i = 0; i < m.size(); i++) {
        m[i] = SKNF(m[i]);
    }

    for (int i = 0; i < m.size(); i++) {
        out << i + 1 << ") ";
        if (m[i].length() != 0) { out << m[i] << endl; }
        else {
            out << "СКНФ не существует!" << endl;
        }
    }

    in.close();
    out.close();

    system("PAUSE");
}