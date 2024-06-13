#include "func.h"

bool UndoRedoMode = false;

void States::getNewState(int map[][MAX_SIZE])
{
    while (current->next)
    {
        State* temp = current->next;
        current->next = current->next->next;
        delete temp;
        size--;
    }

    current->next = new State();
    memcpy(current->next->gameboard, map, sizeof(map));
    current->next->previous = current;
    current = current->next;
    size++;

    if (size > 5) // Remove head
    {
        State* temp = head;
        head = head->next;
        delete temp;
    }
}

void States::Undo(int map[][MAX_SIZE])
{
    if (current->previous)
    {
        current = current->previous;
        memcpy(map, current->gameboard, sizeof(map));
    }
    else
        return;
}

void States::Redo(int map[][MAX_SIZE])
{
    if (current->next)
    {
        current = current->next;
        memcpy(map, current->gameboard, sizeof(map));
    }
    else
        return;
}

// Function to clear the screen
void Clear()
{
    system("cls");
}

// Function to set color for text
void SetColor(int color)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

// function to print "2048" pattern and introduction to the screen
void Display2048()
{
    SetColor(LIGHT_AQUA);
    cout << " /\\\\\\\\\\\\\\\\\\          /\\\\\\\\\\\\\\                /\\\\\\         /\\\\\\\\\\\\\\\\\\\n";
    cout << "/\\\\\\///////\\\\\\      /\\\\\\/////\\\\\\            /\\\\\\\\\\       /\\\\\\///////\\\\\\\n";
    cout << "\\///      \\//\\\\\\    /\\\\\\    \\//\\\\\\         /\\\\\\/\\\\\\      \\/\\\\\\     \\/\\\\\\\n";
    SetColor(AQUA);
    cout << "           /\\\\\\/    \\/\\\\\\     \\/\\\\\\       /\\\\\\/\\/\\\\\\        \\///\\\\\\\\\\\\/\n";
    cout << "        / \\\\\\//      \\/\\\\\\     \\/\\\\\\     /\\\\\\/  \\/\\\\\\       /\\\\\\///////\\\\\\\n";
    cout << "       /\\\\\\//         \\/\\\\\\     \\/\\\\\\   /\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\   /\\\\\\      \\//\\\\\\\n";
    SetColor(BLUE);
    cout << "       /\\\\\\/            \\//\\\\\\    /\\\\\\   \\///////////\\\\\\//   \\//\\\\\\      /\\\\\\\n";
    cout << "       /\\\\\\\\\\\\\\\           \\///\\\\\\\\\\\\\\/              \\/\\\\\\      \\///\\\\\\\\\\\\\\\\\\/\n";
    cout << "       \\///////////////      \\///////                \\///         \\/////////\n";
    SetColor(WHITE);
    cout << "\n-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
    SetColor(BLUE);
    cout << "\n- 2048 is a captivating puzzle game where players combine numbered tiles to reach 2048.\n";
    cout << "- With its minimalist design, it offers addictive gameplay and endless challenges.\n";
    cout << "- This version is developed by student";
    SetColor(LIGHT_AQUA);
    cout << " Phan Anh Tuan, ID: 23120187\n\n";
    SetColor(WHITE);
    cout << "                           ";
    Clear();
}

// Function to print menu to screen
void PrintMenu()
{
    SetColor(RED);
    cout << "                                  =====MAIN MENU=====\n\n";
    SetColor(YELLOW);
    cout << "                                  0. Exit\n";
    SetColor(LIGHT_YELLOW);
    cout << "                                  1. New game\n";
    SetColor(YELLOW);
    cout << "                                  2. Game settings\n";
    SetColor(LIGHT_YELLOW);
    cout << "                                  3. Top 20 players\n";
    SetColor(YELLOW);
    cout << "                                  4. Resume\n";
    SetColor(LIGHT_YELLOW);
    cout << "                                  5. Instruction\n";
    SetColor(WHITE);
}

