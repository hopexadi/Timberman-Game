#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;


void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
enum class side{ LEFT, RIGHT, NONE};
side branchPositions[NUM_BRANCHES];


int main()
{
	VideoMode vm(960, 540);
	RenderWindow window(vm, "Timber!!!");
	View view(FloatRect(0, 0, 1920, 1080));
    window.setView(view);
	Texture textureBackground;
	textureBackground.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/graphics/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);


	Texture textureTree;
	textureTree.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	Texture textureBee;
	textureBee.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);


	bool beeActive = false;


	float beeSpeed = 0.0f;



	Texture textureCloud;
	textureCloud.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/graphics/cloud.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 150);
	spriteCloud3.setPosition(0, 300);


	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;


	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;
	

	Clock clock;


	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
	

	bool paused = true;


	int score = 0;
	sf::Text messageText;
	sf::Text scoreText; 


	sf::Font font;
	font.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/fonts/KOMIKAP_.ttf");
	

	messageText.setFont(font);
	scoreText.setFont(font);
	

	messageText.setString("Press Enter to start");
	scoreText.setString("Score = 0");
	

	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);


	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);


	scoreText.setPosition(20, 20);
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);	
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	

	Texture textureBranch;
	textureBranch.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/graphics/branch.png");
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}
	

	Texture texturePlayer;
	texturePlayer.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);


	side playerSide = side::LEFT;


	Texture textureRIP;
	textureRIP.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);


	Texture textureAxe;
	textureAxe.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);
	

	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;
	
	
	Texture textureLog;
	textureLog.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);
	
	

	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;



	bool acceptInput = false;

	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	SoundBuffer outBuffer;
	outBuffer.loadFromFile("C:/Users/ADITYA/Desktop/Projects/Timber_prereq/sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(outBuffer);
	
	while (window.isOpen()) {	
			
			Event event;
			while (window.pollEvent(event)) {

			if (event.type == Event::KeyReleased && !paused) {
				acceptInput = true;

				
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}
		
		
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
			}
			
			
		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			paused = false;	

			score = 0;
			timeRemaining = 6;

			
			for (int i = 1; i < NUM_BRANCHES; i++) {
				branchPositions[i] = side::NONE;
			}

			
			spriteRIP.setPosition(675, 2000);

			
			spritePlayer.setPosition(580, 720);
			acceptInput = true;

		}
		
		
		if (acceptInput) {
			
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				
				playerSide = side::RIGHT;
				score++;
				
				timeRemaining += (2 / score) + 0.15;

				
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);

				
				spritePlayer.setPosition(1200, 720);

				
				updateBranches(score);
				scoreText.setString("Score = " + std::to_string(score));

				
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				chop.play();

			}
		
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				
				playerSide = side::LEFT;
				score++;

				timeRemaining += (2 / score) + 0.15;

				
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);

				
				spritePlayer.setPosition(580, 720);

				
				updateBranches(score);

				scoreText.setString("Score = " + std::to_string(score));

				
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;

				chop.play();

			}
		}
		if (!paused) {

		
			Time dt = clock.restart();
			
			
			timeRemaining -= dt.asSeconds();
			
			timeBar.setSize(Vector2f(timeBarWidthPerSecond*timeRemaining, timeBarHeight));

			
			if (timeRemaining <= 0.0f) {
				
				paused = true;	
				
				messageText.setString("Out of Time!");

				
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				outOfTime.play();

			}

		
			if (beeActive == false) {

				
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 200;

				
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;

			}
			else {
				
				spriteBee.setPosition(
					spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y);

				
				if (spriteBee.getPosition().x < -100) {
					
					beeActive = false;
				}

			}

			
			if (cloud1Active == false) {

				
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;
			}
			else {
				
				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x +
					(cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y);


				if (spriteCloud1.getPosition().x > 1920) {

					cloud1Active = false;
				}
			}


			if (cloud2Active == false) {


				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);


				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else {

				spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);


				if (spriteCloud2.getPosition().x > 1920) {

					cloud2Active = false;
				}
			}


			if (cloud3Active == false) {


				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);


				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else {

				spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);


				if (spriteCloud3.getPosition().x > 1920) {

					cloud3Active = false;
				}
			}


			for (int i = 0; i < NUM_BRANCHES; i++) {
				float height = i * 150;
				if (branchPositions[i] == side::LEFT) {

					branches[i].setPosition(610, height);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT) {

					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else {

					branches[i].setPosition(3000, height);
				}
			}


			if (logActive) {
				spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));
				

				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000) {
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			if (playerSide == branchPositions[5]) {
				paused = true;
				acceptInput = false;


				spriteRIP.setPosition(525, 760);

				spritePlayer.setPosition(2000, 660);


				messageText.setString("GAME OVER!");

				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				death.play();


			}
}


		window.clear();


		window.draw(spriteBackground);
		

		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);


		window.draw(spriteTree);


		window.draw(spriteBee);
		

		window.draw(timeBar);
		

		window.draw(scoreText);
		

		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}
		
		
		window.draw(spritePlayer);

		
		window.draw(spriteAxe);

		


		window.draw(spriteLog);
		

		window.draw(spriteRIP);
		
		if (paused) {
			window.draw(messageText);
		}
		
		window.display();

	}

    return 0;
        
}
    void updateBranches(int seed) {
	
	
	for (int i = NUM_BRANCHES - 1; i > 0; i--) {
		branchPositions[i] = branchPositions[i - 1];
	}

	
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;

	case 1:
		branchPositions[0] = side::RIGHT;
		break;

	default:
		branchPositions[0] = side::NONE;
		break;
	}
}
