#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <array>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <string>
#include "Icon.h"

#define column 240
#define row 124
#define size_of_box 8

void next_gen(bool arr[row][column], bool pre_array[row][column], int start, int gap)
{
    int end = start + gap;

    for (int rows = 0; rows < row; rows++) {
        for (int columns = 0; columns < column; columns++) {
            int live = 0;
            
            if (rows == 0 && columns == 0) {
                live = pre_array[rows + 1][columns] +
                       pre_array[row  - 1][columns] +
                       pre_array[rows + 1][columns + 1] +
                       pre_array[rows + 1][column - 1] +
                       pre_array[row  - 1][columns + 1] +
                       pre_array[row  - 1][column - 1] +
                       pre_array[rows    ][columns + 1] +
                       pre_array[rows    ][column - 1];
            }
            else if (rows == 0 && columns == column - 1) {
                live =  pre_array[rows + 1][columns] +
                        pre_array[row  - 1][columns] +
                        pre_array[rows + 1][0] +
                        pre_array[rows + 1][columns - 1] +
                        pre_array[row  - 1][0] +
                        pre_array[row  - 1][columns - 1] +
                        pre_array[rows    ][0] +
                        pre_array[rows    ][columns - 1];
            }
            else if (rows == row - 1 && columns == 0) {
                live =  pre_array[0       ][columns] +
                        pre_array[rows - 1][columns] +
                        pre_array[0       ][columns + 1] +
                        pre_array[0       ][column - 1] +
                        pre_array[rows - 1][columns + 1] +
                        pre_array[rows - 1][column - 1] +
                        pre_array[rows    ][columns + 1] +
                        pre_array[rows    ][column - 1];
            }
            else if (rows == row - 1 && columns == column - 1) {
                live =  pre_array[0       ][columns] +
                        pre_array[rows - 1][columns] +
                        pre_array[0       ][0] +
                        pre_array[0       ][columns - 1] +
                        pre_array[rows - 1][0] +
                        pre_array[rows - 1][columns - 1] +
                        pre_array[rows    ][0] +
                        pre_array[rows    ][columns - 1];
            }
            else if (columns == 0) {
                live = pre_array[rows + 1][columns] +
                       pre_array[rows - 1][columns] +
                       pre_array[rows + 1][columns + 1] +
                       pre_array[rows + 1][column - 1] +
                       pre_array[rows - 1][columns + 1] +
                       pre_array[rows - 1][column - 1] +
                       pre_array[rows    ][columns + 1] +
                       pre_array[rows    ][column - 1];
            }
            else if (columns == column - 1) {
                live = pre_array[rows + 1][columns] +
                       pre_array[rows - 1][columns] +
                       pre_array[rows + 1][0] +
                       pre_array[rows + 1][columns - 1] +
                       pre_array[rows - 1][0] +
                       pre_array[rows - 1][columns - 1] +
                       pre_array[rows    ][0] +
                       pre_array[rows    ][columns - 1];
            }
            else if (rows == 0) {
                live = pre_array[rows + 1][columns    ] +
                       pre_array[row  - 1][columns    ] +
                       pre_array[rows + 1][columns + 1] +
                       pre_array[rows + 1][columns - 1] +
                       pre_array[row  - 1][columns + 1] +
                       pre_array[row  - 1][columns - 1] +
                       pre_array[rows    ][columns + 1] +
                       pre_array[rows    ][columns - 1];

            }            
            else if (rows == row - 1) {
                live =  pre_array[0       ][columns    ] +
                        pre_array[rows - 1][columns    ] +
                        pre_array[0       ][columns + 1] +
                        pre_array[0       ][columns - 1] +
                        pre_array[rows - 1][columns + 1] +
                        pre_array[rows - 1][columns - 1] +
                        pre_array[rows    ][columns + 1] +
                        pre_array[rows    ][columns - 1];
            }
            else {
                live = pre_array[rows + 1][columns] +
                       pre_array[rows - 1][columns] +
                       pre_array[rows + 1][columns + 1] +
                       pre_array[rows + 1][columns - 1] +
                       pre_array[rows - 1][columns + 1] +
                       pre_array[rows - 1][columns - 1] +
                       pre_array[rows    ][columns + 1] +
                       pre_array[rows    ][columns - 1];
            }

            if (pre_array[rows][columns] == true && live > 3) {
                arr[rows][columns] = false;
            }
            else if (pre_array[rows][columns] == true && live < 2) {
                arr[rows][columns] = false;
            }
            else if (pre_array[rows][columns] == false && live == 3) {
                arr[rows][columns] = true;
            }
        }
    }
    return;
}