// Function to print menu
void Menu(PlayerAccount& p, int& size, int map[][10])
{
    int option = -1;
    while (true)
    {
        PrintMenu();

        cout << "                                  \nYour option: ";
        cin >> option;

        // NOTE CỦA ANH TRƯỜNG:
        // Mất kí tự đầu có là do em chưa ignore sau khi cin option nè!!!'
        // Vì cls nó chỉ xoá màn hình thôi chứ không xoá bộ nhớ đầu vào nên căn bản nó vẫn còn kí tự xuống dòng trong bộ nhớ đầu vào
        cin.ignore();
        ///////////////////////////////////////////////////////////////////

        system("cls");

        switch (option)
        {
        case 0:
        {
            return;
        }
        case 1:
        {
            NewGame(p, size, map);
            break;
        }
        case 2:
        {
            GameSetting(p, size, map);
            break;
        }
        case 3:
        {
            Top20Display();
            break;
        }
        case 5:
        {
            ShowInstruction();
            break;
        }
        // Build thêm cái default nè
        }

        system("cls");
    }
}

//====================CASE 1====================//
// Funtion to start a new game
void NewGame(PlayerAccount& p, int& size, int map[][10])
{
    SignUp(p);
    PlayGame(p, size, map);
}

// Funtion to let new player sign up
void SignUp(PlayerAccount& p)
{
    SetColor(RED);
    cout << "                                  ----SIGN UP----\n\n";
    while (true)
    {
        SetColor(WHITE);
        cout << "                                  Enter your name: ";
        cin.ignore(); // bug ở đây bị mất ki tự đầu (EM CÓ THỂ CHUYỂN LÊN TRƯỚC KHI COUT ENTER YOUR NAME NẾU CÁI CIN.IGNORE ANH THÊM Ở HÀM MENU KHÔNG CÓ TÁC DỤNG)
        string buffer;
        getline(cin, buffer);
        strcpy_s(p.Username, buffer.c_str());
        // Check if the username already exists
        if (UsernameExists(p.Username))
        {
            cout << "Username already exists. Please choose a different username." << endl;
            Clear();
        }
        else
            break;
    }

    cout << "                                  Enter your password: ";
    string buffer;
    getline(cin, buffer);
    strcpy_s(p.Password, buffer.c_str());
    p.score = 0;
    p.time = 0;
    // SaveNewPlayerAccountToFile(p);
}
// Function to check if a username has existed
bool UsernameExists(const string& username)
{
    ifstream inFile("PlayerList.bin", ios::binary);
    if (!inFile)
        return false; // File does not exist, so username can't exist either

    string user, pass;
    int score;
    int ptime;
    while (!inFile.eof())
    {
        char* buffer = new char[sizeof(PlayerAccount)];
        inFile.read(buffer, sizeof(PlayerAccount));
        PlayerAccount account = *reinterpret_cast<PlayerAccount*>(&buffer);
        delete[] buffer;
        if (account.Username == username)
            return true;
    }
    return false;
}

//====================CASE 2====================//
// Function to set modes of game
void GameSetting(PlayerAccount& p, int& size, int map[][10])
{
    int option = -1;
    while (true)
    {
        SetColor(RED);
        cout << "                                  -----GAME SETTINGS-----\n\n";
        SetColor(LIGHT_YELLOW);
        cout << "                                  0. Exit\n";
        SetColor(YELLOW);
        cout << "                                  1. Size setting\n";
        SetColor(LIGHT_YELLOW);
        cout << "                                  2. Undo & Redo mode: ON\n";
        SetColor(YELLOW);
        cout << "                                  3. Undo & Redo mode: OFF\n\n";
        SetColor(WHITE);

        cout << "Your option is: ";
        cin >> option;

        switch (option)
        {
        case 0:
            return;

        case 1:
        {
            // Size setting
            cout << "                                  Enter the size of the map (from 2 to 8): ";
            cin >> size;
            break;
        }
        case 2:
        {
            UndoRedoMode = true;
            break;
        }
        case 3:
        {
            UndoRedoMode = false;
            break;
        }
        }

        system("cls");
    }
}

