#include <iostream>
#include <cstdlib>

using namespace std;

enum enGameChoice {Rock = 1, Paper = 2, Scissor = 3};
enum enWinner {Player = 1, Computer = 2, Draw = 3};

struct stRoundInfo {

	short NumberRound = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner RoundWinner;

};

struct stFinalResultInfo {

	short NumberOfRounds = 0;
	short PlayerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner FinalWinner;

};

short ReadNumberOfRounds() {

	short NumberOfRounds = 1;

	do
	{
		cout << "How many rounds you want ? 1 to 10" << endl;
		cin >> NumberOfRounds;
	} while (NumberOfRounds < 1 || NumberOfRounds > 10);

	return NumberOfRounds;

}

enGameChoice ReadPlayerChoice() {

	int PlayerChoice = 0;

	do
	{

		cout << "\nYour Choice: [1]:Rock, [2]:Paper, [3]:Scissor : ";
		cin >> PlayerChoice;

	} while (PlayerChoice < 1 || PlayerChoice > 3);

	return (enGameChoice) PlayerChoice;

}

short GetRandomNumber(short From, short To) {

	short RandomNumber = rand() % (To - From + 1) + From;

	return RandomNumber;

}

enGameChoice GetComputerChoice() {

	return (enGameChoice) GetRandomNumber(1, 3);

}

enWinner WhoIsTheWinner(stRoundInfo RoundInfo) {

	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
		return enWinner::Draw;

	switch (RoundInfo.PlayerChoice)
	{

	case enGameChoice::Rock:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper) {
			return enWinner::Computer;
		}
			break;
		
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor) {
			return enWinner::Computer;
		}
			break;
		
	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Rock) {
			return enWinner::Computer;
		}
			break;
		

	}

	return enWinner::Player;

}

void CountPoints(short &PlayerWinTimes, short &ComputerWinTimes, short &DrawTimes, enWinner Winner) {

	switch (Winner)
	{

	case enWinner::Draw: {
		DrawTimes++;
	}
		break;

	case enWinner::Computer: {
		ComputerWinTimes++;
	}
		break;

	case enWinner::Player: {
		PlayerWinTimes++;
	}
		break;

	}
}

string TheChoice(enGameChoice Choice) {

	string Choices[3] = { "Rock", "Paper", "Scissor" };

	return Choices[Choice - 1];

}

string TheWinner(enWinner Winner) {

	string Winners[3] = { "Player", "Computer", "No Winner" };

	return Winners[Winner - 1];

}

void SetWinnerColor(enWinner Winner) {

	switch (Winner)
	{

	case enWinner::Player: {
		system("color 2F");
	}
		break;

	case enWinner::Computer: {
		system("color 4F");
		cout << "\a";
	}
		break;

	default: {
		system("color 6F");
	}
		break;
	}
}

string Tabs(short NumberOfTabs) {

	string Tab = "";

	for (int i = 0; i < NumberOfTabs; i++) {
		Tab = Tab + "\t";
	}

	return Tab;

}

void RoundResult(stRoundInfo RoundInfo) {

	cout << "________________ Round[" << RoundInfo.NumberRound << "] ________________\n\n";
	cout << "Player Choice  : " << TheChoice(RoundInfo.PlayerChoice) << "\n";
	cout << "Computer Choice: " << TheChoice(RoundInfo.ComputerChoice) << "\n";
	cout << "Round Winner   : " << TheWinner(RoundInfo.RoundWinner) << "\n";
	cout << "__________________________________________\n\n";

	SetWinnerColor(RoundInfo.RoundWinner);

}

enWinner WhoIsTheFinalWinner(short PlayerWonTimes, short ComputerWonTimes) {

	if (PlayerWonTimes == ComputerWonTimes)
		return enWinner::Draw;

	else if (PlayerWonTimes < ComputerWonTimes)
		return enWinner::Computer;

	else
		return enWinner::Player;

}

stFinalResultInfo FinalResultInfo(short NumberOfRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes) {

	stFinalResultInfo FinalResults;

	FinalResults.NumberOfRounds = NumberOfRounds;
	FinalResults.PlayerWonTimes = PlayerWinTimes;
	FinalResults.ComputerWonTimes = ComputerWinTimes;
	FinalResults.DrawTimes = DrawTimes;
	FinalResults.FinalWinner = WhoIsTheFinalWinner(PlayerWinTimes, ComputerWinTimes);

	return FinalResults;

}

void ShowGameOverScreen() {

	cout << Tabs(2) << "_____________________________________________________________\n\n";
	cout << Tabs(5) << "+++ Game Over +++\n";
	cout << Tabs(2) << "_____________________________________________________________\n\n";

}

void ShowFinalResult(stFinalResultInfo FinalResultInfo) {

	ShowGameOverScreen();

	cout << Tabs(2) << "________________________ [ Game Results ] ___________________\n\n";
	cout << Tabs(2) << "Game Rounds: " << FinalResultInfo.NumberOfRounds << "\n";
	cout << Tabs(2)  << "Player Won Times: " << FinalResultInfo.PlayerWonTimes << "\n";
	cout << Tabs(2) << "Computer Won Times: " << FinalResultInfo.ComputerWonTimes << "\n";
	cout << Tabs(2) << "Draw Times: " << FinalResultInfo.DrawTimes << "\n";
	cout << Tabs(2) << "Final Winner: " << TheWinner(FinalResultInfo.FinalWinner) << "\n";
	cout << Tabs(2) << "______________________________________________________________\n\n";

	SetWinnerColor(FinalResultInfo.FinalWinner);

}

stFinalResultInfo PlayGame(short NumberOfRounds) {

	stRoundInfo RoundInfo;

	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	
	cout << endl;

	for (int RoundNumber = 1; RoundNumber <= NumberOfRounds; RoundNumber++) {

		cout << "Round [" << RoundNumber << "] begins:\n";
		
		RoundInfo.NumberRound = RoundNumber;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.RoundWinner = WhoIsTheWinner(RoundInfo);

		CountPoints(PlayerWinTimes, ComputerWinTimes, DrawTimes, RoundInfo.RoundWinner);
		
		cout << "\n";

		RoundResult(RoundInfo);
	}

	return FinalResultInfo(NumberOfRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);


}

void ResetScreen() {
	system("color 0F");
	system("CLS");
}

void StartGame() {

	char PlayAgain = 'Y';

	do
	{

		ResetScreen();
		stFinalResultInfo FinalResults = PlayGame(ReadNumberOfRounds());
		ShowFinalResult(FinalResults);
		cout << Tabs(2) << "Do you want to play again ? Y/N" << endl;
		cout << Tabs(2);
		cin >> PlayAgain;
		

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}


int main()
{
	srand((unsigned)time(NULL));
	
	StartGame();

	return 0;
}
