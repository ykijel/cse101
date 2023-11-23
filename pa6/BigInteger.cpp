//-----------------------------------------------------------------------------
//  Yahli Kijel
//  ykijel
//  2023 Fall CSE101 PA6
//  BigInteger.cpp 
//  BigInteger ADT implementation and functions
//-----------------------------------------------------------------------------
#include "BigInteger.h"
#include <stdexcept>
#include<iostream>
#include<string>
#include <cstdio>
#include <vector>

const int POWER = 9;
const ListElement base = 1000000000;

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setAfter(-L.peekNext());
        L.moveNext();
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn) {
    S.clear();
    ListElement sum;
    int carry = 0;

    A.moveBack();
    B.moveBack();

    while (A.position() > 0 || B.position() > 0 || carry > 0) {
        ListElement digitA = (A.position() > 0) ? A.movePrev() : 0;
        ListElement digitB = (B.position() > 0) ? B.movePrev() : 0;
        sum = digitA + sgn * digitB + carry;
        carry = sum / base;
        S.insertBefore(sum % base);
    }
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub(), and mult().
int normalizeList(List& L) {
    L.moveFront();
    int sign = 1;

    if (L.front() < 0) {
        sign = -1;
        L.setBefore(-L.front());
    }

    return sign;
}


// Helper function to shift a List to the left
void shiftList(List& L, int p) {
    while (p > 0) {
        L.insertAfter(0);
        p--;
    }
}

// Helper function to multiply a List by a scalar
void scalarMultList(List L, ListElement m) {
    L.moveBack();
    int carry = 0;
    while (L.position() >= 0 || carry > 0) {
        ListElement digit = (L.position() >= 0) ? L.movePrev() : 0;
        ListElement product = digit * m + carry;
        carry = product / base;
        L.setAfter(product % base);
    }
}

// Helper function to multiply two Lists
List multLists(List list1, List list2) {
    List result;
    list2.moveBack();
    int zeros = 0;
    while (list2.position() >= 0) {
        ListElement digit2 = list2.movePrev();
        List temp = list1;
        scalarMultList(temp, digit2);
        shiftList(temp, zeros);
        sumList(result, result, temp, 1);
        zeros++;
    }
    return result;
}

// Constructor that creates a new BigInteger in the zero state
BigInteger::BigInteger() : signum(0), digits() {}

// Constructor that creates a new BigInteger from the long value x
BigInteger::BigInteger(long x) : signum((x > 0) - (x < 0)), digits() {;
    x = std::abs(x);
    while (x > 0) {
        digits.insertBefore(x % base);
        x /= base;
    }
}

// Constructor that creates a new BigInteger from the string s
BigInteger::BigInteger(std::string s) : signum(0), digits() {
    if (s.empty()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }

    size_t start = 0;
    if (s[0] == '-' || s[0] == '+') {
        signum = (s[0] == '-') ? -1 : 1;
        start = 1;
    }

    int templength = s.length();
    int i = 0;

    // Remove negative sign if the number is negative
    if (signum == -1) {
        s.erase(0, 1);
    }

    // Handle the case where the length is not a multiple of power
    if (templength % POWER != 0) {
        std::string temp;
        for (; i < templength % POWER; i++) {
            temp += s[i];
        }

        digits.insertBefore(std::stoi(temp));  // Insert from the front
    }

    while (i < templength) {
        std::string temp;
        for (int j = 0; j < POWER && i < templength; j++, i++) {
            temp += s[i];
        }

        try {
            int test = std::stoi(temp);
            digits.insertBefore(test);  // Insert from the front
        } catch (const std::invalid_argument& e) {
            // Handle the exception, for example, print an error message
            std::cerr << "Error converting string to integer: " << e.what() << std::endl;
        }
    }

    // Remove leading zeros
    while (digits.length() > 1 && digits.front() == 0) {
        digits.moveFront();
        digits.eraseAfter();
    }

    // Set signum to -1 if the number is negative and the magnitude is not zero
    if (signum == 0 && digits.length() > 1) {
        signum = 1;
    }
}

/*    
    for (size_t i = start; i < s.length(); i++) {
        int digitValue;

        if (isdigit(s[i])) {
            digitValue = s[i] - '0';
        } else if (isalpha(s[i])) {
            digitValue = tolower(s[i]) - 'a' + 10;
        } else {
            throw std::invalid_argument("BigInteger: Constructor: invalid character");
        }

        if (digitValue < 0 || digitValue >= base) {
            throw std::invalid_argument("BigInteger: Constructor: invalid digit for the specified base");
        }
        
        digits.insertBefore(digitValue);
    }
*/

// Copy constructor
BigInteger::BigInteger(const BigInteger& N) : signum(N.signum), digits(N.digits) {}

// Access function to get the sign of the BigInteger
int BigInteger::sign() const {
    return signum;
}

// Access function to compare two BigIntegers
int BigInteger::compare(const BigInteger& N) const {
    if (signum < N.signum) {
        return -1;
    } else if (signum > N.signum) {
        return 1;
    } else {
        List tempDigits = digits;
        List tempNDigits = N.digits;

        // Remove leading zeros
        while (tempDigits.length() > 1 && tempDigits.front() == 0) {
            tempDigits.moveFront();
            tempDigits.eraseAfter();
        }
        while (tempNDigits.length() > 1 && tempNDigits.front() == 0) {
            tempNDigits.moveFront();
            tempNDigits.eraseAfter();
        }

        // If one number has more digits than the other, consider the longer number greater
        if (tempDigits.length() < tempNDigits.length()) {
            return -signum;
        } else if (tempDigits.length() > tempNDigits.length()) {
            return signum;
        }

        // Compare each digit individually
        tempDigits.moveFront();
        tempNDigits.moveFront();
        while (tempDigits.position() > 0 && tempNDigits.position() > 0) {
            ListElement digitA = tempDigits.moveNext();
            ListElement digitB = tempNDigits.moveNext();

            if (digitA < digitB) {
                return -signum;
            } else if (digitA > digitB) {
                return signum;
            }
        }

        return 0;  // Magnitudes are equal
    }
}

// BigInteger arithmetic operations

BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger result;
    List A = digits;
    List B = N.digits;
    List& S = result.digits;

    int carry = 0;

    A.moveBack();
    B.moveBack();

    while (A.position() > 0 || B.position() > 0 || carry > 0) {
        ListElement digitA = (A.position() > 0) ? A.movePrev() : 0;
        ListElement digitB = (B.position() > 0) ? B.movePrev() : 0;

        // Adjust the signs for negative numbers
        if (signum == -1) {
            digitA = -digitA;
        }
        if (N.signum == -1) {
            digitB = -digitB;
        }

        ListElement sum = digitA + digitB + carry;

        // Update carry for the next iteration
        carry = sum / base;

        // Ensure sum is positive (handle cases where digitA + digitB + carry exceeds base)
        sum = (sum + base) % base;

        S.insertAfter(sum);
    }

    // Determine the sign based on the absolute values
    if (signum == -1 && N.signum == -1) {
        result.signum = -1; // Both numbers are negative
    } else if (signum == 1 && N.signum == 1) {
        result.signum = 1; // Both numbers are positive
    } else {
        // One positive and one negative
        // Compare absolute values manually
        if (digits.length() > N.digits.length()) {
            result.signum = (signum == -1) ? -1 : 1; // Absolute value of A is greater
        } else if (digits.length() < N.digits.length()) {
            result.signum = (N.signum == -1) ? -1 : 1; // Absolute value of B is greater
        } else {
            // Compare digit by digit
            A.moveFront();
            B.moveFront();
            while (A.position() < A.length()) {
                ListElement digitA = A.moveNext();
                ListElement digitB = B.moveNext();
                if (digitA > digitB) {
                    result.signum = (signum == -1) ? -1 : 1;
                    break;
                } else if (digitA < digitB) {
                    result.signum = (N.signum == -1) ? -1 : 1;
                    break;
                }
            }
            // If the loop completes without breaking, absolute values are equal
            if (result.signum == 0) {
                result.signum = 0;
            }
        }
    }

    // Remove leading zeros
    while (S.length() > 1 && S.front() == 0) {
        S.moveFront();
        S.eraseAfter();
    }

    return result;
}


