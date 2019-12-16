#include "Header.h"

/////////////////// auto generate
void generateBrick(std::vector<brick>& br, int col, int row)
{
	for (int i = 0; i < br.size(); i++)
	{
		if (br[i].Special != ' ')
		{
			sf::Vector2f vt;
			vt.x = WINDOW_WIDTH / 2 + i % col * 78 - 503;
			vt.y = WINDOW_HEIGHT / 2 + i / col * 35 - 290;
			br[i].setPossition(vt);
		}
		else
		{
			br[i].clear();
		}
	}
}

void arcadeMode(int switch_mode)
{
	sf::RenderWindow ArcadeWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arcade Mode", sf::Style::Close);
	ArcadeWindow.setFramerateLimit(60);


	sf::SoundBuffer buffer_paddle;
	if (!buffer_paddle.loadFromFile("audios/click.wav"))
	{
	}
	sf::Sound sound_paddle;
	sound_paddle.setBuffer(buffer_paddle);

	sf::SoundBuffer buffer_brick;
	if (!buffer_brick.loadFromFile("audios/click3.wav"))
	{

	}
	sf::Sound sound_brick;
	sound_brick.setBuffer(buffer_brick);
	
	//Tạo banh
	Ball ball(15);
	ball.setPosition(DEFAULT_BALL_POSITION);
	sf::Texture ballColor;
	ballColor.loadFromFile("images/ball.png");
	ballColor.setSmooth(true);
	ball.setTexture(ballColor);

	sf::Event event;

	//Tạo danh sách gạch
	std::vector<brick> br;
	int col = 0;
	int row = 0;

	//tạo paddle
	brick paddle({ PADDLE_WIDTH, PADDLE_HEIGHT });
	paddle.setPossition(DEFAULT_PADDLE_POSITION);
	sf::Texture paddleColor;
	paddleColor.loadFromFile("images/paddle.jpg");
	paddleColor.setSmooth(true);
	paddle.setTexture(paddleColor);

	//tạo biên an toàn
	brick safe_wall({ WINDOW_WIDTH - 110,BARRIER_WIDTH });
	safe_wall.setPossition({ 0,0 });
	safe_wall.setColor(SAFE_BARRIER_COLOR);
	bool safe_barrier = false;

	//tạo wall
	Barrier Wall;

	//tạo điểm
	int Score = 0;
	sf::Text textScore;
	sf::Font font;
	font.loadFromFile("fonts/INVASION2000.TTF");
	textScore.setFont(font);
	textScore.setCharacterSize(50);
	textScore.setPosition({ WINDOW_WIDTH / 2 - 180,0 });
	textScore.setFillColor(SCORE_COLOR);

	//thời gian xuất hiện thông tin effect
	sf::Clock info_time;

	//thông tin effect
	sf::Text effect_info;
	effect_info.setFont(font);
	effect_info.setCharacterSize(40);
	effect_info.setPosition({ WINDOW_WIDTH / 2 - 180,50 });
	effect_info.setFillColor(sf::Color::White);
	bool check_effect_info = false;

	//tốc độ ban đầu của ball
	float ballSpeed = DEFAULT_BALL_SPEED;

	//tốc độ ban đầu của paddle
	float padSpeed = DEFAULT_PADDLE_SPEED;


	/*
		Trạng thái game
		0: bình thường
		1: thua
		2: thắng
		3: next level
		Ban đầu status = 3 để load level
	*/
	int status = 3;
	int level;
	bool demo = false; //demo game
	if (switch_mode == 1)
	{
		level = 0; //level 0: chế độ ball speed
	}
	else if (switch_mode == 2)
	{
		level = 1; //level >= 1: chế độ level
	}
	else if (switch_mode == 0)
	{
		demo = true;
		switch_mode = 1;
		level = 0;
	}

	//thông tin level
	sf::Text level_info;
	level_info.setFont(font);
	level_info.setCharacterSize(50);
	level_info.setPosition({ 65,0 });
	level_info.setFillColor(SCORE_COLOR);
	
	
	//thời gian và trạng thái của gạch đặc biệt
	vector<sf::Clock> effect_time;
	vector<bool> effect_status;
	for (int i = 0; i < sizeof(SPECIALS); i++)
	{
		sf::Clock m_clock;
		bool effect = false;

		effect_time.push_back(m_clock);
		effect_status.push_back(effect);
	}

	// điểm tăng(giảm) khi có hiệu ứng đặc biệt
	float score_effect = 1;

	int paddleWidth = PADDLE_WIDTH; // trường hợp có hiệu ứng tăng kích thước paddle


	//pause màn hình trước khi vào game
	bool start = false;


	while (ArcadeWindow.isOpen())
	{
		ArcadeWindow.clear();
		////Close, Exit, Pause, Resume
		while (ArcadeWindow.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				ArcadeWindow.close();
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					ArcadeWindow.close();
					break;
				case sf::Keyboard::P:
					if (start == true)
					{
						while (ArcadeWindow.waitEvent(event)) {
							switch (event.type) {
							case sf::Event::Closed:
								ArcadeWindow.close();
							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
								ArcadeWindow.close();
							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
								break;
							}
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
								break;
							}
						}
					}
				}
			}
		}

		//load level khi trạng thái là 3
		if (status == 3 && switch_mode == 2)
		{
			if (br.empty() == false)
			{
				br.clear();
			}
			buildStage(level, br, col, row);
			level_info.setString("LEVEL " + to_string(level));
			status = 0; //trạng thái trở về 0 sau khi load level
		}
		else if (status == 3 && switch_mode == 1){
			if (br.empty() == false)	{
				br.clear();
			}
			buildStage(level, br, col, row);
			level_info.setString("SPEED MODE");
			level_info.setPosition({ 120,0 });
			textScore.setPosition({ WINDOW_WIDTH / 2 + 80,0 });
			status = 0;
		}

		static bool goingUp = true;
		static bool goingDown = false;
		static bool goingLeft = false;
		static bool goingRight = true;

		if (demo == true)	{
			if (paddle.getPosition().x + paddle.getSize().x/2 < ball.getPosition().x + ball.getRadius()
				&& paddle.getPosition().x < WINDOW_WIDTH - paddleWidth - 65)
			{
				paddle.move({ padSpeed, 0 });
			}
			if (paddle.getPosition().x + paddle.getSize().x / 2 > ball.getPosition().x + ball.getRadius()
				&& paddle.getPosition().x > 76)
			{
				paddle.move({ -padSpeed, 0 });
			}
		}
		else {
			//paddle move
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (paddle.getPosition().y > WINDOW_HEIGHT - 80)) {
				paddle.move({ 0, -padSpeed });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (paddle.getPosition().x < WINDOW_WIDTH - paddleWidth - 65)) {
				paddle.move({ padSpeed, 0 });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (paddle.getPosition().y < WINDOW_HEIGHT - 40)) {
				paddle.move({ 0, padSpeed });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (paddle.getPosition().x > 76)) {
				paddle.move({ -padSpeed, 0 });
			}
		}
		
		if (start == false && demo == false)
		{
			goingUp = true;
			goingDown = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				goingLeft = true;
				goingRight = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				goingLeft = false;
				goingRight = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				start = true;
			}
			ball.setPosition({ paddle.getPosition().x + paddle.getSize().x / 2 - ball.getRadius(), paddle.getPosition().y - 30 });

			ball.drawTo(ArcadeWindow);
			for (int i = 0; i < br.size(); i++) {
				if (br[i].Special != ' ')
				{
					br[i].drawTo(ArcadeWindow);
				}
			}
			ArcadeWindow.draw(level_info);
			ArcadeWindow.draw(effect_info);
			textScore.setString("SCORE: " + to_string(Score));
			ArcadeWindow.draw(textScore);
			Wall.drawTo(ArcadeWindow);
			paddle.drawTo(ArcadeWindow);
			ArcadeWindow.display();
			continue;
		}


		int i = 0;
		
		//kiểm tra va chạm gạch
		for (i; i < br.size(); i++)
		{
			if (ball.getPosition().y + ball.getRadius() * 2 > br[i].getPosition().y&& ball.getPosition().y < br[i].getPosition().y + br[i].getSize().y) {
				if (ball.getPosition().x + ball.getRadius() * 2 > br[i].getPosition().x && ball.getPosition().x < br[i].getPosition().x + br[i].getSize().x) {
					sound_brick.play();
					if (br[i].Special != '\0')// TH là gạch đặc biệt
					{
						handleSpecialBrick(br, i, col, row, effect_time, effect_status, score_effect, paddle, paddleWidth, effect_info, info_time, check_effect_info, safe_barrier, ballSpeed, padSpeed);
					}
					handleCollision(br, i, col, row, ball, goingUp, goingDown, goingLeft, goingRight, Score, score_effect, effect_time, effect_status, paddle, paddleWidth, effect_info, info_time, check_effect_info, safe_barrier, ballSpeed, padSpeed);
					break;

				}
			}
		}

		//kiểm tra thời gian hiệu ứng
		checkEffect(effect_time, effect_status, score_effect, paddle, paddleWidth, effect_info, info_time, check_effect_info, safe_barrier, ballSpeed, padSpeed);

		
		// paddle chạm banh
		if (paddle.isHitBall(ball)) {
			if (paddle.isHitSide(ball,false)){
			}
			else {
				if (goingUp == false)
				{
					sound_paddle.play();
				}

				if (switch_mode == 1)
				{
					if (ballSpeed < BALL_SPEED_MAX && goingUp == false)
					{
						ballSpeed += ballSpeed * 0.1;
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					goingLeft = true;
					goingRight = false;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					goingLeft = false;
					goingRight = true;
				}
				goingUp = true;
				goingDown = false;
			}
		}

		//kiểm tra biên chạm banh, nếu banh chạm biên dưới thì thua
		if (Wall.isHitBall(ball, goingUp, goingDown, goingLeft, goingRight) == false) 
		{
			status = 1;
		}

		// kiểm tra nếu còn gạch trên màn hình (trừ gạch vật cản và gạch đã phá)
		i = 0;
		for (i; i < br.size(); i++)
		{
			if (br[i].Special != ' ' && br[i].Special != 'o')
			{
				break;
			}
		}

		// nếu không còn gạch thì thắng
		if (i == br.size())
		{
			status = 2;
		}
		
		// banh di chuyển
		if (goingDown == true) {
			ball.move({ 0, ballSpeed });
		}
		if (goingUp == true) {
			ball.move({ 0, -ballSpeed });
		}
		if (goingLeft == true) {
			ball.move({ -ballSpeed, 0 });
		}
		if (goingRight == true) {
			ball.move({ ballSpeed, 0 });
		}
		// vẽ banh lên màn hình
		ball.drawTo(ArcadeWindow);
		for (int i = 0; i < br.size(); i++) {
			if (br[i].Special != ' ')
			{
				br[i].drawTo(ArcadeWindow);
			}
		}


		//kiểm tra chế độ biên dưới an toàn
		if (safe_barrier == true)
		{
			//tạo biên dưới an toàn
			safe_wall.setPossition({60, WINDOW_HEIGHT - 26});
			safe_wall.drawTo(ArcadeWindow);
			if (safe_wall.isHitBall(ball))
			{
				sound_paddle.play();
				goingUp = true;
				goingDown = false;
			}
		}
		else
		{

			safe_wall.setPossition({0,0});
		}

		// vẽ lên màn hình
		ArcadeWindow.draw(level_info);
		ArcadeWindow.draw(effect_info);
		textScore.setString("SCORE: " + to_string(Score));
		ArcadeWindow.draw(textScore);
		Wall.drawTo(ArcadeWindow);
		paddle.drawTo(ArcadeWindow);
		ArcadeWindow.display();

		// khi trạng thái khác normal thì vẽ bảng điểm
		if (status != 0)
		{
			if (demo == true){ 
				sf::Text demo_text;
				demo_text.setString("END DEMO");
				demo_text.setFont(font);
				demo_text.setCharacterSize(50);
				demo_text.setPosition({ WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT/2 + 100 });
				demo_text.setFillColor(sf::Color::Green);
				ArcadeWindow.draw(demo_text);
				ArcadeWindow.display();
				while (ArcadeWindow.waitEvent(event)) {
					switch (event.type) {
					case sf::Event::Closed:
						ArcadeWindow.close();
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
						|| sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						ArcadeWindow.close();
					}
				}
			}
			ArcadeWindow.clear();

			sf::Text Stat;
			Stat.setCharacterSize(100);
			Stat.setFont(font);
			Stat.setPosition({ WINDOW_WIDTH / 2 - 250,0 });
			if (status == 1)
			{
				Stat.setString("YOU LOSE");
				Stat.setFillColor(LOSE_COLOR);
			}
			else if (status == 2 && (level == 3 || level == 0))
			{
				Stat.setString("YOU WIN");
				Stat.setFillColor(WIN_COLOR);
			}
			else if (status == 2 && level < 3 && level > 0)
			{
				Stat.setString("HIGH SCORE");
				Stat.setFillColor(HIGHSCORE_COLOR);
			}
			ArcadeWindow.draw(Stat);

			HighScore high_score;
			// load và ghi điểm vào file
			if (switch_mode == 1) // chế độ speed mode lưu thẳng điểm
			{
				high_score.loadHighScores("Data/highscore_speed_mode.txt");
				high_score.saveHighScore(Score);
				high_score.writeHighScores("Data/highscore_speed_mode.txt");
			}
			else if (switch_mode == 2)
			{
				high_score.loadHighScores("Data/highscore_level_mode.txt");
				high_score.saveHighScore(Score);
			}


			vector<string> ScoreBoard = high_score.getHighScore();

			sf::Text Rank;
	
			Rank.setString(to_string(Score));
			Rank.setFont(font);
			Rank.setCharacterSize(50);

			int checkPlayerRank = 0;
			string lineRank;
			//Vẽ bảng điểm

			bool HI = false;
			sf::Vector2f vt;

			for (int i = 0; i < ScoreBoard.size(); i++)
			{
				switch (i)
				{
				case 0:
					lineRank = "1ST RANK              " + ScoreBoard[i];
					Rank.setString(lineRank);
					Rank.setFillColor(RANK1_COLOR);
					break;
				case 1:
					lineRank = "2ND RANK             " + ScoreBoard[i];
					Rank.setString(lineRank);
					Rank.setFillColor(RANK2_COLOR);
					break;
				case 2: 
					lineRank = "3RD RANK             " + ScoreBoard[i];
					Rank.setString(lineRank);
					Rank.setFillColor(RANK3_COLOR);
					break;
				case 9:
					lineRank = "10TH RANK            " + ScoreBoard[i];
					Rank.setString(lineRank);
					Rank.setFillColor(OTHER_RANK_COLOR);
					break;
				default:
					lineRank = to_string(i + 1) + "TH RANK             " + ScoreBoard[i];
					Rank.setString(lineRank);
					Rank.setFillColor(OTHER_RANK_COLOR);
					break;
				}

				//Cài đặt vị trí điểm
				vt.x = WINDOW_WIDTH / 2 - 320;
				vt.y = WINDOW_HEIGHT / 2 - 300 + i * 60;
				if (Score == stoi(ScoreBoard[i]) && checkPlayerRank == 0)
				{
					Rank.setString("YOU > " + lineRank);
					vt.x = WINDOW_WIDTH / 2 - 500;
					checkPlayerRank++;
					HI = true;
				}
				Rank.setPosition(vt);
				ArcadeWindow.draw(Rank);
			}
			// Nếu điểm người chơi không nằm trong danh sách thì thông báo điểm người chơi
			if (HI == false)
			{
				Rank.setString("YOU:                    " + to_string(Score));
				vt.x = WINDOW_WIDTH / 2 - 320;
				vt.y = WINDOW_HEIGHT / 2 - 300 + ScoreBoard.size() * 60;
				Rank.setPosition(vt);
				Rank.setFillColor(sf::Color::Magenta);
				ArcadeWindow.draw(Rank);

			}

			ArcadeWindow.display();
			// dừng màn hình chờ lệnh
			while (ArcadeWindow.waitEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					high_score.writeHighScores("Data/highscore_level_mode.txt");
					ArcadeWindow.close();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					high_score.writeHighScores("Data/highscore_level_mode.txt");
					ArcadeWindow.close();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					if (level < 3 && switch_mode == 2 && status == 2)// TH level mode, khi clear level hiện tại và chưa đạt level max thì tăng level và giữ điểm hiện tại
					{
						level++; 
						status = 3;
						start = false;
						UpdateGame(paddle, ball, br, effect_time, effect_status, score_effect, paddleWidth, effect_info, info_time, check_effect_info, safe_barrier, ballSpeed, padSpeed);
					}
					else // các TH khác thì reset game
					{
						status = 3;
						Score = 0;
						start = false;
						UpdateGame(paddle, ball, br, effect_time, effect_status, score_effect, paddleWidth, effect_info, info_time, check_effect_info, safe_barrier, ballSpeed, padSpeed);
						
						if (switch_mode == 2)//nếu ở chế độ level mode thì reset level
						{
							level = 1;
							high_score.writeHighScores("Data/highscore_level_mode.txt");
						}
					}
					break;
				}
				
			}
			
		}
		
		
	}

}

