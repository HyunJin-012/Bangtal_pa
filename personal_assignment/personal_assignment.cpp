/*객체지향 프로그래밍
  개인과제 - 미로게임 Way to School
 */

#include <iostream>
#include <bangtal>
using namespace bangtal;
using namespace std;

int main()
{
	//필요없는 아이콘 지우기
	//setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	//setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	//장면생성
	auto intro = Scene::create("Intro", "pa_images/현관.jpg");
	auto scene = Scene::create("Way to  School", "pa_images/미로.jpg");
	auto scene1 = Scene::create("in the Playground", "pa_images/놀이터.jpg");
	auto scene2 = Scene::create("in the Park", "pa_images/공원.jpg");
	auto scene3 = Scene::create("in the Shop", "pa_images/문구점.jpg");
	scene3->setLight(0.88f);
	auto scene4 = Scene::create("in the Cafe", "pa_images/카페내부.jpg");
	

	//오브젝트 생성
	auto move = 15;
	auto starX = 350;   //아무 초깃값 잡아놓음. 수정하기
	auto starY = 510;
	auto finishX= 650;
	auto finishY =60;
	auto click_returnX= 14;
	auto click_returnY = 10;
	

	auto star = Object::create("pa_images/별.png", scene, starX, starY);
	star->setScale(0.02f);
	
	auto startButton = Object::create("pa_images/start.png", scene, 590, 70);
	auto endButton = Object::create("pa_images/end.png", scene, 590, 20);

	auto upButton = Object::create("pa_images/위화살표.png", scene, 860, 75, false);
	auto downButton = Object::create("pa_images/아래화살표.png", scene, 860, 25, false);
	auto leftButton = Object::create("pa_images/왼화살표.png", scene, 820, 50, false);
	auto rightButton = Object::create("pa_images/오화살표.png", scene, 900, 50, false);
	upButton->setScale(0.06f);
	downButton->setScale(0.06f);
	leftButton->setScale(0.06f);
	rightButton->setScale(0.06f);


	//타이머생성
	auto timer = Timer::create(90.0f);
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

		timer->set(90.f);
		timer->start();

		return true;
		});

	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
		});

	upButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		starY += move;
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
		starY -= move;
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
		starX += move;
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
		starX -= move;
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

	auto end = Object::create("pa_images/도착.png", scene, 650, 40);
	end->setScale(0.2f);
	end->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("~~~SUCCESS~~~");

		upButton->hide();
		downButton->hide();
		leftButton->hide();
		rightButton->hide();
		endButton->show();
		startButton->setImage("pa_images/restart.png");
		startButton->show();

		return true;
		});



	//intro-->게임시작
	auto me = Object::create("pa_images/나.png", intro, 600, 10);
	auto go = Object::create("pa_images/흰색클릭.png", intro, 640, 5);
	me->setScale(0.3f);
	go->setScale(0.1f);

	me->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("학교에 지각하겠어! 1분 30초 안에 도착해야해! \n 가는 길에 해야할 일들을 잊지마!!");
		
		go->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			scene->enter();
			return true;
			});

		return true;
		});
	
	//scene1--놀이터에서 동생과 인사하기
	auto click1 = Object::create("pa_images/클릭.png", scene, 780, 540);
	auto child1 = Object::create("pa_images/어린이1.png", scene1, 120, 110);
	auto child2 = Object::create("pa_images/어린이2.png", scene1, 700, 100);
	auto brother = Object::create("pa_images/동생.png", scene1, 500, 120);
	auto click_return1 = Object::create("pa_images/이전으로.png", scene1, click_returnX, click_returnY, false);

	click1->setScale(0.05f);
	click_return1->setScale(0.05f);
	child1->setScale(0.2f);
	child2->setScale(0.2f);
	brother->setScale(0.2f);

	click1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		click_return1->show();

		showMessage("동생에게 인사하자!");
		brother->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			showMessage("~학교 다녀올게~");
			return true;
			});
		click_return1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			scene->enter();
			return true;
			});

		return true;
		});



	//scene2--친구 만나서 전공책 받기
	auto click2 = Object::create("pa_images/클릭.png", scene, 470, 210);
	auto friend_girl = Object::create("pa_images/친구_여.png", scene2, 460, 110);
	auto click_return2 = Object::create("pa_images/이전으로.png", scene2, click_returnX, click_returnY);
	auto book = Object::create("pa_images/책.png", scene2, 848, 353);

	click2->setScale(0.05f);
	click_return2->setScale(0.05f);
	friend_girl->setScale(0.25f);

	click2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		
		showMessage("친구에게 전공책을 받자!");
		friend_girl->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			book->show();
			book->pick();
			showMessage("~전공책 획득~");
			return true;
			});

		click_return2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			scene->enter();
			return true;
			});

		return true;
		});


	//scene3--문구점 미션
	auto click3 = Object::create("pa_images/클릭.png", scene, 730, 180);
	auto click_shop1 = Object::create("pa_images/흰색클릭.png", scene3, 520, 110);
	auto click_shop2  = Object::create("pa_images/흰색클릭.png", scene3, 230, 670);
	auto click_return3 = Object::create("pa_images/이전으로.png", scene3, click_returnX, click_returnY);
	auto note = Object::create("pa_images/노트.png", scene3, 848, 353, false);
	auto highlight = Object::create("pa_images/형광펜.png", scene3, 848, 353, false);

	click3->setScale(0.05f);
	click_return3->setScale(0.05f);
	click_shop1->setScale(0.07f);
	click_shop2->setScale(0.07f);

	click3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene3->enter();
		click3->hide();

		showMessage("노트와 형광펜을 사자!");
		click_shop1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			note->show();
			note->pick();
			showMessage("~노트 획득~");
			click_shop1->hide();
			return true;
			});
		click_shop2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			highlight->show();
			highlight->pick();
			showMessage("~형광펜 획득~");
			click_shop2->hide();
			return true;
			});

		click_return3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			scene->enter();
			return true;
			});
		
		return true;
		});



	//scene4--커피사기 미션
	auto click4 = Object::create("pa_images/클릭.png", scene, 880, 365);
	auto click_cafe = Object::create("pa_images/클릭.png", scene4, 695, 320);
	auto click_return4 = Object::create("pa_images/이전으로.png", scene4, click_returnX, click_returnY);
	auto coffee = Object::create("pa_images/커피.png", scene4, 845, 350, false);

	click4->setScale(0.05f);
	click_cafe->setScale(0.05f);
	click_return4->setScale(0.05f);
	

	click4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		//scene->setImage("pa_images/카페내부.jpg");
		scene4->enter();
		click4->hide();
		
		showMessage("수업시간에 마실 커피를 사자!");
		click_cafe->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			coffee->show();
			coffee->pick();
			showMessage("~커피 획득~");
			return true;
			});
		
		click_return4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			scene->enter();
			return true;
			});

		return true;
		});


		startGame(intro);
		return 0;

}