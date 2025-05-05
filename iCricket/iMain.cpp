# include "iGraphics.h"

typedef struct {
	char name[20];
	int score;
} HighScore;

char demo[20];
int demo_int;
char menu_state = 'a';

int x = 300, y = 300, r = 20;
double bx = 295, by = 250;
double batx = 303, baty = 396;
double shx = bx - 2, shy = by;
double height = 1;
int tmove, moveFrequency = 70;
bool bowling = false, fielding = false, pressedInThisBowl = false, fielded = false, loftedShot = false, running = false;
char direction = 's', battersDirection = 'd';
int timing = -1;
int shotStrength = 0;
int runs = 0, prevruns = 0, wickets = 0;
char scoreDisplay[12], scoreInLeaderboard[100];

double p[][2] = {{113,511},{140,167},{389,90},{520,355},{361,452},{379,274},{267,242},{193,370},{284,434},{302,419},{294.5,246}};
double P[][2] = {{113,511},{140,167},{389,90},{520,355},{361,452},{379,274},{267,242},{193,370},{284,434},{302,419},{294.5,246}};

void initializeGame() {
	for (int i = 0; i < 11; ++i) {p[i][0] = P[i][0]; p[i][1] = P[i][1];}
	x = 300, y = 300, r = 20;
	bx = 295, by = 250;
	batx = 303, baty = 396;
	shx = bx - 2, shy = by;
	height = 1;
	tmove, moveFrequency = 70;
	bowling = false, fielding = false, pressedInThisBowl = false, fielded = false, loftedShot = false;
	direction = 's', battersDirection = 'd';
	timing = -1;
	shotStrength;
	runs = 0, prevruns = 0, wickets = 0;
	scoreDisplay[12];
	scoreInLeaderboard[100];
}

/*
	function iDraw() is called again and again by the system.

	*/