//====================CASE 3====================//
void Top20Display()
{
    SetColor(RED);
    cout << "---TOP 20 BEST PLAYERS---\n";
    SetColor(WHITE);
    SortPlayersByScore();
    ifstream file("PlayerList.txt");
    if (file.is_open())
    {
        const int top20 = 20;
        PlayerAccount players[top20];
        int numPlayers = 0; // Number of players read from file

        // Read player data from file
        string line;
        while (getline(file, line) && numPlayers < top20)
        {
            stringstream ss(line);
            ss >> players[numPlayers].Username >> players[numPlayers].Password >> players[numPlayers].score >> players[numPlayers].time;
            numPlayers++;
        }
        file.close();
        for (int i = 0; i < top20; i++)
        {
            if (players[i].Username == "")
                break;
            cout << i + 1 << " - " << players[i].Username << " - Score: " << players[i].score << " - Time: " << players[i].time << endl;
        }
    }
    else
    {
        cout << "Unable to open file for reading!" << endl;
    }
}

// Function to read players from file, sort by score, and write back to file
void SortPlayersByScore()
{
    ifstream file("PlayerList.bin", ios::binary); // Open file for reading
    if (file.is_open())
    {
        const int top20 = 20;
        PlayerAccount players[top20];
        int numPlayers = 0; // Number of players read from file

        // Read player data from file
        string line;
        while (!file.eof())
        {
            char* buffer = NULL;
            file.read(buffer, sizeof(PlayerAccount));
            players[numPlayers] = *reinterpret_cast<PlayerAccount*>(buffer);
            numPlayers++;
        }
        file.close(); // Close file

        // Sort players by score (in descending order)
        sort(players, players + numPlayers, comparePlayers);

        // Open file for writing (overwrite mode)
        ofstream outFile("PlayerList.bin", ios::binary);
        if (outFile.is_open())
        {
            // Write sorted player data to file
            for (int i = 0; i < numPlayers; i++)
            {
                outFile.write(reinterpret_cast<char*>(&players[i]), sizeof(PlayerAccount));
            }
            outFile.close(); // Close file
        }
        else
        {
            cout << "Unable to open file for writing!" << endl;
        }
    }
    else
    {
        cout << "Unable to open file for reading!" << endl;
    }
}
// Comparison function for sorting players by score (in descending order)
bool comparePlayers(const PlayerAccount& p1, const PlayerAccount& p2)
{
    return p1.score > p2.score;
}

//====================CASE 4====================//

//====================CASE 5====================//
void ShowInstruction()
{
    SetColor(RED);
    cout << "                                  =====INSTRUCTION=====\n\n";
    SetColor(WHITE);
    cout << "                                  - Default: Game size: 4 - Undo&Redo mode: OFF \n";
    cout << "                                  - Go to Game Settings to set the game size, and turn on/off the Undo&Redo mode \n";
    cout << "                                  - Press arrow buttons to go up/down/left/right \n";
    cout << "                                  - Press e button to exit immediately \n";
    cout << "                                  - Press u button to undo\n";
    cout << "                                  - Press r button to redo \n";
    system("pause");
}

