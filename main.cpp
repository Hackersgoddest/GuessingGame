/* A Guessing Game */
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

// Declaring function prototypes

// Function to display a welcoming message to the user
void WelcomeMessage(); 
// Function to display a list of instruction the user will like to perform
int Menu();  
// Function to check whether a certain data entered by the user is an integer or not 
void isNumDigit(string&);
// Funtion that contains all the logic behind this game.
void PlayGame();
// Function that terminates the game.
void ExitGame();
// Function that allow the user to select the number of people who wants to play the game.
int setNumOfPlayers();
// Function that checks whether a certain data entered by the user is an alphabets or not
void isAlphabet(string&);
// Functions that takes the names of the players.
void setPlayersNames(const int);
// Function that allow the user(s) to choose range, that's default range or manually set range .
int setRange();
// Function that allow the user to manually set the range
void ManualRange();
// Function that automatically set the range for the user(s), that is between 1 and 100
void DefaultRange();
// Function that takes in the number of players guesses
void setPlayersGuesses();
// Function that set the random number from the range choosed by the user(s).
int setNumber();
// Function that tracks the number of guesses the player(s)/user(s) has made.
int setNumOfGuesses();
// Function that checks whether the guesses make by the player(s) is/are  true or not
void checkGuesses(const int, const int);
// Function that ask the users(s) whether they want to continue playing.
bool PlayAgain();

// Declaring global variable

// A variable to store the name(s) of the player(s)
vector<string> PlayersNames; 
// A variable to store each player guesses
vector<int> PlayersGuesses;
// A variable to store range
int minRange, maxRange;
// A variable to check whether player(s) guesses was correct or not
bool guessCorrect;

int main()
{
    WelcomeMessage();
    int choice;
    do
    {
        choice = Menu();
        if(choice == 1)
          PlayGame();
    }while(choice != 2);
    ExitGame(); 
    return 0;
}

void WelcomeMessage()
{
    cout<<"          ***********************************"<<endl
        <<"          *   WELCOME TO MY GUESSING GAME   *"<<endl  
        <<"          ***********************************"<<endl
        <<"          Press any key to continue...";
    cin.get();
}

int Menu()
{
    system("cls");
    int choice;
    string option;
    cout<<"          **********MENU**********"<<endl
        <<"          *      1.Play Game     *"<<endl
        <<"          *      2.Exit Game     *"<<endl
        <<"          ************************"<<endl;
    do
    {
        cout<<"          Enter your choice... ";
        getline(cin>>ws, option);
        if(option != "1" && option != "2")
            cout<<"          Invalid choice\n";
    } while (option != "1" && option != "2"); // this condition ensures that the user has entered 1 or 2.
    choice = stoi(option);
    return choice;
}

void isNumDigit(string &option)
{
  bool isInt = 0;
  while (!isInt)
  {
    isInt = 1;
    for (int i = 0; i < option.length(); i++)
    {
      if (!isdigit(option[i]) && option[i] != '+' && option[i] != '-') // if score[i] is a number, this condition will evaluate to false else it will evaluate to true.
      {
        isInt = 0;
        break;
      }
    }
    if(option == "+" || option == "-")
       isInt = 0;
    if (!isInt)
    {
        system("cls");
        cout << "          You have entered invalid number\n";
        cout << "          Enter number again...";
        getline(cin >>ws, option);
    }
  }
}

void PlayGame()
{
    system("cls");
    // A variable to hold the number of players who are going to play the game
    int NumOfPlayers = 0; 
    NumOfPlayers = setNumOfPlayers(); // assign the number the setNumOfPlayers function is going to return
    setPlayersNames(NumOfPlayers);
    do
    {
        srand(time(NULL));
        int randomNumber, numOfGuesses = 0;
        const int range = setRange();
        if(range == 1)
          DefaultRange();
        else
          ManualRange();
        randomNumber = setNumber();
        numOfGuesses = setNumOfGuesses();
        do{
            system("cls");
            cout<<"         You have "<<numOfGuesses<<" attempt(s) remaining "<<endl;
            setPlayersGuesses();
            checkGuesses(randomNumber, NumOfPlayers);
            --numOfGuesses;
        }while (numOfGuesses > 0 && !guessCorrect); // ensures that the user(s) is/are not allow to guess anymore if reaches the number of guesses limit and their guess is still not correct
        if(!guessCorrect)
        {
            system("cls");
            cout<<"          The number was "<<randomNumber<<endl; // the random number is display if user(s) is/are unable to guess correctly
        }
        numOfGuesses = 0; // numOfGuesses is set to zero to allow the user(s) to set number of guesses again when the user(s) wants to play again.
    } while (PlayAgain());
    PlayersNames.clear(); // clear user(s) names when the user(S) exit game play mode and go back to the home menu
}