//////////////////////////////


void handleSpecialBrick(vector<brick>& br, int pos, int col, int row, vector<sf::Clock>& effect_time, vector<bool>& effect_status, float& score_effect, brick& paddle, int& paddle_Width, sf::Text& effect_info, sf::Clock& info_time, bool& check_effect_info, bool& safe_barrier, float& ball_speed, float& paddle_speed)
{
	string effect = "";


	sf::Texture block_color;

	int i, j;

	switch (br[pos].Special)
	{
	case 'p': //điểm tăng
		//bắt đầu thời gian effect
		effect_time[0].restart();
		effect_status[0] = true;

		//cài đặt effect
		score_effect = 1.5;

		//cài đặt thông báo effect
		effect = "SCORE UP";
		effect_info.setFillColor(GOOD_EFFECT_COLOR);

		//cài đặt thời gian hiển thị thông báo effect
		info_time.restart();
		check_effect_info = true;
		break;

	case 'm'://điểm giảm
		//////
		effect_time[1].restart();
		effect_status[1] = true;
		
		//////
		score_effect = 0.5;


		//////
		effect = "SCORE DOWN";
		effect_info.setFillColor(BAD_EFFECT_COLOR);

		///////
		info_time.restart();
		check_effect_info = true;
		break;

	case 'l':// paddle dài
		//////
		effect_time[2].restart();
		effect_status[2] = true;

		/////
		paddle_Width = PADDLE_WIDTH + 40;
		paddle.setSize({ PADDLE_WIDTH + 40,PADDLE_HEIGHT });

		//////
		effect = "LONG PADDLE";
		effect_info.setFillColor(GOOD_EFFECT_COLOR);

		//
		info_time.restart();
		check_effect_info = true;
		break;

	case 'i':// paddle ngắn
		//////
		effect_time[3].restart();
		effect_status[3] = true;

		/////
		paddle_Width = PADDLE_WIDTH - 20;
		paddle.setSize({ PADDLE_WIDTH - 20,PADDLE_HEIGHT });

		//////
		effect = "SHORT PADDLE";
		effect_info.setFillColor(BAD_EFFECT_COLOR);

		//
		info_time.restart();
		check_effect_info = true;
		break;

	case 'a'://  tốc độ paddle tăng
		//////
		effect_time[4].restart();
		effect_status[4] = true;

		/////
		paddle_speed = 11;

		//////
		effect = "PADDLE SPEED UP";
		effect_info.setFillColor(GOOD_EFFECT_COLOR);

		//
		info_time.restart();
		check_effect_info = true;
		break;

	case 'b'://  tốc độ paddle giảm
		//////
		effect_time[5].restart();
		effect_status[5] = true;

		/////
		paddle_speed = 5.5;

		//////
		effect = "PADDLE SPEED DOWN";
		effect_info.setFillColor(BAD_EFFECT_COLOR);

		//
		info_time.restart();
		check_effect_info = true;
		break;

	case 's':
		//////
		effect_time[6].restart();
		effect_status[6] = true;

		/////
		safe_barrier = true;

		//////
		effect = "SAFE BARRIER";
		effect_info.setFillColor(GOOD_EFFECT_COLOR);

		//cai dat thoi gian hien thong bao effect
		info_time.restart();
		check_effect_info = true;
		break;

	case 'o':
		//cai dat effect
		block_color.loadFromFile("images/block.jpg");
		block_color.setSmooth(true);
		br[pos].setTexture(block_color);

		break;
	}
	
	effect_info.setString(effect);
	effect_info.setPosition({ WINDOW_WIDTH / 2 - 5 * sizeof(effect) - 20,60 });
}

