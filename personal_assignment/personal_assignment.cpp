/*객체지향 프로그래밍
  개인과제 - 미로게임
 */

#include <bangtal>
using namespace bangtal;

int main()
{
	//필요없는 아이콘 지우기
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	//장면생성
	auto scene = Scene::create("Maze-step1", "pa_images/미로.jpg");

	//오브젝트 생성
	auto starX = 350;   //아무 초깃값 잡아놓음. 수정하기
	auto starY = 510;
	auto finishX= 650;
	auto finishY =60;

	auto star = Object::create("pa_images/별.png", scene, starX, starY);
	star->setScale(0.02f);

	auto startButton = Object::create("pa_images/start.png", scene, 590, 70);
	auto endButton = Object::create("pa_images/end.png", scene, 590, 20);

	auto upButton = Object::create("pa_images/위화살표.png", scene, 610, 80, false);
	auto downButton = Object::create("pa_images/아래화살표.png", scene, 610, 20, false);
	auto leftButton = Object::create("pa_images/왼화살표.png", scene, 560, 50, false);
	auto rightButton = Object::create("pa_images/오화살표.png", scene, 660, 50, false);
	upButton->setScale(0.07f);
	downButton->setScale(0.07f);
	leftButton->setScale(0.07f);
	rightButton->setScale(0.07f);


	//타이머생성
	auto timer = Timer::create(150.f);
	showTimer(timer);
	timer->setOnTimerCallback([&](TimerPtr)->bool {
		showMessage("FAIL");
		upButton->hide();
		downButton->hide();
		leftButton->hide();
		rightButton->hide();

		startButton->setImage("pa_images/restart.png");
		startButton->show();
		endButton->show();

		return true;
		});

		//사운드생성
	auto sound = Sound::create("pa_sound/play.mp3");
	sound->play(true);



	//마우스콜백함수 생성
	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		startButton->hide();
		endButton->hide();

		upButton->show();
		downButton->show();
		leftButton->show();
		rightButton->show();

		star->locate(scene, 350, 510);

		timer->set(150.f);
		timer->start();

		return true;
		});

	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
		});

	upButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		starY += 10;
		star->locate(scene, starX, starY);

		if (starX == finishX && starY== finishY) {
			showMessage("~SUCCESS~");
			timer->stop();

			upButton->hide();
			downButton->hide();
			leftButton->hide();
			rightButton->hide();
			endButton->show();
			startButton->setImage("pa_images/restart.png");
			startButton->show();
		}
		return true;
		});

	downButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		starY -= 10;
		star->locate(scene, starX, starY);

		if (starX == finishX && starY == finishY) {
			showMessage("~SUCCESS~");
			timer->stop();

			upButton->hide();
			downButton->hide();
			leftButton->hide();
			rightButton->hide();
			endButton->show();
			startButton->setImage("pa_images/restart.png");
			startButton->show();
		}
		return true;
		});

	rightButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		starX += 10;
		star->locate(scene, starX, starY);

		if (starX == finishX && starY == finishY) {
			showMessage("~SUCCESS~");
			timer->stop();

			upButton->hide();
			downButton->hide();
			leftButton->hide();
			rightButton->hide();
			endButton->show();
			startButton->setImage("pa_images/restart.png");
			startButton->show();
		}
		return true;
		});

	leftButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		starX -= 10;
		star->locate(scene, starX, starY);

		if (starX == finishX && starY == finishY) {
			showMessage("~SUCCESS~");
			timer->stop();

			upButton->hide();
			downButton->hide();
			leftButton->hide();
			rightButton->hide();
			endButton->show();
			startButton->setImage("pa_images/restart.png");
			startButton->show();
		}
		return true;
		});



		startGame(scene);
		return 0;

}