int setNumOfPlayers()
{
    system("cls");
    string players;
    int NumOfPlayers;
    do
    {
        cout<<"          Enter the number of players... ";
        getline(cin>>ws, players);
        isNumDigit(players);
        NumOfPlayers = stoi(players);
        if(NumOfPlayers < 1)
        {
          cout<<"        Number of players can't be less than 1";
          system("cls");
        }
    } while (NumOfPlayers < 1);
    return NumOfPlayers;
}

void setPlayersNames(const int NumOfPlayers)
{
    system("cls");
    string names;
    for(int i = 0; i < NumOfPlayers; i++)
    {
        if(NumOfPlayers == 1) {
            cout<<"          Enter your name... ";
        }
        else {
        cout<<"          Enter Player "<<(i + 1)<<" name... ";
        }
        getline(cin>>ws, names);
        isAlphabet(names);
        PlayersNames.push_back(names);
    }
}

void isAlphabet(string &names)
{
    bool isAlpha = 0;
    while (!isAlpha)
    {
        isAlpha = 1;
        for (int y = 0; y < names.length(); y++)
        {
            if (!(isalpha(names[y]) || names[y] == ' '))
            {
                isAlpha = 0;
                break;
            }
        }
        if (!isAlpha)
        {
            system("cls");
            cout << "          Invalid name\n          Enter name again... ";
            getline(cin>>ws, names);
        }
    }
}

int setRange()
{
    system("cls");
    int choice;
    string option;
    cout<<"          1.Default Range(i.e from 1 to 100)\n          2.Manually Set Range\n";
    do
    {
        cout<<"          Enter choice... ";
        getline(cin>>ws, option);
        isNumDigit(option);
        choice = stoi(option);
        if(choice != 1 && choice != 2)
           cout<<"          Invalid Option\n";
    } while (choice != 1 && choice != 2);
    return choice;
}

void ManualRange()
{
    string minNum, maxNum;
    system("cls");
    do
    {
        cout << "          Enter the minimum range...";
        getline(cin>>ws, minNum);
        isNumDigit(minNum);
        minRange = stoi(minNum);
        if(minRange < 0)
           cout<<"          minimum range can't be less than 0\n";
    } while (minRange < 0);
    
    system("cls");
    do
    {
        cout << "          Enter the maximum range...";
        getline(cin>>ws, maxNum);
        isNumDigit(maxNum);
        maxRange = stoi(maxNum);
        if(maxRange <= minRange )
            cout<<"          maximum range can't be less than or equal to minumum range\n";
    } while (maxRange <= minRange);
}

int setNumOfGuesses()
{
    int guess;
    string number;
    do
    {
        system("cls");
        cout<<"         Enter the number of guesses you want to make....";
        getline(cin>>ws, number);
        isNumDigit(number);
        guess = stoi(number);
        if(guess < 1)
         cout<<"         number of guess cannot be less than 1\n";
    } while (guess < 1);
    return guess;
}

void DefaultRange()
{
    minRange = 1;
    maxRange = 100;
}

void setPlayersGuesses()
{
    string guess;
    int playerGuess;
    for(string Playername : PlayersNames)
    {
        do
        {
            cout<<"          "<<Playername<<" enter your guess... ";
            getline(cin>>ws, guess);
            isNumDigit(guess);
            playerGuess = stoi(guess);
            if(playerGuess < minRange)
              cout<<"          Guess can't be less than minimum range\n";
            if(playerGuess > maxRange)
              cout<<"          Guess can't be greater than maximum range\n";
        } while (playerGuess < minRange || playerGuess > maxRange); // ensures that the user(s) guess is within range.
        PlayersGuesses.push_back(playerGuess);
    }
}

int setNumber()
{
    // A variable to hold the random number
    int random;
    random = minRange + rand() % ((maxRange - minRange) + 1); // formula used to set the random number base on the range set by the user(s).
    return random;
}

void checkGuesses(const int random, const int players)
{
    guessCorrect = false;
    // this loop helps checks each player guess to see if is correct or not.
    for(int i = 0; i < players; i++ )
    {
        if(PlayersGuesses[i] == random)
        {
            cout<<"          Congratulation "<<PlayersNames[i]<<" your guess is correct"<<endl; // message to be displayed when the user guess is correct
            guessCorrect = true;
        }
        else
            cout<<"          Sorry "<<PlayersNames[i]<<" your guess is wrong"<<endl; // message to be displayed when the user guess is wrong
    }
    if(guessCorrect)
      cout<<"          The number is "<<random<<endl;
    PlayersGuesses.clear();
    cout<<"          Press any key to continue...";
    cin.get();
}

bool PlayAgain()
{
    char choice;
    cout<<"         Press \'y\' to continue or any key to exit to main menu.... ";
    cin.get(choice);
    if(choice == 'y' || choice == 'Y')
      return true;
    else 
      return false;
}

void ExitGame()
{
    system("cls");
    cout<<"          *********************************"<<endl
        <<"          *  THANKS FOR PLAYING THE GAME  *"<<endl
        <<"          *********************************"<<endl;
    exit(0);

}