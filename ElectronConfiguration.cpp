#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

string Level[19] = {
    "1S",
    "/2S",",2P",
    "/3S",",3P",
    "/4S",",3D",",4P",
    "/5S",",4D",",5P",
    "/6S",",4F",",5D",",6P" };
string ElectronCapacity[19] = {
    "2",
    "2","6",
    "2","6",
    "2","10","6",
    "2","10","6",
    "2","14","10","6",
    "2","14","10","6" };
string Print[19];

struct stInfo
{
    int Remain = 0;
    int N = 0;
};

void vValidation(int& Number)
{
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "It must be a \"NUMBER\" : ";
		cin >> Number;
	}
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void vNumberZone(int& Number, int From, int To)
{
	while (Number > To || Number < From)
	{
		cout << "The Number must be (" << From << "-" << To << ") : ";
		cin >> Number;
		vValidation(Number);
	}
}

void vWordZone(string& Word, int From, int To)
{
	while (Word.length() > To || Word.length() < From && !(Word == "x" || Word == "X"))
	{
		if (Word.length() < From)
			cout << "Too short, ";
		else
			cout << "Too long, ";

		cout << "Must be (" << From << "-" << To << ") : ";
		cin >> Word;
	}
}

int iReadPositiveNumber(string Text)
{
    int Num;
    do{
        cout << Text;
        cin >> Num;
        vValidation(Num);
    } while (Num < 1);

    return Num;
}

void vResetScreen()
{
    system("cls");
    system("color 0F");
}

bool bContinueProject(string Text)
{
    char Continue = ' ';
    do{
        cout << Text;
        cin >> Continue;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (!(Continue == 'y' || Continue == 'Y' || Continue == 'n' || Continue == 'N'));

    if (Continue == 'y' || Continue == 'Y')
        return 1;
    else
        return 0;
}

void vResetInfo(stInfo Info)
{
    Info.N = 0;
    Info.Remain = 0;
}

stInfo stCalculation(int Number)
{
    int i = 86;
    stInfo Info;

    vResetInfo(Info);
    Info.Remain = Number - i;

    if (Info.Remain < 0) 
    {
        i = 54;
        for (int j = 18; j >= 2; j -= 8)
        {
            for (i; i > 18; i -= 18)
            {
                Info.Remain = Number - i;
                Info.N++;
                if (Info.Remain >= 0) {
                    break;
                }
            }

            if (Info.Remain >= 0) {

                break;
            }
            else {
                Info.Remain = Number - j;
            }

            Info.N++;
        }
    }

    Info.N = 6 - Info.N;
    return Info;
}

string sgInertGas(stInfo Info)
{
    vResetInfo(Info);

    if (Info.N == 3 || Info.N == 4 || Info.N == 5)
        Info.N = 3 * Info.N - 4;
    else if (Info.N == 2 || Info.N == 6)
        Info.N = 3 * Info.N - 3;
    else if (Info.N == 1 || Info.N == 7)
        Info.N = 3 * Info.N - 2;

    for (int X = 0; X < Info.N; X++)
        Print[X] = Level[X] + ElectronCapacity[X];

    for (int X = 1; X < Info.N; X++)
        Print[0] += Print[X];

    if (Info.Remain == -1)
        Print[0] = "1S1";

    return Print[0];
}

string sgRemain(stInfo Info)
{
    vResetInfo(Info);
    string Result = "";

    if (Info.Remain > 0) {

        if (Info.Remain >= 2) {
            Info.Remain -= 2;
            Result = to_string(Info.N + 1) + "S" + "2,";
        }
        else {
            Result = to_string(Info.N + 1) + "S" + to_string(Info.Remain);
            Info.Remain = 0;
        }

        if (Info.N + 1 >= 6) {

            if (Info.Remain < 15 && Info.Remain > 0)
            {
                Result += to_string(Info.N - 1) + "F" + to_string(Info.Remain - 1) + ",";
                Result += to_string(Info.N) + "D" + "1,";
                Info.Remain = 0;
            }
            else
            {
                if (Info.Remain >= 14) {
                    Info.Remain -= 14;
                    Result += to_string(Info.N - 1) + "F" + "14,";
                }
                else if (Info.Remain > 0) {
                    Result += to_string(Info.N - 1) + "F" + to_string(Info.Remain);
                    Info.Remain = 0;
                }

                if (Info.Remain >= 10) {
                    Info.Remain -= 10;
                    Result += to_string(Info.N) + "D" + "10,";
                }
                else if (Info.Remain > 0) {
                    Result += to_string(Info.N) + "D" + to_string(Info.Remain);
                    Info.Remain = 0;
                }
            }

            if (Result == "6S2,4F14,5D4")
                Result = "6S1,4F14,5D5";
            else if (Result == "6S2,4F14,5D9")
                Result = "6S1,4F14,5D10";
            else if (Result == "7S2,5F14,6D4")
                Result = "7S1,5F14,6D5";
            else if (Result == "7S2,5F14,69")
                Result = "7S1,5F14,6D10";

            if (Info.Remain >= 6) {
                Info.Remain -= 6;
                Result += to_string(Info.N + 1) + "P" + "6,";
            }
            else if (Info.Remain > 0) {
                Result += to_string(Info.N + 1) + "P" + to_string(Info.Remain);
                Info.Remain = 0;
            }
        }
        else if (Info.N + 1 >= 4) {

            if (Info.Remain >= 10) {
                Info.Remain -= 10;
                Result += to_string(Info.N) + "D" + "10,";
            }
            else if (Info.Remain > 0) {
                Result += to_string(Info.N) + "D" + to_string(Info.Remain);
                Info.Remain = 0;
            }

            if (Result == "4S2,3D4")
                Result = "4S1,3D5";
            else if (Result == "4S2,3D9")
                Result = "4S1,3D10";
            else if (Result == "5S2,4D4")
                Result = "5S1,4D5";
            else if (Result == "5S2,4D9")
                Result = "5S1,4D10";

            if (Info.Remain >= 6) {
                Info.Remain -= 6;
                Result += to_string(Info.N + 1) + "P" + "6,";
            }
            else if (Info.Remain > 0) {
                Result += to_string(Info.N + 1) + "P" + to_string(Info.Remain);
                Info.Remain = 0;
            }

        }
        else if (Info.N + 1 >= 2) {

            if (Info.Remain >= 6) {
                Info.Remain -= 6;
                Result += to_string(Info.N + 1) + "P" + "6,";
            }
            else if (Info.Remain > 0) {
                Result += to_string(Info.N + 1) + "P" + to_string(Info.Remain);
                Info.Remain = 0;
            }
        }
    }

    if (Result != "") {
        Result = "/" + Result;
    }

    return Result;
}

void vStart(bool YesOrNo)
{
    if (YesOrNo == 1)
    {
        int Number = iReadPositiveNumber("Please enter the atomic number : ");
        vNumberZone(Number, 1, 118);

        string InvertGas = sgInertGas(stCalculation(Number));
        string Remain = sgRemain(stCalculation(Number));

        cout << endl << InvertGas + Remain << endl;
        cout << "\n--------------------------------------------\n";
    }
}

void vElectronConfiguration()
{
     do{
         vStart(1);
     } while (bContinueProject("\nDo you want to Continue?... (y/n): "));
}

int main ()
{
    vElectronConfiguration();
    return 0;
}