void checkEffect(vector<sf::Clock>& effect_time, vector<bool>& effect_status, float& score_effect, brick& paddle, int& paddle_Width, sf::Text& effect_info, sf::Clock& info_time, bool& check_effect_info, bool& safe_barrier, float& ball_speed, float& paddle_speed)
{
	for (int i = 0; i < effect_status.size(); i++)
	{	
		// xoá hiệu ứng nếu thời gian quá 10s
		if (effect_time[i].getElapsedTime().asSeconds() > 10 && effect_status[i] == true)
		{
			effect_time[i].restart();
			effect_status[i] = false;
			switch (i)
			{
			case 0://điểm trở về bình thường
				if (effect_status[1] == false)
				{
					score_effect = 1;
				}
				break;
			case 1:
				if (effect_status[0] == false)
				{
					score_effect = 1;
				}
				break;
			case 2://độ dài paddle trở về bình thường
				if (effect_status[3] == false)//nếu hiệu ứng paddle không tồn tại thì xóa hiệu ứng này (tránh TH xung đột hiệu ứng)
				{
					paddle_Width = PADDLE_WIDTH;
					paddle.setSize({ PADDLE_WIDTH,PADDLE_HEIGHT });
				}
				break;
			case 3://///
				if (effect_status[2] == false)//tránh TH xung đột hiệu ứng
				{
					paddle_Width = PADDLE_WIDTH;
					paddle.setSize({ PADDLE_WIDTH,PADDLE_HEIGHT });
				}
				break;
			case 4:
				if (effect_status[5] == false)//tránh TH xung đột hiệu ứng
				{
					paddle_speed = DEFAULT_PADDLE_SPEED;
				}
				break;
			case 5:
				if (effect_status[4] == false)//tránh TH xung đột hiệu ứng
				{
					paddle_speed = DEFAULT_PADDLE_SPEED;
				}
				break;
			case 6:
				safe_barrier = false;
				break;
			}
		}
		if (info_time.getElapsedTime().asSeconds() > 10 && check_effect_info == true)
		{
			info_time.restart();
			effect_info.setString("");
			check_effect_info = false;
		}
	}
}

