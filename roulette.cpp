#include <iostream>
#include <stdlib.h>
#include <string>
#include <regex>
using namespace std;

//Function declarations
int generateRandom();
int stringToInt(string st);
bool isNumber(string input);
bool inputChoice();
void printArt();
void printError(string error);
void clearScreen();
void clearCin();
string returnColor(int number);

//Global variables
const int money = 1000;

int main()
{
  //Initiate random seed value with srand and set initial variables.
  srand(time(NULL));
  int moneyLeft = money;
  bool gameOver = false;

  /*
  The following condition loop is used for the ability to restart the game when
  the player have no money left or you choose to not place a bet.
  If gameOver variable is set to true, the program will shut down by
  exiting this loop and return 0.
  This is the only exit point in the program.
  */
  while(gameOver == false)
  {
    clearScreen();
    cout << "Welcome to roulette, you start with " << money << "kr." << endl << endl;

    /*
    The following condition loop governs when the player can keep playing by
    checking if there exists money left to bet and is also used to end the
    game by setting both gameOver to true and moneyLeft to 0.
    */
    while (moneyLeft >= 100)
    {

      /*
      Resets values for each iteration of the loop.
      */
      int bet;
      int number;
      bool validBet = false;
      bool validNumOrColor = false;
      string numberOrColor;
      string color;

      /*
      The following loop repeats until a valid bet has been entered and
      prints a appropriate error message when a non-number input has
      been detected.
      */
      while(validBet == false)
      {
        cout << "Choose how much you want to bet." << endl;

        /*
        The following statement prints different messages depending on how
        much money the player have left so that the player does not
        have to keep track of current balance.
        */
        if (moneyLeft >= 500) {
          cout << "Choose which bet you want to make: [100] or [300] or [500]" << endl << "> ";
        }
        else if (moneyLeft >= 300){
          cout << "Choose which bet you want to make: [100] or [300]" << endl << "> ";
        }
        else {
          cout << "The bet you can make is: [100]" << endl << "> ";
        }

        cin >> bet;
        clearCin();
        clearScreen();

        /*
        The following section checks if one of the valid bets have been
        registered, prints a message to the player and sets the variable
        validBet=true so that we break out of the loop the next time we evalutate it.
        Otherwise, print a fault message from either placing a bet that is
        larger then the money the player have left or from entering a wrong input.
        */
        if ((bet == 100) || (bet == 300) || (bet == 500)){
            if (bet <= moneyLeft) {
                cout << endl << bet << "kr bet has been registered." << endl;
                validBet = true;
            }
            else{
                cout << endl << "You do not have enough money to place this bet." << endl;
                cout << "The bet you placed was " << bet << "kr and you have " << moneyLeft << "kr left." << endl << endl;
            }
        }
        else
        {
            printError("ERROR, only these values are allowed: [100] or [300] or [500]");
        }
      }

      /*
      This following loop repeats until a valid color or number has been
      entered and prints a appropriate error message when something else
      then a color or a number has been detected.
      */
      while(validNumOrColor == false)
      {
        cout << endl << "Which number or color do you want to place a bet on:" << endl;
        cout << "Valid numbers are: [1-36]" << endl;
        cout << "Valid colors are: [red] or [black]" << endl << "> ";
        cin >> numberOrColor;
        clearCin();
        clearScreen();

        /*
        The following statement checks if the input is either a number or
        a color by using the helper function isNumber and comparing the string
        against the strings "black" or "red".
        When a valid input has been detected, set the variable validNumOrColor
        to true so that we break out of the loop the next time it is evalutated.
        Otherwise, print a error message telling the player that the input
        is not a valid number or color.
        */
        if (isNumber(numberOrColor))
        {
          number = stringToInt(numberOrColor);
          color = returnColor(number);
          if ((1 <= number) && (number <= 36))
          {
            validNumOrColor = true;
          }
          else
          {
            printError("ERROR, Only numbers [0-36] are allowed");
          }
        }
        else if (numberOrColor == "black" || numberOrColor == "red")
        {
          color = numberOrColor;
          validNumOrColor = true;
        }
        else
        {
          printError("ERROR, wrong input. Valid options are: [ 1-36 ] and [ red | black ]");
        }
      }

      /*
      The following code generates both a winning number by using the
      function generateRandom and a color by using the returnColor function.
      Print a message with the result containing both the winning number and
      the color associated to it.
      */
      cout << endl << "Spinning wheel..." << endl;
      int randomNumber = generateRandom();
      string randomColor = returnColor(randomNumber);
      cout << endl << "Result was:" << endl;
      cout << "Number: " << randomNumber << endl;
      cout << "Color: " << randomColor << endl;

      /*
      The following statements checks if the number and/or color you input match the
      randomly generated number. If true, increase money print congratulatory message.
      Otherwise, decrease money and print appropriate message.
      The two main cases prints different messages if you bet either on a number or a color.
      */
      if(isNumber(numberOrColor))
      {
        if(number == randomNumber)
        {
          cout << endl << "WINNER!, your number was " << number << ", your color was " << color << "." << endl;
          cout << "You win 10 times your bet, " << (bet*10) << "kr will be added to your account." << endl << endl;
          moneyLeft = moneyLeft + (bet*10);
        }
        else
        {
          cout << endl << "Sorry, you lost the bet. Your number was " << number << ", your color was " << color << "." << endl;
          cout << bet << "kr will be charged from your account." << endl << endl;
          moneyLeft = moneyLeft - bet;
        }
      }
      else
      {
        if(color == randomColor)
        {
          cout << endl << "WINNER!, your color was " << color << "." << endl;
          cout << "You win 2 times your bet, " << (bet*2) << "kr will be added to your account." << endl << endl;
          moneyLeft = moneyLeft + (bet*2);
        }
        else
        {
          cout << endl << "Sorry, you lost the bet. Your color was " << color << "." << endl;
          cout << bet << "kr will be charged from your account." << endl << endl;
          moneyLeft = moneyLeft - bet;
        }
      }

      /*
      The following section checks if we have money left. If true, ask the
      player if another bet should be placed.
      Without this condition, the player gets asked if another bet should
      be placed even though there is no money left.
      */
      if (moneyLeft > 0) {
        cout << "Place another bet? Enter [y] or [n]" << endl;
        bool betAgain;
        betAgain = inputChoice();
        if(betAgain == false){
          moneyLeft = 0;
          gameOver = true;
        }
        else {
            cout << "You have " << moneyLeft << "kr on your account." << endl << endl;
        }
      }
    }

    /*
    The following section asks the player if the game should be restarted and
    then sets the variables moneyLeft and gameOver depending on the answer.
    When the player choose not to place another bet or the money is at 0, the
    player will have to make this choice.
    */
    cout << "Game Over, play again? Enter [y] or [n]" << endl;
    bool playAgain = inputChoice();
    if (playAgain){
        cout << endl << "Restarting game..." << endl << endl;
        moneyLeft = money;
        gameOver = false;
    }
    else {
        cout << endl << "Thank you for playing!" << endl << endl;
        gameOver = true;
    }
  }
  cin.get();
  return 0;
}