//====================PLAY GAME====================//
// Function to play game
void PlayGame(PlayerAccount& p, int& size, int map[][10])
{

    for (short i = 0; i < size; i++)
    {
        for (short j = 0; j < size; j++)
        {
            map[i][j] = 0;
        }
    }
    // Two first number
    RandomNumber(size, map);
    RandomNumber(size, map);

    States states;

    states.current = new State();
    memcpy(&states.current->gameboard, map, sizeof(map));
    states.head = states.current;
    states.current->next = nullptr;
    states.current->previous = nullptr;

    short currentCol = MARGIN_LEFT;
    short currentRow = MARGIN_TOP;

    // Init state
    saveState savedStates[5];
    fstream input("savedGame.bin", ios::binary);
    char* buffer = NULL;
    input.read(buffer, sizeof(savedStates[0])*5);
    //===========

    system("cls");
    DrawBoard(size, map, currentCol, currentRow);

    high_resolution_clock::time_point start; // Variable to store the start time
    StartTimer(start);                       // Start the timer

    while (true)
    {

        ShowScore(p, size, map);

        int key = _getch();

        system("cls");

        if (key == 114 && UndoRedoMode && states.current->next) // Redo
        {
            states.current = states.current->next;
            memcpy(map,states.current->gameboard, sizeof(map));
        } else

        if (key == 117 && UndoRedoMode && states.current->previous) // Undo
        {
            states.current = states.current->previous;
            memcpy(map, states.current->gameboard, sizeof(map));
        } else

        if (key == 224 ) // <- or "a"
        {
            int k = _getch(); // events from keyboard
            cout << k << "," <<key << endl;

            HandleEventFromKeyboard(size, map, k);

            if (UndoRedoMode)
            {
                states.getNewState(map);
                /*cout << UndoRedoMode << "," << key;
                cout << states.current->gameboard[0][0] << endl;*/
            }

           

            if (GameWin(size, map))
            {
                p.time += StopTimer(start);
                p.score = Score(p, size, map);
                SaveNewPlayerAccountToFile(p);
                DisplayWinPattern();
                ScoreDisplayWhenReaching2048(p);
            }

            if (!isFull(size, map) && key != 114 && key != 117)
            {
                RandomNumber(size, map);
            } else
            {
                p.time = StopTimer(start);
                system("cls");
                SetColor(RED);
                cout << "GAME OVER\n";
                SetColor(WHITE);
                p.score = Score(p, size, map);
                cout << "Your final score: " << p.score << endl;
                cout << "Time: " << p.time << " seconds " << endl;
                SaveNewPlayerAccountToFile(p);
                break;
            }

       
        }
        DrawBoard(size, map, currentCol, currentRow);
        if (key == 13 || key == 'e') {
            cout << "You are going to exit, do you want to save your games?" << endl;
            int exit_code;
            cin >> exit_code;
            if (exit_code == 13) {
                saveState save;
                memcpy(save.gameboard, map, sizeof(map));
                save.player = p;
                save.player.time = StopTimer(start);
                /*ostream file(save.player.Username+".bin",)*/
            }

        }
    }
}

////Function to randomly initialize number 2 or 4 at a random empty position
void RandomNumber(int& size, int map[][10])
{
    int pos1, pos2;
    srand(time(0));

    do
    {
        pos1 = rand() % size;
        pos2 = rand() % size;
    } while (map[pos1][pos2] != 0);

    do
    {
        map[pos1][pos2] = 2 + rand() % 3;
    } while (map[pos1][pos2] == 3);
    //// to test 2048 reaching situation
    // if (pos1 == pos2)
    //	map[pos1][pos2] = 2048;
}

