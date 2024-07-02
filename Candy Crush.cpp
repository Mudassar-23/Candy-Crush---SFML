#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

const int MaxGridSize = 7, MinGridSize = 6;
int Score = 0, TargetScore = 100000000000, Moves = 20;
int Game[MaxGridSize][MaxGridSize];

bool WinCheck() {
    return Score >= TargetScore;
}
bool FailCheck() {
    return Moves == 0;
}

void DeallocateGame(int GridSize) {
    for (int i = 0; i < GridSize; i++) {
        for (int j = 0; j < GridSize; j++) {
            Game[i][j] = 0;
        }
    }
}

//FUNCTION: Candy selection using left mouse button
void Select(RenderWindow& window, RectangleShape& r1, int& selectedX, int& selectedY, int GridSize) {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        Vector2i mousePos = Mouse::getPosition(window);
        selectedX = (mousePos.x - ((1366 - GridSize * 100) / 2)) / 100;
        selectedY = (mousePos.y - ((768 - GridSize * 100) / 2)) / 100;

        //Check if selected position is within grid boundaries
        if (selectedX >= 0 && selectedX < GridSize && selectedY >= 0 && selectedY < GridSize) {
            r1.setPosition(selectedX * 100 + ((1366 - GridSize * 100) / 2), selectedY * 100 + ((768 - GridSize * 100) / 2));
        }
    }
}

//FUNCTION: Swap candies in grid
void SwapCandies(int selectedX, int selectedY, int direction, int GridSize) {
    int TargetX = selectedX, TargetY = selectedY;

    //Determine target position based on direction
    switch (direction) {
    case 0: TargetY--; break;
    case 1: TargetY++; break;
    case 2: TargetX--; break;
    case 3: TargetX++; break;
    }

    if (TargetX >= 0 && TargetX < GridSize && TargetY >= 0 && TargetY < GridSize) {        
        swap(Game[selectedX][selectedY], Game[TargetX][TargetY]);//Swap candies in grid
    }
}