void cycle_colors(float color[3], int& cycle, float& cycle_speed) 
{
    if (cycle == 0) {
        if (color[0] <= 100.f) {
            cycle = 1;
            color[0] = 100;
            color[1] = 255;
        }
        else {
            if (color[0] - cycle_speed < 100) {
                color[0] = 100;
            }
            else {
                color[0] -= cycle_speed;
            }
            if (color[1] + cycle_speed > 255) {
                color[1] = 255;
            }
            else {
                color[1] += cycle_speed;
            }
        }
    }
    else if (cycle == 1) { 
        if (color[1] <= 100.f) {
            cycle = 2;
            color[1] = 100;
            color[2] = 255;
        }
        else {
            if (color[1] - cycle_speed < 100) {
                color[1] = 100;
            }
            else {
                color[1] -= cycle_speed;
            }
            if (color[2] + cycle_speed > 255) {
                color[2] = 255;
            }
            else {
                color[2] += cycle_speed;
            }
        }
    }
    else if (cycle == 2) {
        if (color[2] <= 100.f) {
            cycle = 0;
            color[2] = 100;
            color[0] = 255;
        }
        else {
            if (color[2] - cycle_speed < 100) {
                color[2] = 100;
            }
            else {
                color[2] -= cycle_speed;
            }
            if (color[0] + cycle_speed > 255) {
                color[0] = 255;
            }
            else {
                color[0] += cycle_speed;
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    const int boxsize = size_of_box;
    const float radius = boxsize / 2 - 1;
    const int number_of_boxes_columns = column;
    const int number_of_boxes_rows = row;
    const int width = boxsize * number_of_boxes_columns;
    const int height = boxsize * number_of_boxes_rows;
    const int gap = 1;
    const int thread_gap = row / 4;
    const int thread_row[4] = { 0, thread_gap, thread_gap * 2, thread_gap * 3 };
    bool pre_array[row][column] = { false };
    bool color_cycle = true;
    int iterations = 0;
    float color[] = {100, 100, 255};
    int cycle = 2;
    float brightness = 0.3f;
    float cycle_speed = 1.f;
    float cell_color[7][3] = { {245 * 0.3, 245, 245},
                           {245, 245 * 0.3, 245},
                           {245, 245, 245 * 0.3},
                           {245 * 0.3, 245 * 0.3, 245},
                           {245 * 0.3, 245, 245 * 0.3},
                           {245, 245 * 0.3, 245 * 0.3},
                           {245, 245, 245} };
    int cell_color_selection = 6;

    std::cout << "Welcome to Game of Life!" << std::endl << std::endl
    << "This is not really a game but a simulation based on Conway's Game of Life" << std::endl << std::endl
    << "Press C to toggle color cycling ON/OFF." << std::endl
    << "Press LEFT/RIGHT arrow keys to increase/decrease color cycle speed." << std::endl
    << "Press X to reset color cycle speed." << std::endl
    << "Press Z to change cell color." << std::endl
    << "Press UP/DOWN arrow keys to increase/decrease brightness." << std::endl
    << "Press any other key to randomize board." << std::endl << std::endl
    << "Epilepsy warning for high color cycle speed." << std::endl << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    bool board[number_of_boxes_rows][number_of_boxes_columns] = {false};

    for (int rows = 0; rows < row; rows++) {
        for (int columns = 0; columns < column; columns++) {
            bool random_number = round((float) rand() / RAND_MAX);
            board[rows][columns] = random_number;
        }
    }

    //board[25][25] = true;
    //board[25][26] = true;
    //board[26][24] = true;
    //board[26][25] = true;
    //board[27][25] = true;

    //board[65][65] = true;
    //board[65][66] = true;
    //board[66][64] = true;
    //board[66][65] = true;
    //board[67][65] = true;

    //board[45][85] = true;
    //board[45][86] = true;
    //board[46][84] = true;
    //board[46][85] = true;
    //board[47][85] = true;

    //board[75][155] = true;
    //board[75][156] = true;
    //board[76][154] = true;
    //board[76][155] = true;
    //board[77][155] = true;
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(width, height), "Game of Life");

    window.sf::RenderWindow::setIcon(life_icon.width, life_icon.height, life_icon.pixel_data);
    window.setPosition(sf::Vector2i(-8, 0));
    auto box = sf::CircleShape(radius);
    box.setFillColor(sf::Color::Blue);
    box.setPointCount(20);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::C)
                {
                    if (color_cycle == false) {
                        color_cycle = true;
                        std::cout << "Color cycling ON" << std::endl;
                    }
                    else if (color_cycle == true) {
                        color_cycle = false;
                        std::cout << "Color cycling OFF" << std::endl;
                    }
                }
                else if(event.key.code == sf::Keyboard::Up)
                {
                    brightness += 0.05f;
                    if (brightness > 1.f) {
                        brightness = 1.f;
                    }
                }
                else if (event.key.code == sf::Keyboard::X)
                {
                    cycle_speed = 1;
                    std::cout << "Color cycle speed is " << cycle_speed << std::endl;
                }
                else if (event.key.code == sf::Keyboard::Z)
                {
                    cell_color_selection += 1;
                    if (cell_color_selection + 1 > 7) {
                        cell_color_selection = 0;
                    }
                    std::cout << "Cell color changed in a way I cant describe." << cycle_speed << std::endl;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    brightness -= 0.05f;
                    if (brightness < 0.f) {
                        brightness = 0.f;
                    }
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    if (cycle_speed - 1.f >= 0) {
                        cycle_speed -= 1.f;
                    }
                    std::cout << "Color cycle speed is " << cycle_speed << std::endl;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    cycle_speed += 1.f;
                    std::cout << "Color cycle speed is " << cycle_speed << std::endl;
                }
                //else if (event.key.code == sf::Keyboard::F11)
                //{
                //    
                //    toggle fullscreen
                //}
                else {
                    for (int rows = 0; rows < row; rows++) {
                        for (int columns = 0; columns < column; columns++) {
                            bool random_number = round((float)rand() / RAND_MAX);
                            board[rows][columns] = random_number;
                        }
                    }
                }
            }
        }

        //window.clear();

        for (int rows = 0; rows < row; rows++) {
            for (int columns = 0; columns < column; columns++) {
                pre_array[rows][columns] = board[rows][columns];
            }
        }

        std::thread next1(next_gen, board, pre_array, thread_row[0], thread_gap);
        std::thread next2(next_gen, board, pre_array, thread_row[1], thread_gap);
        std::thread next3(next_gen, board, pre_array, thread_row[2], thread_gap);
        std::thread next4(next_gen, board, pre_array, thread_row[3], thread_gap);

        next1.join();
        next2.join();
        next3.join();
        next4.join();
        //next_gen(board, pre_array, 0, row);

        if (color_cycle == true) {
            cycle_colors(color, cycle, cycle_speed);
        }

        for (int rows = 0; rows < number_of_boxes_rows; rows++) {
            for (int columns = 0; columns < number_of_boxes_columns; columns++) {
                int posx = columns * boxsize;
                int posy = rows * boxsize;
                if (board[rows][columns] == true) {
                    box.setFillColor(sf::Color::Color(cell_color[cell_color_selection][0],
                                                      cell_color[cell_color_selection][1], 
                                                      cell_color[cell_color_selection][2]));
                    box.setPosition(posx, posy);
                }
                else {
                    box.setPosition(posx, posy);
                    box.setFillColor(sf::Color::Color(color[0] * brightness, 
                                                      abs(color[1] * (brightness - 0.1f)),
                                                      color[2] * brightness));
                }
                window.draw(box);
            }
        }

        iterations++;
        if (iterations%100 == 0) {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> time_taken = end - start;
            std::cout << iterations <<" cycles have passed and wasted " << time_taken.count() << "s of your life." << std::endl;
        }
        window.display();
    }
    return 0;
}