////Function to draw game board
void DrawBoard(int& size, int map[][MAX_SIZE], short& currentCol, short& currentRow)
{

    currentCol = MARGIN_LEFT;
    currentRow = MARGIN_TOP;

    GoToxy(currentCol, currentRow);
    cout << char(218);
    for (short i = 1; i < size * 8; i++)
    {
        if (i % 8 == 0)
        {
            cout << char(194);
        }
        else
        {
            cout << char(196);
        }
    }
    cout << char(191);
    currentRow++;

    for (short i = 1; i < size * 4; i++)
    {
        currentCol = MARGIN_LEFT;
        if (i % 4 == 0)
        {
            currentCol = MARGIN_LEFT;
            GoToxy(currentCol, currentRow);
            cout << char(195);
            for (short j = 1; j < size * 8; j++)
            {
                if (j % 8 == 0)
                {
                    cout << char(197);
                }
                else
                {
                    cout << char(196);
                }
            }
            cout << char(180);
        }
        else if ((i - 2) % 4 == 0)
        {
            currentCol = MARGIN_LEFT;
            GoToxy(currentCol, currentRow);
            cout << char(179);
            for (short j = 1; j < size * 8; j++)
            {
                if (j % 8 == 0)
                {
                    currentCol++;
                    GoToxy(currentCol, currentRow);
                    cout << char(179);
                }
                else if ((j - 4) % 8 == 0)
                {
                    // draw numbers
                    currentCol++;
                    GoToxy(currentCol, currentRow);

                    short x, y;
                    if ((i - 2) % 4 == 0)
                        y = (i - 2) / 4;
                    if ((j - 4) % 8 == 0)
                        x = (j - 4) / 8;

                    int number = map[x][y];
                    if (number != 0)
                    {

                        NumberColor(number);

                        switch (CountNumbers(number))
                        {
                        case 1:
                            currentCol -= 6;
                            cout << " " << map[x][y] << " ";
                            currentCol += 6;
                            break;
                        case 2:
                            currentCol--;
                            GoToxy(currentCol, currentRow);
                            cout << " " << map[x][y] << " ";
                            currentCol++;
                            break;
                        case 3:
                            currentCol -= 2;
                            GoToxy(currentCol, currentRow);
                            cout << " " << map[x][y] << " ";
                            currentCol += 2;
                            break;
                        case 4:
                            currentCol -= 3;
                            GoToxy(currentCol, currentRow);
                            cout << " " << map[x][y] << " ";
                            currentCol += 3;
                            break;
                        default:
                            currentCol -= 3;
                            GoToxy(currentCol, currentRow);
                            cout << " " << map[x][y] << " ";
                            currentCol += 3;
                        }
                        SetColor(15);
                    }
                }
                else
                {
                    currentCol++;
                    GoToxy(currentCol, currentRow);
                }
            }
            currentCol++;
            GoToxy(currentCol, currentRow);
            cout << char(179);
        }
        else if (i % 2 != 0)
        {
            for (short j = 0; j <= size * 8; j++)
            {
                if (j % 8 == 0)
                {
                    GoToxy(currentCol, currentRow);
                    cout << char(179);
                    currentCol++;
                }
                else
                {
                    currentCol++;
                    GoToxy(currentCol, currentRow);
                }
            }
        }
        currentRow++;
    }

    currentCol = MARGIN_LEFT;
    GoToxy(currentCol, currentRow);
    cout << char(192);
    for (short i = 1; i < size * 8; i++)
    {
        if (i % 8 == 0)
        {
            cout << char(193);
        }
        else
        {
            cout << char(196);
        }
    }
    cout << char(217);
    currentRow++;
}
// Function to go to a point on Console
void GoToxy(short x, short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x, y };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
// Function to set color of number displayed on Console
void NumberColor(int number)
{
    switch (number)
    {
    case 2:
    {
        SetColor(LIGHT_AQUA);
        break;
    }
    case 4:
    {
        SetColor(LIGHT_BLUE);
        break;
    }
    case 8:
    {
        SetColor(LIGHT_GREEN);
        break;
    }
    case 16:
    {
        SetColor(AQUA);
        break;
    }
    case 32:
    {
        SetColor(PURPLE);
        break;
    }
    case 64:
    {
        SetColor(BLUE);
        break;
    }
    case 128:
    {
        SetColor(GREEN);
        break;
    }
    case 256:
    {
        SetColor(LIGHT_YELLOW);
        break;
    }
    case 512:
    {
        SetColor(YELLOW);
        break;
    }
    case 1024:
    {
        SetColor(LIGHT_RED);
        break;
    }
    case 2048:
    {
        SetColor(RED);
        break;
    }
    }
}
// Function to count digits of a number
short CountNumbers(int x)
{
    short count = 0;
    do
    {
        count++;
        x = x / 10;
    } while (x > 0);
    return count;
}

