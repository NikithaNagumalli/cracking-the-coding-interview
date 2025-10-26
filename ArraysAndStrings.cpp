#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <unordered_set>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::to_string;
using std::unordered_set;

// 1.1 - only works for lowercase letters
bool isUnique(string x) {
    char seen;
    for (char c : x) {
        int charNum = c - 'a';
        int charBit = 1 << charNum;
        //cout << "Binary representation of " << bit << ": " << std::bitset<sizeof(int) * 8>(bit) << endl;
        if (seen & charBit) {
            return false;
        }
        seen |= charBit;

    }
    return true;
}

// 1.2 - only works for lowercase letters
bool checkPermutation(string x, string y) {
    vector<int> counts(26, 0);
    if (x.size() != y.size()) { return false; }
    for (char c : x) {
        counts[c - 'a'] += 1;
    }

    for (char c : y) {
        if (--counts[c - 'a'] < 0) {
            return false;
        }
    }
    return true;

}

// 1.3
string URLify(string x) {
    int spaceCount = 0;
    for (char c : x) {
        if (c == ' ') {
            spaceCount++;
        }
    }

    string result(x.size() + spaceCount * 2, ' ');
    int resultIndex = 0;
    for (char c : x) {
        if (c == ' ') {
            result[resultIndex] = '%';
            result[++resultIndex] = '2';
            result[++resultIndex] = '0';
        } else {
            result[resultIndex] = c;
        }
        resultIndex++;
    }
    return result;
}

// 1.4 
bool palindromePermutation(string x) {
    vector<int> counts(26, 0);
    for (char c : x) {
        counts[c - 'a']++;
    }
    int oddCount = 0;
    for (int i : counts) {
        if (i % 2 != 0) {
            oddCount++;
        }
    }
    return oddCount <= 1;
}

// 1.5
bool oneAway(string x, string y) {
    cout << "x: " << x << " y: " << y << endl;
    if (x.size() == y.size()) {
        bool diffChar = false;
        for (int i = 0; i < x.size(); i++) {
            if (x[i] != y[i]) {
                if (diffChar) { return false; }
                diffChar = true;
            }
        }
        return true;
    } else if (x.size() - y.size() == 1) { // car , cr
        bool diffChar = false;
        int xIndex = 0;
        for (int i = 0; i < y.size(); i++) {
            if (x[xIndex] != y[i]) {
                if (diffChar) { return false; }
                diffChar = true;
                xIndex++;
            }
            xIndex++;
        }
        return true;
    } else if (x.size() - y.size() == -1) {
        bool diffChar = false;
        int yIndex = 0;
        for (int i = 0; i < x.size(); i++) {
            if (x[i] != y[yIndex]) {
                if (diffChar) { return false; }
                diffChar = true;
                yIndex++;
            }
            yIndex++;
        }
        return true;
    } else {
        return false;
    }
}

// 1.6
string stringCompression(string x) {
    if (x.size() == 0) {
        return x;
    }
    char prevChar = x[0];
    int currCount = 1;
    string result;
    for (int i = 1; i < x.size(); i++) {
        if (prevChar == x[i]) {
            currCount++;
        } else {
            result.append(1, prevChar);
            result.append(to_string(currCount));
            currCount = 1;
        }
        if (i == x.size() - 1) {
            result.append(1, x[i]);
            result.append(to_string(currCount));
        }
        prevChar = x[i];
    }
    if (result.size() < x.size()) {
        return result;
    } else {
        return x;
    }
}