void handleCollision(vector<brick>& br, int pos, int col, int row, Ball ball, bool& goingUp, bool& goingDown, bool& goingLeft, bool& goingRight, int& Score, float& score_effect, vector<sf::Clock>& effect_time, vector<bool>& effect_status, brick& paddle, int& paddleWidth, sf::Text& effect_info, sf::Clock& info_time, bool& check_effect_info, bool& safe_barrier, float& ball_speed, float& paddle_speed)
{
	int i;

	i = pos + 1;
	if (i <  br.size() && br[i].isHitBall(ball))
	{
		if (br[i].Special != ' ')
		{
			handleSpecialBrick(br, i, col, row, effect_time, effect_status, score_effect, paddle, paddleWidth, effect_info, info_time, check_effect_info, safe_barrier, ball_speed, paddle_speed);
		}

		if (br[i].Special != 'o')
		{
			br[i].clear();
			Score += 1000 * score_effect;
		}
		goingDown = !goingDown;
		goingUp = !goingUp;
		if (br[pos].Special != 'o')
		{
			br[pos].clear();
			Score += 1000 * score_effect;
		}
		return;
	}

	i = pos + col;
	if (i < br.size() && br[i].isHitBall(ball))
	{
		if (br[i].Special != '\0')
		{
			handleSpecialBrick(br, i, col, row, effect_time, effect_status, score_effect, paddle, paddleWidth, effect_info, info_time, check_effect_info, safe_barrier, ball_speed, paddle_speed);
		}

		if (br[i].Special != 'o')
		{
			br[i].clear();
			Score += 1000 * score_effect;
		}
		goingLeft = !goingLeft;
		goingRight = !goingRight;
		if (br[pos].Special != 'o')
		{
			br[pos].clear();
			Score += 1000 * score_effect;
		}
		return;
	}

	if (br[pos].isHitSide(ball, goingUp))
	{
		goingLeft = !goingLeft;
		goingRight = !goingRight;
	}
	else
	{
		goingDown = !goingDown;
		goingUp = !goingUp;
	}
	if (br[pos].Special != 'o')
	{
		br[pos].clear();
		Score += 1000 * score_effect;
	}
}