////Function to start the timer
void StartTimer(high_resolution_clock::time_point& start)
{
    start = high_resolution_clock::now();
}

////Function to print score to the screen
void ShowScore(PlayerAccount& p, int& size, int map[][10])
{
    cout << endl
        << "Score: ";
    SetColor(YELLOW);
    cout << Score(p, size, map);
    SetColor(WHITE);
}
// Function to calculate the total score of player
int Score(PlayerAccount& p, int& size, int map[][10])
{
    int total = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            total += map[i][j];
    }
    return total;
}

////
void HandleEventFromKeyboard(int& size, int map[][10], int k)
{
    switch (k)
    {
    case 72: // UP
        GoUp(size, map);
        break;
    case 75: // LEFT
        GoLeft(size, map);
        break;
    case 77: // RIGHT
        GoRight(size, map);
        break;
    case 80: // DOWN
        GoDown(size, map);
        break;
    }
}
// Functions to handle events (up, down, left, right) from keyboard
void GoUp(int& size, int map[][10])
{
    // fill spaces
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if (!map[x][y])
            {
                for (int z = y + 1; z < size; z++)
                {
                    if (map[x][z])
                    {
                        map[x][y] = map[x][z];
                        map[x][z] = 0;
                        break;
                    }
                }
            }
        }
    }

    // update values
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size - 1; y++)
        {
            if (map[x][y] == map[x][y + 1])
            {
                map[x][y] *= 2;
                map[x][y + 1] = 0;
            }
        }
    }

    // fill spaces
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if (!map[x][y])
            {
                for (int z = y + 1; z < size; z++)
                {
                    if (map[x][z])
                    {
                        map[x][y] = map[x][z];
                        map[x][z] = 0;
                        break;
                    }
                }
            }
        }
    }
}
void GoDown(int& size, int map[][10])
{
    // fill spaces
    for (int x = 0; x < size; x++)
    {
        for (int y = size - 1; y > 0; y--)
        {
            if (!map[x][y])
            {
                for (int z = y - 1; z >= 0; z--)
                {
                    if (map[x][z])
                    {
                        map[x][y] = map[x][z];
                        map[x][z] = 0;
                        break;
                    }
                }
            }
        }
    }

    // update values
    for (int x = size - 1; x >= 0; x--)
    {
        for (int y = size - 1; y > 0; y--)
        {
            if (map[x][y] == map[x][y - 1])
            {
                map[x][y] *= 2;
                map[x][y - 1] = 0;
            }
        }
    }

    // fill spaces
    for (int x = 0; x < size; x++)
    {
        for (int y = size - 1; y > 0; y--)
        {
            if (!map[x][y])
            {
                for (int z = y - 1; z >= 0; z--)
                {
                    if (map[x][z])
                    {
                        map[x][y] = map[x][z];
                        map[x][z] = 0;
                        break;
                    }
                }
            }
        }
    }
}
void GoLeft(int& size, int map[][10])
{
    // fill spaces
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if (!map[y][x])
            {
                for (int z = y + 1; z < size; z++)
                {
                    if (map[z][x])
                    {
                        map[y][x] = map[z][x];
                        map[z][x] = 0;
                        break;
                    }
                }
            }
        }
    }

    // update values
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size - 1; y++)
        {
            if (map[y][x] == map[y + 1][x])
            {
                map[y][x] *= 2;
                map[y + 1][x] = 0;
            }
        }
    }

    // fill spaces
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            if (!map[y][x])
            {
                for (int z = y + 1; z < size; z++)
                {
                    if (map[z][x])
                    {
                        map[y][x] = map[z][x];
                        map[z][x] = 0;
                        break;
                    }
                }
            }
        }
    }
}
void GoRight(int& size, int map[][10])
{
    // fill spaces
    for (int x = 0; x < size; x++)
    {
        for (int y = size - 1; y >= 0; y--)
        {
            if (!map[y][x])
            {
                for (int z = y - 1; z >= 0; z--)
                {
                    if (map[z][x])
                    {
                        map[y][x] = map[z][x];
                        map[z][x] = 0;
                        break;
                    }
                }
            }
        }
    }

    // update values
    for (int x = 0; x < size; x++)
    {
        for (int y = size - 1; y >= 0; y--)
        {
            if (map[y][x] == map[y - 1][x])
            {
                map[y - 1][x] *= 2;
                map[y][x] = 0;
            }
        }
    }

    // fill spaces
    for (int x = 0; x < size; x++)
    {
        for (int y = size - 1; y >= 0; y--)
        {
            if (!map[y][x])
            {
                for (int z = y - 1; z >= 0; z--)
                {
                    if (map[z][x])
                    {
                        map[y][x] = map[z][x];
                        map[z][x] = 0;
                        break;
                    }
                }
            }
        }
    }
}