//FUNCTION: Check for matches and remove candies
void CheckMatches(int GridSize) {
    //Loop through each cell in grid
    for (int i = 0; i < GridSize; i++) {
        for (int j = 0; j < GridSize; j++) {
            int CurrentCandy = Game[i][j];//Value of current candy

            //Elbow (bottom-right) candies
            if (i + 1 < GridSize && j + 1 < GridSize && Game[i + 1][j] == CurrentCandy && Game[i + 1][j + 1] == CurrentCandy) {
                Score += 15;
                Game[i][j] = Game[i + 1][j] = Game[i + 1][j + 1] = 0;
            }
            //Elbow (bottom-left) candies
            else if (i + 1 < GridSize && j - 1 >= 0 && Game[i + 1][j] == CurrentCandy && Game[i + 1][j - 1] == CurrentCandy) {
                Score += 15;
                Game[i][j] = Game[i + 1][j] = Game[i + 1][j - 1] = 0;
            }
            //Elbow (top-right) candies
            else if (i - 1 >= 0 && j + 1 < GridSize && Game[i - 1][j] == CurrentCandy && Game[i - 1][j + 1] == CurrentCandy) {
                Score += 15;
                Game[i][j] = Game[i - 1][j] = Game[i - 1][j + 1] = 0;
            }
            //Elbow (top-left) candies
            else if (i - 1 >= 0 && j - 1 >= 0 && Game[i - 1][j] == CurrentCandy && Game[i - 1][j - 1] == CurrentCandy) {
                Score += 15;
                Game[i][j] = Game[i - 1][j] = Game[i - 1][j - 1] = 0;
            }

            //5 horizontal candies
            else if (j + 4 < GridSize && Game[i][j + 1] == CurrentCandy && Game[i][j + 2] == CurrentCandy && Game[i][j + 3] == CurrentCandy && Game[i][j + 4] == CurrentCandy) {
                Score += 30;
                Game[i][j] = Game[i][j + 1] = Game[i][j + 2] = Game[i][j + 3] = Game[i][j + 4] = 0;
            }
            //5 vertical candies
            else if (i + 4 < GridSize && Game[i + 1][j] == CurrentCandy && Game[i + 2][j] == CurrentCandy && Game[i + 3][j] == CurrentCandy && Game[i + 4][j] == CurrentCandy) {
                Score += 30;
                Game[i][j] = Game[i + 1][j] = Game[i + 2][j] = Game[i + 3][j] = Game[i + 4][j] = 0;
            }
            //5 \-diagonal candies
            else if (i - 4 >= 0 && j - 4 >= 0 && Game[i - 1][j - 1] == CurrentCandy && Game[i - 2][j - 2] == CurrentCandy && Game[i - 3][j - 3] == CurrentCandy && Game[i - 4][j - 4] == CurrentCandy) {
                Score += 30;
                Game[i][j] = Game[i - 1][j - 1] = Game[i - 2][j - 2] = Game[i - 3][j - 3] = Game[i - 4][j - 4] = 0;
            }
            //5 /-diagonal candies
            else if (i + 4 < GridSize && j - 4 >= 0 && Game[i + 1][j - 1] == CurrentCandy && Game[i + 2][j - 2] == CurrentCandy && Game[i + 3][j - 3] == CurrentCandy && Game[i + 4][j - 4] == CurrentCandy) {
                Score += 30;
                Game[i][j] = Game[i + 1][j - 1] = Game[i + 2][j - 2] = Game[i + 3][j - 3] = Game[i + 4][j - 4] = 0;
            }

            //4 horizontal candies
            else if (j + 3 < GridSize && Game[i][j + 1] == CurrentCandy && Game[i][j + 2] == CurrentCandy && Game[i][j + 3] == CurrentCandy) {
                Score += 20;
                Game[i][j] = Game[i][j + 1] = Game[i][j + 2] = Game[i][j + 3] = 0;
            }
            //4 vertical candies
            else if (i + 3 < GridSize && Game[i + 1][j] == CurrentCandy && Game[i + 2][j] == CurrentCandy && Game[i + 3][j] == CurrentCandy) {
                Score += 20;
                Game[i][j] = Game[i + 1][j] = Game[i + 2][j] = Game[i + 3][j] = 0;
            }
            //4 \-diagonal candies
            else if (i - 3 >= 0 && j - 3 >= 0 && Game[i - 1][j - 1] == CurrentCandy && Game[i - 2][j - 2] == CurrentCandy && Game[i - 3][j - 3] == CurrentCandy) {
                Score += 20;
                Game[i][j] = Game[i - 1][j - 1] = Game[i - 2][j - 2] = Game[i - 3][j - 3] = 0;
            }
            //4 /-diagonal candies
            else if (i + 3 < GridSize && j - 3 >= 0 && Game[i + 1][j - 1] == CurrentCandy && Game[i + 2][j - 2] == CurrentCandy && Game[i + 3][j - 3] == CurrentCandy) {
                Score += 20;
                Game[i][j] = Game[i + 1][j - 1] = Game[i + 2][j - 2] = Game[i + 3][j - 3] = 0;
            }

            //3 horizontal candies
            else if (j + 2 < GridSize && Game[i][j + 1] == CurrentCandy && Game[i][j + 2] == CurrentCandy) {
                Score += 10;
                Game[i][j] = Game[i][j + 1] = Game[i][j + 2] = 0;
            }
            //3 vertical candies
            else if (i + 2 < GridSize && Game[i + 1][j] == CurrentCandy && Game[i + 2][j] == CurrentCandy) {
                Score += 10;
                Game[i][j] = Game[i + 1][j] = Game[i + 2][j] = 0;
            }
            //3 \-diagonal candies
            else if (i - 2 >= 0 && j - 2 >= 0 && Game[i - 1][j - 1] == CurrentCandy && Game[i - 2][j - 2] == CurrentCandy) {
                Score += 10;
                Game[i][j] = Game[i - 1][j - 1] = Game[i - 2][j - 2] = 0;
            }
            //3 /-diagonal candies
            else if (i + 2 < GridSize && j - 2 >= 0 && Game[i + 1][j - 1] == CurrentCandy && Game[i + 2][j - 2] == CurrentCandy) {
                Score += 10;
                Game[i][j] = Game[i + 1][j - 1] = Game[i + 2][j - 2] = 0;
            }
        }
    }
}

