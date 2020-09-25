#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

string convertToString(int);//convert

string replace(string, string, int, int);
//after one calculation, make a new string to calculate

string getresult(string);//do calculation

int getfrontnum(string a, int b);// to get front number

int getbacknum(string a, int b);//to get back number

double sqrt1(string); //do sqrt

// do assignment of x and y

string substitude(string, char, char);

char forassignleft(string);

char forassignright(string);

string arbitraryprecision(string, int, int, int);//for addition of large number

void formatStringWithZero(string &, unsigned long);

string addTwoString(string, string, string, string);

//
int main() {

    string s = "Hello";
    cout << "Please input your formula : " << endl;
    cin >> s;
    while (true) {
        //for arbitrary precision
        if (s.find('.') != string::npos&&s.find('+')!=string::npos) {

            int addpos = s.find('+');
            int dot1 = s.find_first_of('.');
            int dot2 = s.find_last_of('.');

            cout << "Answer is: " << endl;
            cout << arbitraryprecision(s, addpos, dot1, dot2) << endl;
            return 0;

        }

        if (s.find("x=") != string::npos || s.find("y=") != string::npos) {
            cout << "Please input your next parameter :" << endl;
            string s1 = "Hello again!";
            cin >> s1;
            cout << "Please input your formula with parameter :" << endl;
            string s2 = "Hello again an again!";
            cin >> s2;
            s2 = substitude(s2, forassignleft(s), forassignright(s));
            s2 = substitude(s2, forassignleft(s1), forassignright(s1));
            if (s2.find('(') != string::npos) {
                s = s2;
                continue;
            }

            cout << "Answer is: " << endl;
            cout << getresult(s2) << endl;
            return 0;
        }
        //do x y assignment

        if (s.find('(') != string::npos) {
            int front = s.find('(');
            int back = s.find(')');
            string s1 = s.substr(front + 1, back - 1 - front);
            if (s.find("sqrt") != string::npos) {
                cout << "Answer is:  " << endl;
                cout << setprecision(2) << sqrt1(s1) << endl;
                return 0;
            }
            s = replace(s, getresult(s1), front, back);
            continue;
        }
        break;
    }
    //do formula with bracket or sqrt()

    cout << "Answer is:  " << endl;
    cout << getresult(s) << endl;
    // most basic formula
    return 0;
}

string getresult(string a) {
    //multiply
    while (true) {
        int mul = a.find('*');
        if (mul == string::npos)  //when to stop
            break;
        int front = getfrontnum(a, mul); // find and get the number aside
        int back = getbacknum(a, mul);
        string mu1 = a.substr(front, mul - front);
        string mu2 = a.substr(mul + 1, back - mul);
        int mul1 = stoi(mu1), mul2 = stoi(mu2);
        //turn the number strings into int for calculator
        string multi = convertToString(mul1 * mul2);
        a = replace(a, multi, front, back);
        //make the result into the string

    }
    //addition
    while (true) {
        int add = a.find('+');
        if (add == string::npos)
            break;
        int front = getfrontnum(a, add);
        int back = getbacknum(a, add);
        string ad1 = a.substr(front, add - front);
        string ad2 = a.substr(add + 1, back - add);
        int add1 = stoi(ad1), add2 = stoi(ad2);
        string addi = convertToString(add1 + add2);
        a = replace(a, addi, front, back);

    }

    return a;
}

string convertToString(int a) {
    stringstream ss;
    ss << a;

    return ss.str();
}


string replace(string a, string b, int c, int d) {
    string e = a.erase(c, d - c + 1);
    string f = e.insert(c, b);
    return e;
}

int getfrontnum(string a, int b) {
    while (b >= 1 && isdigit(a[b - 1]) != 0) {
        b--;
    }
    return b;
}

int getbacknum(string a, int b) {
    while (b <= a.length() - 1 && isdigit(a[b + 1]) != 0) {
        b++;
    }
    return b;
}

double sqrt1(string todouble) {
    istringstream iss(todouble);
    double num = 0;
    iss >> num;
    double b = sqrt(num);

    return b;

}

char forassignleft(string a) {
    int pos = a.find('=');
    return a[pos - 1];
}

char forassignright(string a) {
    int pos = a.find('=');
    return a[pos + 1];
}

string substitude(string a, char b, char c) {
    for (char &d : a) {
        if (d == b)
            d = c;
    }
    return a;
}

string arbitraryprecision(string a, int b, int c, int d) {
    string s1 = a.substr(0, c);
    string s2 = a.substr(b + 1, d - b - 1);
    string s3 = a.substr(c + 1, b - c - 1);
    string s4 = a.substr(d + 1, a.length() - d - 1);

    return addTwoString(s1, s2, s3, s4);

}


void formatStringWithZero(string &s, unsigned long n) {
    for (unsigned long i = 0; i < n; i++) {
        s = "0" + s;
    }
}

string addTwoString(string s1, string s2, string s3, string s4) {
    if (s1.size() > s2.size()) {
        formatStringWithZero(s2, s1.size() - s2.size());
    } else {
        formatStringWithZero(s1, s2.size() - s1.size());
    }

    if (s3.size() >= s4.size()) {
        s1 += s3.substr(0, s4.size());
        s2 += s4;
    } else {
        s2 += s4.substr(0, s3.size());
        s1 += s3;
    }

    string res = "";
    int i, j;
    i = j = s1.size() - 1;
    int flag = 0;
    while (i >= 0 && j >= 0) {
        int n1 = s1[i--] - '0';
        int n2 = s2[j--] - '0';
        int r = (n1 + n2 + flag) % 10;
        flag = (n1 + n2 + flag) / 10;
        res = to_string(r) + res;
    }
    //最后flag为0或1 如果为1得加到res的最前端
    if (flag) {
        res = "1" + res;
    }


    string ans = " ";
    if (s3.size() >= s4.size()) {
        ans = res + s3.substr(s4.size(), s3.size() - s4.size());
        ans = ans.insert(ans.size() - s3.size(), ".");
        return ans;
    } else {
        ans = res + s4.substr(s3.size(), s4.size() - s3.size());
        ans = ans.insert(ans.size() - s4.size(), ".");
        return ans;
    }
}