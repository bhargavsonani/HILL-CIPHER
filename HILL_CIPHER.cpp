#include <iostream>
#include <vector>
#include <string>

using namespace std;

int mod(int a, int b) {
    return (a % b + b) % b;
}

vector<int> matrixMul(vector<vector<int>>& keyM, vector<int>& a, int modValue) {
    vector<int> res(2, 0);  
    for (int i = 0; i < keyM.size(); i++) {
        for (int j = 0; j < keyM[i].size(); j++) { 
            res[i] += keyM[i][j] * a[j];
        }
        res[i] = mod(res[i], modValue); 
    }
    return res;
}

vector<vector<int>> InverseMatrix(vector<vector<int>>& matrix, int modValue) {
    int determinant = mod(matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0], modValue);

    int inverseDeterminant = 0;
    for (int i = 0; i < modValue; i++) {
        if (mod(determinant * i, modValue) == 1) {
            inverseDeterminant = i;
            break;
        }
    }

    vector<vector<int>> inverseMatrix(2, vector<int>(2));
    inverseMatrix[0][0] = matrix[1][1];
    inverseMatrix[1][1] = matrix[0][0];
    inverseMatrix[0][1] = -matrix[0][1];
    inverseMatrix[1][0] = -matrix[1][0];

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inverseMatrix[i][j] = mod(inverseMatrix[i][j] * inverseDeterminant, modValue);
        }
    }

    return inverseMatrix;
}

string encrypt(string plaintext, vector<vector<int>>& keyMatrix) {
    vector<int> plaintextVector(2);
    string encryptedText;

    for (int i = 0; i < plaintext.length(); i += 2) {
        plaintextVector[0] = plaintext[i] - 'A';
        plaintextVector[1] = plaintext[i + 1] - 'A';
        vector<int> encryptedVector = matrixMul(keyMatrix, plaintextVector, 26);

        encryptedText += (char)(encryptedVector[0] + 'A');
        encryptedText += (char)(encryptedVector[1] + 'A');
    }

    return encryptedText;
}

string decrypt(string ciphertext, vector<vector<int>>& keyMatrix) {
    vector<int> ciphertextVector(2);
    vector<vector<int>> inverseKeyM = InverseMatrix(keyMatrix, 26);
    string decryptedText;

    for (int i = 0; i < ciphertext.length(); i += 2) {
        ciphertextVector[0] = ciphertext[i] - 'A';
        ciphertextVector[1] = ciphertext[i + 1] - 'A';
        vector<int> decryptedArr = matrixMul(inverseKeyM, ciphertextVector, 26);

        decryptedText += (char)(decryptedArr[0] + 'A');
        decryptedText += (char)(decryptedArr[1] + 'A');
    }

    return decryptedText;
}

int main() {
    vector<vector<int>> keyMatrix(2, vector<int>(2));
    cout << "Enter the 2x2 key matrix (row by row):" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> keyMatrix[i][j];
        }
    }

    cout << "Enter the plaintext (uppercase, even length): ";
    string plaintext;
    cin >> plaintext;

    if (plaintext.length() % 2 != 0) {
        cout << "Plaintext must have an even number of characters!" << endl;
        return 0;
    }

    string ciphertext = encrypt(plaintext, keyMatrix);
    cout << "Encrypted ciphertext: " << ciphertext << endl;

    string decryptedText = decrypt(ciphertext, keyMatrix);
    cout << "Decrypted plaintext: " << decryptedText << endl;

    return 0;
}
