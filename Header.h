#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "ball.h"
#include "player.h"
#include "brick.h"
#include <vector>
#include "DesignArcade.h"
#include "Barrier.h"
#include "buildingStage.h"
#include "HighScore.h"

void generateBrick(std::vector<brick>& br, int, int);
void arcadeMode(int switch_mode);
void handleSpecialBrick(vector<brick>& br, int pos, int col, int row, vector<sf::Clock>& effect_time, vector<bool>& effect_status, float& score_effect, brick& paddle, int& paddle_Width, sf::Text& effect_info, sf::Clock& info_time, bool& check_effect_info, bool& safe_barrier, float& ball_speed, float& paddle_speed);
void checkEffect(vector<sf::Clock>& effect_time, vector<bool>& effect_status, float& score_effect, brick& paddle, int& paddle_Width, sf::Text& effect_info, sf::Clock& info_time, bool& check_effect_info, bool& safe_barrier, float& ball_speed, float& paddle_speed);
void handleCollision(vector<brick>& br, int pos, int col, int row, Ball ball, bool& goingUp, bool& goingDown, bool& goingLeft, bool& goingRight, int& Score, float& score_effect, vector<sf::Clock>& effect_time, vector<bool>& effect_status, brick& paddle, int& paddleWidth, sf::Text& effect_info, sf::Clock& info_time, bool& check_effect_info, bool& safe_barrier, float& ball_speed, float& paddle_speed);
void buildStage(int level, vector<brick>& br, int& col, int& row);
void UpdateGame(brick& paddle, Ball& ball, vector<brick>& br, vector<sf::Clock>& effect_time, vector<bool>& effect_status, float& score_effect, int& paddle_Width, sf::Text& effect_info, sf::Clock& info_time, bool& check_effect_info, bool& safe_barrier, float& ball_speed, float& paddle_speed);