////Fucntion to check if the player has won (reach 2048)
bool GameWin(int& size, int map[][10])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (map[i][j] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

////Function to stop the timer and calculate the elapsed time
double StopTimer(high_resolution_clock::time_point start)
{
    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(end - start);
    return time_span.count(); // Return the elapsed time in seconds
}

////Function to display WIN pattern when player reaches 2024.
void DisplayWinPattern()
{
    SetColor(LIGHT_AQUA);
    cout << "\n\n\n\n\n\n\n\n";
    cout << "                                  W       W   IIIII  N     N\n";
    cout << "                                  W       W     I    NN    N\n";
    cout << "                                  W   W   W     I    N N   N\n";
    cout << "                                  W   W   W     I    N  N  N\n";
    cout << "                                   W W W W      I    N   N N\n";
    cout << "                                    W   W     IIIII  N    NN\n";

    for (int i = 0; i < 150; ++i)
    {
        GoToxy(rand() % 100, rand() % 35);
        SetColor(rand() % 16);
        cout << "*";
        Sleep(30);
    }
    SetColor(WHITE);
    Clear();
}

////Function to save the information of a new player to file
void SaveNewPlayerAccountToFile(const PlayerAccount& player)
{
    ofstream outFile("PlayerList.bin", ios::app | ios::binary); // Open file in append mode
    if (!outFile)
    {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    PlayerAccount account2Save = player;

    outFile.write(reinterpret_cast<char*>(&account2Save), sizeof(account2Save));
    outFile.close();
}

////
void ScoreDisplayWhenReaching2048(PlayerAccount& p)
{
    SortPlayersByScore();
    ifstream file("PlayerList.bin", ios::binary);
    if (file.is_open())
    {
        const int top20 = 20;
        PlayerAccount players[top20];
        int numPlayers = 0; // Number of players read from file

        // Read player data from file
        string line;
        while (!file.eof())
        {
            char* buffer = NULL;
            file.read(buffer, sizeof(PlayerAccount));
            players[numPlayers] = *reinterpret_cast<PlayerAccount*>(buffer);
            numPlayers++;
        }
        file.close();
        bool flag = false;
        for (int i = 0; i < top20; i++)
        {
            if (players[i].Username == p.Username)
            { // Because every username is unique
                cout << "Rank: " << i + 1 << " - " << players[i].Username << " - Score: " << players[i].score << " - Time: " << players[i].time << endl;
                flag = true;
            }
        }
        if (flag == false)
            cout << "Unfortunately, you are not in top 20 best players!\n";
    }
    else
    {
        cout << "Unable to open file for reading!" << endl;
    }
}

// Function to check if the map is full, which means there is no available cell left
bool isFull(int& size, int map[][10])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (map[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool LoadSetting(string path)
{
    FILE* file;
    fopen_s(&file, path.c_str(), "rb");
    if (!file)
        return false;
    bool setting;
    fread_s(&setting, 1, 1, 1, file);
    return setting;
}