/*
This following function is used "clear" cin so that input is not
skipped the next time in a loop, otherwise an infinite loop occurs.
Resets error flags and ignores 5000 extracted characters from the stream.
Stops extracting at the newline character.
*/
void clearCin()
{
    cin.clear();
    cin.ignore(5000, '\n');
}

/*
The printError function is only used for making the code a bit more clean,
since the error messages uses a lot of end lines.
*/
void printError(string error){
    cout << endl << endl << error << endl << endl;
}

/*
This function generates a random number between 1-37 and then returns that number.
*/
int generateRandom()
{
  int numberRan = rand() % 36 + 1;
  return numberRan;
}

/*
The following function converts a string to an int.
No error checking is done here since we use the isNumber function to check if
it really is number beforehand.
Uses stdlib.h library for the atoi function.
*/
int stringToInt(string st)
{
  int result = atoi(st.c_str());
  return result;
}

/*
Returns a color as a string depending on the input number being a even
number or not.
This is done by checking ((input number) modulo 2) as a true or false value.
*/
string returnColor(int num){
  string result = "black";
  if (num % 2)
  {
    result = "red";
  }
  return result;
}

/*
The isNumber function checks if a string is a valid number.
This is done by using regex_match from the newer C++11 libraries which can
match certain patterns in a string.
Uses the regex library and might require some extra command line options on
certain systems to compile.
*/
bool isNumber(string input){
  bool result = false;
  regex num("[[:digit:]]+");
  if(regex_match(input,num))
  {
    result = true;
  }
  return result;
}

/*
This function simply prints some nice ASCII art.
*/
void printArt(){
  cout << " ______   _______ __   __ ___     _______ _______ _______ _______ " << endl;
  cout << "|    _ | |       |  | |  |   |   |       |       |       |       |" << endl;
  cout << "|   | || |   _   |  | |  |   |   |    ___|_     _|_     _|    ___|" << endl;
  cout << "|   |_||_|  | |  |  |_|  |   |   |   |___  |   |   |   | |   |___ " << endl;
  cout << "|    __  |  |_|  |       |   |___|    ___| |   |   |   | |    ___|" << endl;
  cout << "|   |  | |       |       |       |   |___  |   |   |   | |   |___ " << endl;
  cout << "|___|  |_|_______|_______|_______|_______| |___|   |___| |_______|" << endl << endl;
}


/*
The clearScreen function clears the screen by printing 50 newlines characters.
This way of clearing the screen is not optimal but works on both windows and
linux systems.
*/
void clearScreen(){
  cout << string( 150, '\n' );
  printArt();
}

/*
The player has to make two yes or no choices during the game, this
function makes the code look more clean.
Since the way of input is the same, there is no need to write it twice.
*/
bool inputChoice(){
  bool choice = false;
  bool validChoice = false;
  while(validChoice == false)
  {
    string inputChoice;
    cout << "> ";
    cin >> inputChoice;
    clearCin();
    if (inputChoice == "y"){
        choice = true;
        validChoice = true;
    }
    else if(inputChoice == "n"){
        validChoice = true;
    }
    else{
      cout << endl << "ERROR, invalid output." << endl;
    }
  }
  clearScreen();
  return choice;
}