void iDraw() {
	//place your drawing codes here
	iClear();

	if (menu_state == 'a') {
		iShowBMP(0, 0, "game_background.bmp");
		return;
	}
	if (menu_state == 'l') {
		iShowBMP(0, 0, "leaderboard_background.bmp");
		HighScore highScoresL[5];
		FILE *recordFile = fopen("leaderboard.txt", "r");
		for (int i = 0; i < 5; ++i) {
			fscanf(recordFile, "%s %d", highScoresL[i].name, &highScoresL[i].score);
		}
		fclose(recordFile);
		iSetColor(47,48,36);
		iText(250, 470, "Rank        |        Score", GLUT_BITMAP_TIMES_ROMAN_24);
		// iText(250.4, 470, "Rank        |        Score", GLUT_BITMAP_TIMES_ROMAN_24);
		// iText(250, 470.4, "Rank        |        Score", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(250.5, 470.5, "Rank        |        Score", GLUT_BITMAP_TIMES_ROMAN_24);
		for (int i = 0; i < 5; ++i) {
			sprintf(scoreInLeaderboard, "   %d.                      %d", i+1, highScoresL[i].score);
			iText(250, 420 - i*45, scoreInLeaderboard, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		for (int i = 0; i < 5; ++i) {
			sprintf(scoreInLeaderboard, "   %d.                      %d", i+1, highScoresL[i].score);
			iText(250.5, 420 - i*45, scoreInLeaderboard, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		// iText(245, 471, "Rank     |     Name     |     Score", GLUT_BITMAP_TIMES_ROMAN_24);
		// for (int i = 0; i < 5; ++i) {
		// 	sprintf(scoreInLeaderboard, "  %d.             %s             %d", i+1, highScoresL[i].name, highScoresL[i].score);
		// 	iText(245, 420 - i*45, scoreInLeaderboard, GLUT_BITMAP_TIMES_ROMAN_24);
		// }
		return;
	}
	if (menu_state == 'i') {
		iShowBMP(0, 0, "instructions.bmp");
		return;
	}


	if (fielded) fielding = false;
	if (loftedShot == false && bowling == false && fielding == true) height = 0;
	shx = bx - height;
	shy = by;


	iSetColor(1, 100, 45);
	iFilledRectangle(0, 0, 800, 750); // Field
	iSetColor(200, 220, 220);
	iLine(600, 0, 600, 750);
	iSetColor(241, 210, 207);
	iFilledRectangle(290, 290, 20, 120); // Pitch

	iSetColor(200, 200, 200);
	iEllipse(300, 350, 250, 330, 18); // Boundary
	// iCircle(300, 350, 130, 20); // Powerplay Area
	iPoint(340, 227, 1);
	iPoint(406, 275, 1);
	iPoint(429, 350, 1);
	iPoint(405, 426, 1);
	iPoint(340, 473, 1);
	iPoint(259, 474, 1);
	iPoint(194, 426, 1);
	iPoint(170, 352, 1);
	iPoint(194, 275, 1);
	iPoint(259, 227, 1);

	iPoint(376, 455, 1);
	iPoint(423, 389, 1);
	iPoint(424, 313, 1);
	iPoint(377, 246, 1);
	iPoint(299, 220, 1);
	iPoint(222, 244, 1);
	iPoint(176, 311, 1);
	iPoint(176, 391, 1);
	iPoint(223, 455, 1);
	iPoint(300, 481, 1);
	
	iLine(280, 400, 320, 400);
	iLine(280, 300, 320, 300);

	iSetColor(2, 73, 12);
	iFilledCircle(shx, shy, 3); // shadow of ball
	iSetColor(240, 10, 10);
	iFilledCircle(bx, by, 3); // ball

	// fielders
	iSetColor(250, 250, 250);
	for (int i = 0; i < 10; ++i) {
		iFilledCircle(p[i][0], p[i][1], 5);
	}
	iSetColor(0, 0, 0);
	iFilledCircle(p[10][0], p[10][1], 5); // bowler
	iSetColor(8,92,81);
	iFilledCircle(batx, baty, 4); // batsman

	iSetColor(141,106,110);
	iLine(297, 404.5, 303, 404.5); // Stump;
	iPoint(297, 405, 1);
	iPoint(300, 405, 1);
	iPoint(303, 405, 1);

	iSetColor(0, 0, 0);
	sprintf(scoreDisplay, "Score: %d/%d", runs, wickets);
	iText(450, 670, scoreDisplay, GLUT_BITMAP_HELVETICA_18);
	
	if (loftedShot && shotStrength == 30 && pow((bx-300)/260, 2) + pow((by-350)/340, 2) > 1) {
		iClear();
		iShowBMP(205, 150, "six.bmp");
	} else if (pow((bx-300)/260, 2) + pow((by-350)/340, 2) > 1) {
		iClear();
		iShowBMP(135, 100, "four.bmp");
	}

	if (wickets == 10 && bowling) {
		iShowBMP(105, 250, "game_over.bmp");
		HighScore highScores[6];
		FILE *recordFile10r = fopen("leaderboard.txt", "r");
		for (int i = 0; i < 5; ++i) {
			fscanf(recordFile10r, "%s %d", highScores[i].name, &highScores[i].score);
		}
		fclose(recordFile10r);
		sprintf(highScores[5].name, "Ruhan");
		highScores[5].score = runs;
		for (int i = 0; i < 6; ++i) {
			int maxIndex = i, maxValue = highScores[i].score;
			for (int j = i + 1; j < 6; ++j) {
				if (highScores[j].score > maxValue) {
					maxIndex = j;
					maxValue = highScores[j].score;
				}
			}
			HighScore tempHS;
			tempHS = highScores[i];
			highScores[i] = highScores[maxIndex];
			highScores[maxIndex] = tempHS;
		}
		FILE *recordFile10w = fopen("leaderboard.txt", "w");
		for (int i = 0; i < 5; ++i) {
			fprintf(recordFile10w, "%s %d\n", highScores[i].name, highScores[i].score);
		}
		fclose(recordFile10w);
		Sleep(1000);
		initializeGame();
		menu_state = 'a';
	}
}

void move() {
	if (menu_state == 'p') {
		if (bowling && !fielding) {
			if (by < 297) {
				p[10][1] += 2;
				by += 2;
				moveFrequency = 30;
			}
			else if (by <= 395) {
				by += 5;
				moveFrequency = 10;
				if (bx < 299) {
					bx += 0.25;
					if (by < 340) height += 0.5;
					else height -= 0.5;
				}
			} else {
				height = 1;
				bowling = false;
				fielding = true;
			}
		}
		if (fielding) {
			// printf ("Direction: %c\n", direction);
			if (pow((bx-300)/260, 2) + pow((by-350)/340, 2) <= 1) {
				if (running) {
					if (battersDirection == 'n') {
						if (396-baty > baty-305) battersDirection = 'd';
						else battersDirection = 'u';
					}
					if (battersDirection == 'd' && baty > 305) {
						baty -= 7;
					} else if (battersDirection == 'd' && baty <= 305) {
						if (shotStrength == 10) ++runs;
						battersDirection = 'u';
					} else if (battersDirection == 'u' && baty < 396) {
						baty += 7;
					} else if (battersDirection == 'u' && baty >= 396) {
						if (shotStrength == 10) ++runs;
						battersDirection = 'd';
					}
				} else {
					if (battersDirection == 'u' && baty > 305) {
						baty -= 5;
					} else if (battersDirection == 'u' && baty <= 305) {
						battersDirection = 'n';
					} else if (battersDirection == 'd' && baty < 396) {
						baty += 5;
					} else if (battersDirection == 'd' && baty >= 396) {
						battersDirection = 'n';
					}
				}

				switch (direction)
				{
				case 'q':
					if (shotStrength == 30) {
						if (bx > 200) height += 3;
						else height -= 3;
					} else if (shotStrength == 20) {
						if (bx > 250) height += 2;
						else if (bx > 200) height -= 2;
						else height = 2;
					} else if (shotStrength == 10) {
						if (bx > 220) height += 3.8;
						else if (bx > 140) height -= 3.5;
						else height = 2;
					}
					if  (shotStrength != 10 || bx > 140) {
						p[0][0] += 1;
						p[0][1] += 3.1;
						bx -= shotStrength;
						by += shotStrength;
					} else {
						bx = 133; by = 559;
						fielded = true;
					}
					break;
				case 'w':
					if (shotStrength == 30) {
						if (by < 550) height += 3;
						else height -= 3;
					} else if (shotStrength == 20) {
						if (by < 470) height += 2;
						else if (by < 540) height -= 2;
						else height = 2;
					}
					if (shotStrength != 10 || by < 432) {
						p[8][0] = 289;
						p[8][1] = 437;
						bx -= 2;
						by += shotStrength;
					} else {
						bx = 290; by = 432;
						fielded = true;
					}
					break;
				case 'e':
					if (by > 350 && batx >= 303) batx -= 1.5;
					if (shotStrength == 30) {
						if (bx < 500) height += 3;
						else height -= 3;
					} else if (shotStrength == 20) {
						if (bx < 350) height += 2;
						else if (bx < 400) height -= 2;
						else height = 2;
					} else if (shotStrength == 10) {
						if (bx < 325) {
							height += 3.8;
							bx -= 5;
							by -= 5;
						}
						else if (bx < 350) {
							height -= 3.5;
							bx -= 5;
							by -= 5;
						}
						else height = 2;
					}
					if (shotStrength != 10 || bx < 350) {
						p[4][0] = 359;
						p[4][1] = 456;
						bx += shotStrength;
						by += shotStrength;
					} else {
						bx = 356; by = 453;
						fielded = true;
					}
					break;
				case 'a':
					if (shotStrength == 30) {
						if (bx > 170) height += 3;
						else height -= 3;
					} else if (shotStrength == 20) {
						if (bx > 250) height += 2;
						else if (bx > 200) height -= 2;
						else height = 2;
					} else if (shotStrength == 10) {
						if (bx > 235) {
							height += 3.8;
						}
						else if (bx > 170) {
							height -= 3.7;
						}
						else height = 2;
					}
					if (shotStrength != 10 || bx > 170) {
						p[7][0] -= 2;
						p[7][1] += 2;
						p[0][0] -= 1.7;
						p[0][1] -= 4;
						bx -= shotStrength;
						// by += 5;
					} else {
						bx = 170; by = 398;
						fielded = true;
					}
					break;
				case 's':
					// bx -= 5;
					by += 7;
					bowling = false;
					fielding = false;
					break;
				case 'd':
					if (by > 350 && batx >= 303) batx -= 1.5;
					if (shotStrength == 30) {
						if (bx < 430) height += 3;
						else height -= 3;
					} else if (shotStrength == 20) {
						if (bx < 350) height += 2;
						else if (bx < 400) height -= 2;
						else height = 2;
					} else if (shotStrength == 10) {
						if (bx < 413.5) {
							height += 3;
						}
						else if (bx < 527) {
							height -= 3;
						}
						else height = 2;
					}
					if (shotStrength != 10 || bx < 527) {
						p[3][0] += 0.45;
						p[3][1] += 1.9;
						bx += shotStrength;
						// by += 5;
					} else {
						bx = 527; by = 398;
						fielded = true;
					}
					break;
				case 'z':
					if (shotStrength == 30) {
						if (bx > 180) height += 4;
						else height -= 4;
					} else if (shotStrength == 20) {
						if (bx > 250) height += 2;
						else if (bx > 200) height -= 2;
						else height = 2;
					} else if (shotStrength == 10) {
						if (bx > 202) {
							height += 3.8;
						}
						else if (bx > 104) {
							height -= 3.7;
						}
						else height = 2;
					}
					if (shotStrength != 10 || bx > 104) {
						p[1][0] -= 2;
						p[1][1] += 1.5;
						bx -= shotStrength;
						by -= shotStrength;
					} else {
						bx = 103.8; by = 198;
						fielded = true;
					}
					break;
				case 'x':
					if (shotStrength == 30) {
						if (by > 204) height += 3;
						else height -= 3;
					} else if (shotStrength == 20) {
						if (by > 225) height += 2;
						else if (by > 150) height -= 2;
						else height = 2;
					} else if (shotStrength == 10) {
						if (by > 286) {
							height += 3.8;
						}
						else if (by > 172) {
							height -= 3.7;
						}
						else height = 2;
					}
					if (shotStrength != 10 || by > 172) {
						p[6][0] += 1.25;
						p[6][1] -= 3.3;

						p[2][0] -= 2;
						p[2][1] -= 0.2;
						// bx -= 5;
						if (shotStrength == 20) by -= 17;
						else by -= shotStrength;
					} else {
						bx = 299; by = 168;
						fielded = true;
					}
					break;
				case 'c':
					if (by > 350 && batx >= 303) batx -= 1.5;
					if (shotStrength == 30) {
						if (bx < 420) height += 3;
						else height -= 3;
					} else if (shotStrength == 20) {
						if (bx < 350) height += 2;
						else if (bx < 400) height -= 2;
						else height = 2;
					} else if (shotStrength == 10) {
						if (bx < 408.5) {
							height += 3.8;
						}
						else if (bx < 517) {
							height -= 3.7;
						}
						else height = 2;
					}
					if (shotStrength != 10 || bx < 517) {
						p[3][0] += 0.8;
						p[3][1] -= 6.1;

						p[5][0] += 3;
						p[5][1] += 0.5;
						bx += shotStrength;
						// by += 5;
					} else {
						bx = 517; by = 294.7;
						fielded = true;
					}
					if (shotStrength == 30) {
						bx += 25;
						by -= 25;
					} else {
						bx += shotStrength;
						by -= shotStrength;
					}
					break;
				// case 'b':
				// 	bx = 295;
				// 	by = 250;
				// 	fielding = false;
				// 	bowling = false;
				// 	break;
				default:
					// bx -= 5;
					by += 7;
					bowling = false;
					fielding = false;
					direction = 's';
					break;
				}
			} else {
				height = 1;
				if (shotStrength == 30 && loftedShot) {
					runs += 6;
				}
				else {
					runs += 4;
				}
				fielding = false;
				bowling = false;
			}
		}
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	// printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		printf("x = %d, y = %d\n", mx, my);
		if (menu_state == 'a') {
			if (mx >= 521 && mx <= 938 && my >= 296 && my <= 361) {
				menu_state = 'p';
			} else if (mx >= 521 && mx <= 938 && my >= 117 && my <= 242) {
				menu_state = 'l';
			} else if (mx >= 1388 && mx <= 1426 && my >= 673 && my <= 717) {
				menu_state = 'i';
			} else if (mx >= 521 && mx <= 938 && my >= 55 && my <= 119) {
				exit(0);
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == '/') {
		exit(0);
	}
	if (menu_state != 'a') {
		if (key == 'B') menu_state = 'a';
		else if (key == 'C') {
			wickets = 10;
			bowling = true;
		}
	}
	//place your codes for other keys here
	if (menu_state != 'p') return;
	if (!bowling && key == 'b') {
		if (bx == 295 && by == 250) bowling = true;
		else if (pow((bx-300)/260, 2) + pow((by-350)/340, 2) > 1 || direction == 's' || (fielded && key == 'b')) {
			for (int i = 0; i < 11; ++i) {p[i][0] = P[i][0]; p[i][1] = P[i][1];}
			bx = 295; by = 250;
			batx = 303, baty = 396;
			// fielding = false;
			fielded = false;
			running = false;
			battersDirection = 'd';
			if (direction == 's' || (shotStrength == 10 && loftedShot)) ++wickets;
			printf("Run: %d + %d = %d\n", prevruns, runs - prevruns, runs);
			// sprintf(scoreDisplay, "Score: %d/%d", runs, wickets);
			prevruns = runs;
		}
		pressedInThisBowl = false;
		if (!fielding) {
			loftedShot = false;
		}
	}
	if (key == 'r') running = !running;
	if (bowling) {
		if (by > 395) shotStrength = 30;
		else if (by > 390) shotStrength = 20;
		else if (by > 380) shotStrength = 10;
		else direction = 's';
		if (by > 380 && !pressedInThisBowl) direction = key;
		// printf ("Direction: %d\n", pressedInThisBowl);
		if (by >= 300 && bowling && !fielding && (key == 'q' || key == 'w' || key == 'e' || key == 'a' || key == 'd' || key == 'z' || key == 'x' || key == 'c' || key == 's')) pressedInThisBowl = true;
	}
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	if (menu_state != 'p') return;
	if (key == GLUT_KEY_UP) {
		if (bowling == true && by < 400) {
			loftedShot = true;
		}
	} else if (bowling == true && key == GLUT_KEY_DOWN) {
		if (by < 400) {
			loftedShot = false;
		}
	}
	//place your codes for other keys here
}


int main() {
	//place your own initialization codes here.
	tmove = iSetTimer(moveFrequency, move);
	iInitialize(599, 740, "iCricket");
	return 0;
}