BigInteger BigInteger::sub(const BigInteger& N) const {
    if (((signum == 1 && N.signum == -1) || (signum == -1 && N.signum == 1))) {
        BigInteger result;
        List A = digits;
        List B = N.digits;
        List& S = result.digits;

        int carry = 0;

        A.moveBack();
        B.moveBack();

        while (A.position() > 0 || B.position() > 0 || carry > 0) {
            ListElement digitA = (A.position() > 0) ? A.movePrev() : 0;
            ListElement digitB = (B.position() > 0) ? B.movePrev() : 0;
            ListElement sum = digitA + digitB + carry;
            carry = sum / base;
            sum %= base;
            S.insertAfter(sum);
        }

        result.signum = signum;

        // Remove leading zeros
        while (S.length() > 1 && S.front() == 0) {
            S.moveFront();
            S.eraseAfter();
        }
        return result;
    }

    BigInteger result;
    List A = digits;
    List B = N.digits;
    List& S = result.digits;

    int borrow = 0;

    A.moveBack();
    B.moveBack();

    while (A.position() > 0 || B.position() > 0 || borrow > 0) {
        ListElement digitA = (A.position() > 0) ? A.movePrev() : 0;
        ListElement digitB = (B.position() > 0) ? B.movePrev() : 0;

        // Adjust the subtraction and borrow calculation
        ListElement diff = digitA - digitB - borrow + base;
        borrow = (digitA - borrow < digitB) ? 1 : 0;  // Adjust the borrow condition
        diff %= base;

        S.insertAfter(diff);
    }

    result.signum = (S.front() != 0) ? signum : 0;  // Set signum to 0 if the result is zero

    // Remove leading zeros
    while (S.length() > 1 && S.front() == 0) {
        S.moveFront();
        S.eraseAfter();
    }
    return result;
}


BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger result;

    List A = digits;
    List B = N.digits;

    // Check if either operand is zero
    if ((A.length() == 1 && A.front() == 0) || (B.length() == 1 && B.front() == 0)) {
        return result;  // The product is zero
    }

    // Determine the sign of the result
    result.signum = (signum == N.signum) ? 1 : -1;

    // Calculate the size of the result array
    int size = A.length() + B.length();

    // Initialize the matrix to zero using a dynamically allocated array
    ListElement** multMatrix = new ListElement*[size];
    for (int i = 0; i < size; ++i) {
        multMatrix[i] = new ListElement[size]();
    }

    // Perform multiplication
    A.moveBack();

    for (int i = 0; i < A.length(); i++) {
        int carry = 0;
        ListElement digitA = (A.position() > 0) ? A.movePrev() : 0;
        
        B.moveBack();

        for (int j = 0; j < B.length(); j++) { //digA needs to only move back once every time this loops
            
            ListElement digitB = (B.position() > 0) ? B.movePrev() : 0;
            ListElement product = digitA * digitB + carry + multMatrix[i][i + j];
            carry = product / base;
            
            multMatrix[i][i + j] = product % base;
        }

        multMatrix[i][i + B.length()] = carry;
        
    }

    // Sum the columns of the matrix to get the final result
ListElement carry = 0;
for (int i = 0; i < size; i++) {
	
    ListElement columnSum = 0;

    for (int j = 0; j < size; ++j) {
        columnSum += multMatrix[j][i];       
    }

    columnSum += carry;

    // Insert each digit separately with leading zeros
    while (columnSum > 0) {
        ListElement insert = (columnSum % base);
        columnSum /= base;
        if(columnSum > 0)
        {
        	carry = columnSum;
        }
        //insert += columnSum;
        if(carry != insert)
        {
        result.digits.insertAfter(insert);
        }
        
    }
//the problem is, we are taking the excess digit(s) and instead of adding it to the next number (like a carry) mathematically, we are just shoving it into the list.
}
return result;
}

// Other functions

std::string BigInteger::to_string() {
    if (signum == 0) {
        return "0";
    }

    std::string result = (signum == -1) ? "-" : "";
    digits.moveFront();

    // Skip leading zeros
    while (digits.front() == 0 && digits.length() > 1) {
        digits.eraseAfter();
    }

    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        std::string digitStr = std::to_string(digits.peekNext());
        std::string paddingZeros = "";

        // Append trailing zeros based on the power
        for (; paddingZeros.length() + digitStr.length() < POWER && digits.position() > 0; paddingZeros += '0') {}

        result += paddingZeros + digitStr;
    }

    return result;
}





// Overridden operators

std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    stream << N.to_string();
    return stream;
}

bool operator==(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 0;
}

bool operator<(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) < 0;
}

bool operator<=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) <= 0;
}

bool operator>(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) > 0;
}

bool operator>=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) >= 0;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B) {
    return A.add(B);
}

BigInteger operator+=(BigInteger& A, const BigInteger& B) {
    A = A.add(B);
    return A;
}

BigInteger operator-(const BigInteger& A, const BigInteger& B) {
    return A.sub(B);
}

BigInteger operator-=(BigInteger& A, const BigInteger& B) {
    A = A.sub(B);
    return A;
}

BigInteger operator*(const BigInteger& A, const BigInteger& B) {
    return A.mult(B);
}

BigInteger operator*=(BigInteger& A, const BigInteger& B) {
    A = A.mult(B);
    return A;
}

