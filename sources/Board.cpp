#include <SFML/Graphics.hpp>
#include "Board.h"
#include <iostream>

Board::Board(int boardSize, sf::Vector2f cooards, int difficulty, sf::Font& font) {

    std::cout << "Difficulty Set: " << difficulty << "\n";
    std::cout << "Board Size: (" << boardSize << ")\n";

    /* initialize random seed: */
    srand (time(NULL));

    this->boardSize = boardSize;    
    int potential;

    for( int row = 1 ; row <= boardSize ; row++ ) {

        for( int col = 1 ; col <= boardSize ; col++ ){

            potential = rand() % boardSize + 1;
    
            int count = 0;

            while(count < 200 && !(isNumberValid(col, row, potential))){

                potential = rand() % boardSize + 1;
                count++;
                if(count == 200) potential = 10;
                //std::cout << "isNumberValid col(" << col << ") row(" << row << ") number: " << potential << "\n";
            }

            sudokuNumbers[col][row] = potential;

            std::cout << "isNumberValid: YES - " << potential << " is sudokuNumber[" << col << "][" << row << "]" << "\n";

            squares.push_back(Square(
                sf::Color(0,0,0),
                sf::Vector2f(45.0f, 45.0f),
                sf::Vector2f(50.0f * col, 50.0f * row),
                sf::Vector2u(col,row),
                font,
                33,
                sudokuNumbers[col][row],
                sudokuNumbers[col][row],
                true
            ));
        }
    }
}

Board::~Board()
{
}

void Board::draw(sf::RenderWindow& window){
    
    for(Square& aSquare : squares){

        aSquare.Draw(window);
        aSquare.Update(resizeMultiplier);
    }
}

void Board::updateSizeMultiplier( float change ) { resizeMultiplier = change; }

void Board::CheckPositionOnBoard(sf::Vector2i mousePos){

    for(Square& aSquare : squares){

        if(aSquare.CheckButton(mousePos))

            aSquare.setColor(sf::Color(250,243,62));

        else aSquare.setColor(sf::Color(151,239,223));
    }
}

void Board::ErrorCheck(){

    for(Square& aSquare : squares){

        if(aSquare.getTrueValue() == aSquare.getDisplayValue())

            aSquare.setColor(sf::Color(58,110,54));
    }
}

bool Board::ClickCheck(sf::Vector2i mousePos){

    for(Square& aSquare : squares){

        if(aSquare.CheckButton(mousePos)){

            std::cout << "Return Value: " << aSquare.getDisplayValue() << "\n";
            //screen = CHOICE_SCREEN;

            //aSquare.setColor(sf::Color::Red);

            clickedSquare = &aSquare;

            return true;
        }
    }
    return false;
}

bool Board::isNumberValid(int col, int row, int potential){

    //std::cout << "Checking origin point: " << origin.x << "," << origin.y << "\n";

    for(int i = 1 ; i <= 9 ; i++ ){

        if(sudokuNumbers[col][i] == potential){
            
            std::cout << "invalid (" << col << ")(" << row << ")" << "\n";
            std::cout << "sudokuNumbers[" << col << "][" << i << "] is equal to potential: " << potential << "\n";
            return false;
        }

        if(sudokuNumbers[i][row] == potential){

            std::cout << "invalid (" << col << ")(" << row << ")" << "\n";
            std::cout << "sudokuNumbers[" << i << "][" << row << "] is equal to potential: " << potential << "\n";
            return false;
        }
    }

    int minX, minY;
    int maxX = col, maxY = row;

    while(maxX % 3) maxX++;
    while(maxY % 3) maxY++;
    minX = maxX - 2;
    minY = maxY - 2;

    for(int i = minY ; i <= maxY ; i++ ){

        for(int j = minX ; j <= maxX ; j++ ){

            if(sudokuNumbers[j][i] == potential){

                std::cout << "invalid (" << col << ")(" << row << ")" << "\n";
                std::cout << "square error on: mixX - " << minX << ", minY - " << minY << "\n";
                std::cout << "sudokuNumbers[" << j << "][" << i << "] == " << potential << "\n";
                return false;
            }
        }
    }
    return true;
}

Square& Board::getClickedSquare() {
    
    return *clickedSquare;
    
}