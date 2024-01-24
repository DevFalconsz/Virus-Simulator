#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main()
{
    int selectionVirus;

    SetConsoleOutputCP(CP_UTF8);

    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "  __      ___                   _____ _                 _       _               " << endl;
    cout << "  \\ \\    / (_)                 / ____(_)               | |     | |             " << endl;
    cout << "   \\ \\  / / _ _ __ _   _ ___  | (___  _ _ __ ___  _   _| | __ _| |_ ___  _ __  " << endl;
    cout << "    \\ \\/ / | | '__| | | / __|  \\___ \\| | '_ ` _ \\| | | | |/ _` | __/ _ \\| '__| " << endl;
    cout << "     \\  /  | | |  | |_| \\__ \\  ____) | | | | | | | |_| | | (_| | || (_) | |    " << endl;
    cout << "      \\/   |_|_|   \\__,_|___/ |_____/|_|_| |_| |_|\\__,_|_|\\__,_|\\__\\___/|_|    " << endl;
    cout << "                                                     Created by: DevFalconsz" << endl
         << endl;

    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "Options: " << endl;
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "[1] HIV (Human Immunodeficiency Virus)" << endl;
    cout << "[2] Influenza (Influenza Virus)" << endl;
    cout << "[3] SARS-CoV-2 (COVID-19 virus)" << endl;
    cout << "[4] Herpes Simplex Vírus (HSV)" << endl;
    cout << "[5] Hepatitis C Virus (HCV)" << endl << endl;

    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "WARNING: Average replication cycles were used to estimate viral multiplication rates for different viruses." << endl;  
    cout << "Considering ideal conditions and continuous replication, and may vary depending on specific host and environmental factors." << endl;

    do
    {
        setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << endl
             << "Enter the virus you want to see its multiplication : ";
        cin >> selectionVirus;

        if (selectionVirus == 0 || selectionVirus < 0 || selectionVirus > 5)
        {
            cout << endl
                 << "Wrong virus selection, not found in the database." << endl;
            cout << endl
                 << "Enter the virus you want to see its multiplication : ";
            cin >> selectionVirus;
        }
    } while (selectionVirus == 0 || selectionVirus < 0 || selectionVirus > 5);

    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    // Abre um archive para escrita
    ofstream archive("virus_selection.txt");

    // Verifica se o archive foi aberto com sucesso
    if (archive.is_open())
    {
        // Escreve o valor da variável no archive
        archive << selectionVirus;

        // Fecha o archive
        archive.close();
    }
    else
    {
        cerr << "ARCHIVE ERROR." << endl;
        return 1;
    }

    system("cd.. && main.exe");

    return 0;
}
