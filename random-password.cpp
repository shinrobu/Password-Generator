// Group Members: Jordan Xu, Brad Bolluyt, Hemil Bhasavar, Rob Ranit

#include <iostream> // Just Necessary
#include <ctime>  // Associated with random generation
#include <cmath> // Math reasons
#include <cstring> // Working with c-strings
#include <time.h> // Random number generation
#include <vector> // This is for the shuffling step at the end
#include <algorithm> //This is for the random_shuffle function at the end
using namespace std; //Just necessary
void PasswordTest(char pswd[], double& strength); //Tests the strength of generated passwords
void printLowLetters(int, char[]); //Generates lowercase letters for use in password
void printUpLetters(int, int, char[]); //Generates uppercase letters for use in password
void printNumbers(int, int, int, char[]); //Generates numbers for use in password
void printSymbols(int, int, int, int, char[]); //Generates symbols for use in password
void passwordAssortment(char[]); //Scrambles the generated characters of each type in the password string

int main()
{
    cout << "Welcome to our password generator!" << endl;
    char repeat = 'Y';
    while (repeat == 'y' || repeat == 'Y')
    {
        int LowNum, UpNum, NumNum, SymNum;
        char password[50];
        cout << "Enter the amount (an integer) of the following password parts: " << endl;
        cout << "Lowercase letters: ";
        cin >> LowNum;
        cout << "Uppercase letters: ";
        cin >> UpNum;
        cout << "Numbers: ";
        cin >> NumNum;
        cout << "Symbols: : ";
        cin >> SymNum;
        printLowLetters(LowNum, password);
        printUpLetters(UpNum, LowNum, password);
        printNumbers(NumNum, UpNum, LowNum, password);
        printSymbols(SymNum, NumNum, UpNum, LowNum, password);
        passwordAssortment(password);
        double strength = 0.0;
        PasswordTest(password, strength);
        cout << endl;
        cout << "Would you like a new password? Enter Y/N: ";
        cin >> repeat;
        cout << endl;
        cout << endl;
    }
    return 0;
}

void printLowLetters(int LowNum, char password[])
{
    char characters[] = "qwertyuiopasdfghjklzxcvbnm";
    int length, rNum;
    srand(time(NULL));
    for (int i = 1; i <= LowNum; i++)
    {
        rNum = rand() % (25 + 1);
        password[i - 1] = characters[rNum];
    }
}

void printUpLetters(int UpNum, int LowNum, char password[])
{
    char characters[] = "MNBQWEPOIASDLKJZXCVFHGRUTY";
    int length, rNum;
    srand(time(NULL));
    for (int i = 1; i <= UpNum; i++)
    {
        rNum = rand() % (25 + 1);
        password[(i - 1) + LowNum] = characters[rNum];
    }
}

void printNumbers(int NumNum, int UpNum, int LowNum, char password[])
{
    char characters[] = "0123456789";
    int length, rNum;
    srand(time(NULL));
    for (int i = 1; i <= NumNum; i++)
    {
        rNum = rand() % (10);
        password[(i - 1) + LowNum +UpNum] = characters[rNum];
    }
}

void printSymbols(int SymNum, int NumNum, int UpNum, int LowNum, char password[])
{
    char characters[] = "!@#$%^&*()_+-=;':,.<>/?~'"; //25 characters
    int length, rNum;
    srand(time(NULL));
    for (int i = 1; i <= SymNum; i++)
    {
        rNum = rand() % (25);
        password[(i - 1) + LowNum + UpNum + NumNum] = characters[rNum];
    }
    password[SymNum + LowNum + UpNum + NumNum] = '\0';
}

void passwordAssortment(char genPassword[])
{
    int length = strlen(genPassword);
    vector<char> randSortedPass(length);
    for (int m = 0; m < length; m++) //loop for assigning the current generated password to the password that will be sorted
        randSortedPass[m] = genPassword[m];
    random_shuffle(randSortedPass.begin(), randSortedPass.end()); //randomly shuffles the characters fo the password
    cout << "Assorted password is: ";
    for (int m = 0; m < length; m++) //outputs newly sorted password
        cout << randSortedPass[m];
    cout << endl;
}

//Checks the strength of the password
void PasswordTest(char password[], double& strength)
{
    int uppercase = 0;
    int lowercase = 0;
    int symbols = 0;
    int numbers = 0;
    int check;
    int length = strlen(password);
    for (int i = 0; i < length; i++)
    {
        check = static_cast<int>(password[i]);
        if ((check >= 65) && (check <= 90))
            uppercase++;
        if ((check >= 97) && (check <= 122))
            lowercase++;
        if ((check >= 48) && (check <= 57))
            numbers++;
        if (((check >= 33) && (check <= 47)) || ((check >= 58) && (check <= 64)) || ((check >= 91) && (check <= 96)) || ((check >= 123) && (check <= 126)))
            symbols++;
    }
    strength = (lowercase / 5.0) + (uppercase / 2.0) + (numbers / 2.0) + symbols;

    if (strength < 2)
        cout << "Your password is very weak." << endl;
    else if ((strength >= 2) && (strength < 4))
        cout << "Your password is weak." << endl;
    else if ((strength >= 4) && (strength < 6))
        cout << "Your password is decent." << endl;
    else if ((strength >= 6) && (strength < 8))
        cout << "Your password is strong." << endl;
    else if (strength >= 9)
        cout << "Your password is very strong." << endl;
}