// 1.7
void rotateMatrix(vector<vector<int>>& matrix) {
    // int topLeft = matrix[0][0];
    // int topRight = matrix[0][n - 1];
    // int bottomLeft = matrix[n - 1][0];
    // int bottomRight = matrix[n - 1][n - 1];

    // int temp = matrix[0][0];
    // matrix[0][0] = matrix[n - 1][0];
    // matrix[n - 1][0] = matrix[n - 1][n - 1];
    // matrix[n - 1][n - 1] = matrix[0][n - 1];
    // matrix[0][n - 1] = temp;

    int n = matrix.size();

    for (int layer = 0; layer < n / 2; layer++) {
        for (int i = layer; i < n - 1 - layer; i++) {
            // int topLeft = matrix[layer][i];
            // int topRight = matrix[i][n - 1 - layer];
            // int bottomLeft = matrix[n - 1 - i][layer];
            // int bottomRight = matrix[n - 1 - layer][n - 1 - i];
            // cout << "topLeft: " << topLeft << " topRight: " << topRight << " bottomLeft: " << bottomLeft << " bottomRight: " << bottomRight << endl;

            int temp = matrix[layer][i];
            matrix[layer][i] = matrix[n - 1 - i][layer];
            matrix[n - 1 - i][layer] = matrix[n - 1 - layer][n - 1 - i];
            matrix[n - 1 - layer][n - 1 - i] = matrix[i][n - 1 - layer];
            matrix[i][n - 1 - layer] = temp;
        }
    }
        // int topLeft = matrix[0][i];
        // int topRight = matrix[i][n - 1];
        // int bottomLeft = matrix[n - 1 - i][0];
        // int bottomRight = matrix[n - 1][n - 1 - i];
        // cout << "topLeft: " << topLeft << " topRight: " << topRight << " bottomLeft: " << bottomLeft << " bottomRight: " << bottomRight << endl;
        
        // int temp = matrix[0][i];
        // matrix[0][i] = matrix[n - 1 - i][0];
        // matrix[n - 1 - i][0] = matrix[n - 1][n - 1 - i];
        // matrix[n - 1][n - 1 - i] = matrix[i][n - 1];
        // matrix[i][n - 1] = temp;
}

// 1.8
void zeroMatrix(vector<vector<int>>& matrix) {
    unordered_set<int> rowsWithZero;
    unordered_set<int> colsWithZero;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == 0) {
                rowsWithZero.insert(i);
                colsWithZero.insert(j);
            }
        }
    }

    for (int i = 0; i < matrix.size(); i++) {
        if (rowsWithZero.find(i) != rowsWithZero.end()) {
            for (int j = 0; j < matrix[0].size(); j++) {
                matrix[i][j] = 0;
            }
        }
    }

    for (int j = 0; j < matrix[0].size(); j++) {
        if (colsWithZero.find(j) != colsWithZero.end()) {
            for (int i = 0; i < matrix.size(); i++) {
                matrix[i][j] = 0;
            }
        }
    }
}

// 1.9
bool stringRotation(string x, string y) {
    y.append(y);
    cout << y << endl;
    // return y.find(x) != string::npos;
    size_t index = y.find(x);
    return index != string::npos && index < sizeof(y) && index + sizeof(x) > sizeof(y);
}

int main() {
    // cout << "hello: " << isUnique("hello") << endl;
    // cout << "world: " << isUnique("world") << endl;

    // cout << checkPermutation("ii", "ii") << endl;
    // cout << URLify("h i  there fri en d") << endl;

    // cout << palindromePermutation("bear") << endl;

    // cout << oneAway("pale", "bake") << endl;

    //cout << stringCompression("aabcccccaaa") << endl;

    // 0 1
    // 0 1

    // 0 0 
    // 1 1
    // vector<vector<int>> q = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    // vector<vector<int>> q = {{0, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 0, 12}, {13, 14, 15, 16}};
    // for (int i = 0; i < q.size(); i++) {
    //     for (int j = 0; j < q[i].size(); j++) {
    //         //cout << "i: " << i << " j: " << j << " value: " << q[i][j] << endl;
    //         cout << " " << q[i][j];
    //     }
    //     cout << "\n";
    // }
    // cout << "----" << endl;
    // // rotateMatrix(q);
    // zeroMatrix(q);
    // for (int i = 0; i < q.size(); i++) {
    //     for (int j = 0; j < q[i].size(); j++) {
    //         //cout << "i: " << i << " j: " << j << " value: " << q[i][j] << endl;
    //        cout << " " << q[i][j];
    //     }
    //     cout << "\n";
    // }
    // cout << "----" << endl;

    cout << stringRotation("rot", "trotro") << endl;
}