//FUNCTION: Fill empty spaces in grid
void FillGrid(int GridSize) {
    for (int i = 0; i < GridSize; i++) {
        for (int j = GridSize - 1; j >= 0; j--) {
            if (Game[j][i] == 0) {
                //Move candies down to fill the empty space
                for (int k = j; k > 0; k--) {
                    swap(Game[k][i], Game[k - 1][i]);
                }
                Game[0][i] = rand() % 5 + 1;
            }
        }
    }
}

//FUNCTION: Save game state to file
void SaveGame() {
    ofstream SaveFile("Candy Crush (Saved).txt");
    if (SaveFile.is_open()) {
        SaveFile << Score << "\n";
        SaveFile << Moves << "\n";
        for (int i = 0; i < MaxGridSize; i++) {
            for (int j = 0; j < MaxGridSize; j++) {
                SaveFile << Game[i][j] << " ";
            }
            SaveFile << "\n";
        }
        SaveFile.close();
        cout << "Game saved successfully.\n";
    }
    else {
        cout << "Unable to save the game.\n";
    }
}

//FUNCTION: Load game from file
void LoadGame() {
    ifstream SaveFile("Candy Crush (Saved).txt");
    if (SaveFile.is_open()) {
        SaveFile >> Score;
        SaveFile >> Moves;
        for (int i = 0; i < MaxGridSize; i++) {
            for (int j = 0; j < MaxGridSize; j++) {
                SaveFile >> Game[i][j];
            }
        }
        SaveFile.close();
        cout << "Game loaded successfully.\n";
    }
    else {
        cout << "Unable to load the game.\n";
    }
}