void buildStage(int level, vector<brick>& br, int& col, int& row)
{
	buildingStage Stage;

	//load gach tu file
	br = Stage.getBrick("level" + to_string(level) + ".txt");
	col = Stage.getNumOfCol();
	row = Stage.getNumOfRow();
	//sap xep gach
	generateBrick(br, col, row);

	//load mau gach tu file
	vector<sf::Texture> brickcolor;
	for (int i = 1; i <= 9; i++)// co 9 mau gach
	{
		string name = "images/" + to_string(i) + ".jpg";
		sf::Texture color;
		color.loadFromFile(name);
		color.setSmooth(true);
		brickcolor.push_back(color);
	}

	// cai dat mau cho gach
	int countBrick = 0;
	for (int i = 0; i < row; i++)
	{
		int countColor = i % 9;
		for (int j = 0; j < col; j++)
		{
			br[countBrick].setTexture(brickcolor[countColor]);
			countColor++;
			countBrick++;
			if (countColor == 9)
			{
				countColor = 0;
			}
		}
	}
}

void UpdateGame(brick& paddle, Ball& ball, vector<brick>& br, vector<sf::Clock>& effect_time, vector<bool>& effect_status, float& score_effect, int& paddle_Width, sf::Text& effect_info, sf::Clock& info_time, bool& check_effect_info, bool& safe_barrier, float& ball_speed, float& paddle_speed)
{
	paddle.setPossition(DEFAULT_PADDLE_POSITION);
	paddle.setSize({ PADDLE_WIDTH,PADDLE_HEIGHT });
	ball.setPosition(DEFAULT_BALL_POSITION);
	
	if (br.empty() == false)
	{
		br.clear();
	}

	for (int i = 0; i < effect_time.size(); i++)
	{
		effect_time[i].restart();
		effect_status[i] = false;
	}

	score_effect = 1;

	paddle_Width = PADDLE_WIDTH;

	effect_info.setString("");

	info_time.restart();

	check_effect_info = false;

	safe_barrier = false;

	ball_speed = DEFAULT_BALL_SPEED;

	paddle_speed = DEFAULT_PADDLE_SPEED;
}