int main() {
    Clock Timer;
    srand(time(0));

    int GridSize;
    bool Save;
    cout << "Enter the size of the game board (between 6 and 7): ";
    cin >> GridSize;
    if (GridSize < MinGridSize || GridSize > MaxGridSize) {
        cout << "Invalid input. Please enter a size between " << MinGridSize << " and " << MaxGridSize << "." << endl;
        return 1;//Exit with an error code
    }
    cout << "Do you want to start new game if yes PRESS 1 else 0: ";
    cin >> Save;

    RenderWindow window(VideoMode(1366, 768), "Candy Crush!", Style::Fullscreen);
    if (Save == 1) {
        //Initialize new game
        for (int i = 0; i < GridSize; i++) {
            for (int j = 0; j < GridSize; j++) {
                Game[i][j] = rand() % 5 + 1;
            }
        }
    }
    else if (Save == 0) {
        //Check saved game and load it
        ifstream checkSave("Candy Crush (Saved).txt");
        if (checkSave.is_open()) {
            checkSave.close();
            LoadGame();
        }
    }

    int selectedX = 0, selectedY = 0;
    CircleShape candy;
    RectangleShape background, SelectedCandy;
    SelectedCandy.setFillColor(Color::Cyan);
    SelectedCandy.setSize(Vector2f(100, 100));
    SelectedCandy.setPosition((1366 - GridSize * 100) / 2, (768 - GridSize * 100) / 2);
    background.setSize(Vector2f(1366, 768));
    candy.setRadius(50);
    Texture CANDY1, CANDY2, CANDY3, CANDY4, CANDY5, BACKGROUND1;
    BACKGROUND1.loadFromFile("Resources/Main menu.jpg");
    CANDY1.loadFromFile("Resources/number1.png");
    CANDY2.loadFromFile("Resources/number2.png");
    CANDY3.loadFromFile("Resources/number3.png");
    CANDY4.loadFromFile("Resources/number4.png");
    CANDY5.loadFromFile("Resources/number5.jpg");
    background.setTexture(&BACKGROUND1);

    //Add a "Save" button
    Font Font;
    Font.loadFromFile("Resources/arial.ttf");
    RectangleShape SaveButton(Vector2f(100, 40));
    SaveButton.setPosition(10, 130);
    SaveButton.setFillColor(Color::Green);
    Text SaveButtonText("Save", Font, 20);
    SaveButtonText.setPosition(20, 140);
    SaveButtonText.setFillColor(Color::Black);

    while (window.isOpen()) {
        Event Event1;
        window.clear();
        window.draw(background);

        Select(window, SelectedCandy, selectedX, selectedY, GridSize);//Candy selection based on mouse click
        window.draw(SelectedCandy);

        //Draw candies in grid
        for (int i = 0; i < GridSize; i++)
            for (int j = 0; j < GridSize; j++) {
                if (Game[i][j] == 1) { candy.setTexture(&CANDY1); }
                else if (Game[i][j] == 2) { candy.setTexture(&CANDY2); }
                else if (Game[i][j] == 3) { candy.setTexture(&CANDY3); }
                else if (Game[i][j] == 4) { candy.setTexture(&CANDY4); }
                else { candy.setTexture(&CANDY5); }
                candy.setPosition(i * 100 + ((1366 - GridSize * 100) / 2), j * 100 + ((768 - GridSize * 100) / 2));
                window.draw(candy);
            }

        CheckMatches(GridSize);//Check for matches and update score
        FillGrid(GridSize);//Fill empty spaces in grid

        // Display score
        Text ScoreText("Points: " + to_string(Score), Font, 20);
        ScoreText.setPosition(10, 10);
        // Display time
        Text TimerText("Time: " + to_string(Timer.getElapsedTime().asSeconds()) + "s", Font, 20);
        TimerText.setPosition(10, 70);

        //Penalizing player
        if (Timer.getElapsedTime().asSeconds() >= 10) {
            Score -= 10;
            Moves--;
            Timer.restart();
        }
        TimerText.setString("Time: " + to_string(10 - static_cast<int>(Timer.getElapsedTime().asSeconds())) + "s");
        window.draw(TimerText);

        Text MovesText("Moves Left: " + to_string(Moves), Font, 20);
        MovesText.setPosition(10, 40);
        window.draw(ScoreText);//Draw "Scores"
        window.draw(MovesText);//Draw "Moves"
        //Draw "Save"
        window.draw(SaveButton);
        window.draw(SaveButtonText);
        window.display();

        if (WinCheck()) {
            DeallocateGame(GridSize);
            return 0;
        }
        else if (FailCheck()) {
            DeallocateGame(GridSize);
            return 0;
        }

        while (window.pollEvent(Event1)) {
            if (Event1.type == Event::Closed) {
                window.close();
            }
            //Check if the mouse is clicked on the "Save" button
            else if (Event1.type == Event::MouseButtonPressed) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (SaveButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    SaveGame();
                }
            }
            else if (Event1.type == Event::KeyPressed) {
                if (Event1.key.code == Keyboard::Up) {
                    SwapCandies(selectedX, selectedY, 0, GridSize);
                    Timer.restart();
                    Moves--;
                }
                else if (Event1.key.code == Keyboard::Down) {
                    SwapCandies(selectedX, selectedY, 1, GridSize);
                    Timer.restart();
                    Moves--;
                }
                else if (Event1.key.code == Keyboard::Left) {
                    SwapCandies(selectedX, selectedY, 2, GridSize);
                    Timer.restart();
                    Moves--;
                }
                else if (Event1.key.code == Keyboard::Right) {
                    SwapCandies(selectedX, selectedY, 3, GridSize);
                    Timer.restart();
                    Moves--;
                }
            }
        }
    }

    return 0;
}