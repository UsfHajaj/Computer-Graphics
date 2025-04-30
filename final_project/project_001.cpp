#include <iostream>
//#include <unistd.h>
#include <time.h>
#include <math.h>

// Apple Specific Compatibility Issues

using namespace std;

#include "glut.h"


// Define the value of PI, upto 12 decimal places
#define PI 3.141592653589

// ID to detect which scene the story is in.
int SCENE_ID;




// Variables for Color Morphers
GLfloat window_top_r = 59, window_top_g = 91, window_top_b = 132,
window_bottom_r = 97, window_bottom_g = 131, window_bottom_b = 159,
sky_r = 12, sky_g = 172, sky_b = 232,
grass_r = 255, grass_g = 190, grass_b = 9,
sun_r = 251, sun_g = 255, sun_b = 163, sun_move_left,
traffic_r1= 104, traffic_g1= 37, traffic_b1= 37,
traffic_r2 = 142, traffic_g2 = 151, traffic_b2 = 21,
traffic_r3 = 8, traffic_g3 = 84, traffic_b3 = 59;


// Variables for Turn-based Switching
bool sun_moved_half, sun_has_set, stars_are_made;

// Variables for Random Star Generation
int star_alpha, no_of_stars, stars_array[40][2];

// Function to Create Delay
void delay(float secs) {
	float end = clock() / CLOCKS_PER_SEC + secs;
	while ((clock() / CLOCKS_PER_SEC) < end);
}




// Function to Draw Circle
void drawCircle(GLfloat x, GLfloat y,
	GLfloat r, GLfloat g, GLfloat b,
	GLfloat sx, GLfloat sy,
	GLfloat radius) {
	glPushMatrix();

	glTranslatef(x, y, 0);
	glScalef(sx, sy, 0);

	glBegin(GL_POLYGON);
	glColor3ub(r, g, b);
	for (GLfloat i = 0; i < 360; i += 5)
		glVertex2f(radius * sin(i * PI / 180), radius * cos(i * PI / 180));
	glEnd();

	glPopMatrix();
}
void drawSemiCircle(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat r, GLfloat g, GLfloat b,
	GLfloat radius,
	GLfloat start_angle, GLfloat end_angle) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	glBegin(GL_POLYGON);
	glColor3ub(r, g, b);
	for (GLfloat i = start_angle; i < end_angle; i += 5)
		glVertex2f(radius * sin(i * PI / 180), radius * cos(i * PI / 180));
	glEnd();

	glPopMatrix();
}

// Function to Draw Arc
void drawArc(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat r, GLfloat g, GLfloat b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3ub(r, g, b);
	for (GLfloat i = 90; i < 270; i++)
		glVertex2f(15 * sin(i * PI / 180), 15 * cos(i * PI / 180));
	glEnd();
	glPointSize(1);

	glPopMatrix();
}
void drawTree(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	// Bark
	glBegin(GL_POLYGON);
	glColor3ub(86, 46, 11);
	glVertex2f(0, 0);
	glVertex2f(40, 0);
	glColor3ub(71, 36, 6);
	glVertex2f(35, 200);
	glVertex2f(5, 200);
	glEnd();

	// Tree
	drawCircle(20, 200, 5, 80, 10, 1, 1, 80);

	// Apples
	drawCircle(80, 200, 5, 80, 10, 1, 1.3, 30);
	drawCircle(80, 160, 5, 80, 10, 1, 1.3, 30);
	drawCircle(80, 160, 5, 80, 10, 1, 1.3, 30);
	drawCircle(40, 140, 5, 80, 10, 1, 1.3, 30);
	drawCircle(-10, 140, 5, 80, 10, 1, 1.3, 30);
	drawCircle(-40, 200, 5, 80, 10, 1, 1.3, 30);
	drawCircle(-60, 160, 5, 80, 10, 1, 1.3, 30);
	drawCircle(-60, 160, 5, 80, 10, 1, 1.3, 30);
	drawCircle(-40, 140, 5, 80, 10, 1, 1.3, 30);
	drawCircle(20, 280, 5, 80, 10, 1, 1.3, 30);
	drawCircle(-20, 280, 5, 80, 10, 1, 1.3, 30);
	drawCircle(60, 280, 5, 80, 10, 1, 1.3, 30);
	drawCircle(-40, 250, 5, 80, 10, 1, 1.3, 30);
	drawCircle(-40, 240, 5, 80, 10, 1, 1.3, 30);
	drawCircle(70, 250, 5, 80, 10, 1, 1.3, 30);
	drawCircle(27, 194, 255, 0, 0, 1, 1.2, 5);
	drawCircle(-15, 170, 255, 0, 0, 1, 1.2, 5);
	drawCircle(47, 155, 255, 0, 0, 1, 1.2, 5);
	drawCircle(-2, 228, 255, 0, 0, 1, 1.2, 5);
	drawCircle(72, 216, 255, 0, 0, 1, 1.2, 5);
	drawCircle(60, 194, 255, 0, 0, 1, 1.2, 5);
	drawCircle(90, 170, 255, 0, 0, 1, 1.2, 5);
	drawCircle(100, 155, 255, 0, 0, 1, 1.2, 5);
	drawCircle(-20, 228, 255, 0, 0, 1, 1.2, 5);
	drawCircle(-33, 216, 255, 0, 0, 1, 1.2, 5);
	drawCircle(20, 269, 255, 0, 0, 1, 1.2, 5);
	drawCircle(3, 244, 255, 0, 0, 1, 1.2, 5);
	drawCircle(-20, 266, 255, 0, 0, 1, 1.2, 5);
	drawCircle(-33, 280, 255, 0, 0, 1, 1.2, 5);



	glPopMatrix();
}
void drawtower(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat r, GLfloat g, GLfloat b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	glBegin(GL_POLYGON);
	glLineWidth(3);
	glColor3ub(r, g, b);
	glVertex2f(100, 100);
	glVertex2f(100, 140);
	glVertex2f(300, 140);
	glVertex2f(300, 100);
	glEnd();
	glBegin(GL_POLYGON);

	glColor3ub(r, g, b);
	glVertex2f(120, 140);
	glVertex2f(120, 220);
	glVertex2f(280, 260);
	glVertex2f(280, 140);
	glEnd();
	glBegin(GL_POLYGON);

	glColor3ub(r, g, b);
	glVertex2f(130, 222);
	glVertex2f(130, 310);
	glVertex2f(270, 380);
	glVertex2f(270, 257);
	glEnd();
	glBegin(GL_POLYGON);

	glColor3ub(r, g, b);
	glVertex2f(140, 314);
	glVertex2f(140, 420);
	glVertex2f(260, 500);
	glVertex2f(260, 375);
	glEnd();
	glBegin(GL_POLYGON);

	glColor3ub(r, g, b);
	glVertex2f(160, 433);
	glVertex2f(160, 520);
	glVertex2f(240, 600);
	glVertex2f(240, 485);
	glEnd();
	glBegin(GL_POLYGON);

	glColor3ub(r, g, b);
	glVertex2f(180, 538);
	glVertex2f(180, 630);
	glVertex2f(220, 700);
	glVertex2f(220, 580);
	glEnd();
	glBegin(GL_POLYGON);

	glColor3ub(r, g, b);
	glVertex2f(190, 647);
	glVertex2f(190, 750);
	glVertex2f(210, 800);
	glVertex2f(210, 670);
	glEnd();
	//glLineWidth(1);
	glPopMatrix();
}
void HS_drawBackground() {
	// Background
	glBegin(GL_POLYGON);
	glColor3ub(sky_r, sky_g, sky_b); // Sky Blue
	glVertex2f(0, 800);
	glVertex2f(1400, 800);
	glVertex2f(1400, 400);
	glVertex2f(0, 400);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(sky_r, sky_g, sky_b); // Sky Blue
	glVertex2f(0, 400);
	glVertex2f(1400, 400);
	glColor3ub(grass_r, grass_g, grass_b); // Green Grass
	glVertex2f(1400, 175);
	glVertex2f(0, 175);
	glEnd();
}
void HS_drawSun() {
	// Sun
	drawCircle(1250 - sun_move_left, 700,
		sun_r, sun_g, sun_b,
		1, 1,
		50);
}
void HS_drawStars() {
	if (stars_are_made == false) {
		for (int i = 0, j = 0; i < 40; i++) {
			stars_array[i][j] = 0 + (rand() % (int)(1400 - 0 + 1));
			stars_array[i][j + 1] = 530 + (rand() % (int)(800 - 530 + 1));
			no_of_stars++;
		}
		stars_are_made = true;
	}
	else {
		glPointSize(2);
		glBegin(GL_POINTS);
		glColor4ub(255, 255, 255, star_alpha);
		for (int i = 0, j = 0; i < no_of_stars; i++)
			glVertex2f(stars_array[i][j], stars_array[i][j + 1]);
		glEnd();
		glPointSize(1);
	}
}
void HS_drawRoad() {
	// Road
	glBegin(GL_POLYGON);
	glColor3ub(40, 40, 40);
	glVertex2f(0, 175);
	glVertex2f(1400, 175);
	glVertex2f(1400, 0);
	glVertex2f(0, 0);
	glEnd();

	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3ub(255, 255, 255);
	glVertex2f(0, 87);
	glVertex2f(200, 87);

	glVertex2f(300, 87);
	glVertex2f(500, 87);

	glVertex2f(600, 87);
	glVertex2f(800, 87);

	glVertex2f(900, 87);
	glVertex2f(1100, 87);

	glVertex2f(1200, 87);
	glVertex2f(1400, 87);
	glEnd();
	glLineWidth(1);
}
void traffic() {
	glLineWidth(4);
	glBegin(GL_POLYGON);
	glColor3ub(20, 20, 28);
	glVertex2f(1000, 175);
	glVertex2f(1010, 175);
	glVertex2f(1010, 300);
	glVertex2f(1000, 300);
	glEnd();
	glLineWidth(1);
	glLineWidth(4);
	glBegin(GL_POLYGON);
	glColor3ub(20, 20, 28);
	glVertex2f(990, 300);
	glVertex2f(1020, 300);
	glVertex2f(1020, 400);
	glVertex2f(990, 400);
	glEnd();
	glLineWidth(1);
	drawCircle(1005, 380, traffic_r1, traffic_g1, traffic_b1, 1, 1, 10);
	drawCircle(1005, 350, traffic_r2, traffic_g2, traffic_b2, 1, 1, 10);
	drawCircle(1005, 320, traffic_r3, traffic_g3, traffic_b3, 1, 1, 10);



}

void HS_drawHome() {
	// Home Bottom
	glBegin(GL_POLYGON);
	glColor3ub(169, 117, 83);
	glVertex2f(1375, 175);
	glColor3ub(181, 145, 113);
	glVertex2f(1375, 300);
	glColor3ub(181, 145, 113);
	glVertex2f(1100, 300);
	glColor3ub(169, 117, 83);
	glVertex2f(1100, 175);
	glEnd();

	// Home Bottom Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1375, 175);
	glVertex2f(1375, 300);
	glVertex2f(1100, 300);
	glVertex2f(1100, 175);
	glEnd();

	// Home Top Left
	glBegin(GL_POLYGON);
	glColor3ub(181, 145, 113);
	glVertex2f(1100, 300);
	glVertex2f(1220, 300);
	glColor3ub(169, 117, 83);
	glVertex2f(1220, 400);
	glVertex2f(1100, 400);
	glEnd();

	// Home Top Left Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1100, 300);
	glVertex2f(1220, 300);
	glVertex2f(1220, 400);
	glVertex2f(1100, 400);
	glEnd();

	// Triangle Rooftop
	glBegin(GL_TRIANGLES);
	glColor3ub(69, 39, 23);
	glVertex2f(1090, 400);
	glVertex2f(1230, 400);
	glVertex2f(1160, 450);
	glEnd();

	// Triangle Rooftop Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1090, 400);
	glVertex2f(1230, 400);
	glVertex2f(1160, 450);
	glEnd();

	// Home Top Right
	glBegin(GL_POLYGON);
	glColor3ub(69, 39, 23);
	glVertex2f(1220, 375);
	glVertex2f(1375, 375);
	glVertex2f(1375, 300);
	glVertex2f(1220, 300);
	glEnd();

	glBegin(GL_LINES);
	glColor3ub(99, 56, 33);
	for (int temp_x = 1220; temp_x <= 1375; temp_x += 5) {
		glVertex2f(temp_x, 375);
		glVertex2f(temp_x, 300);
	}
	for (int temp_y = 300; temp_y <= 375; temp_y += 5) {
		glVertex2f(1220, temp_y);
		glVertex2f(1375, temp_y);
	}
	glEnd();

	// Home Bottom-Top Divider
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	glVertex2f(1090, 300);
	glVertex2f(1385, 300);
	glEnd();
	glLineWidth(1);

	// Door
	glBegin(GL_POLYGON);
	glColor3ub(31, 47, 53);
	glVertex2f(1130, 175);
	glVertex2f(1130, 280);
	glVertex2f(1190, 280);
	glVertex2f(1190, 175);
	glEnd();

	// Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1130, 175);
	glVertex2f(1130, 280);
	glVertex2f(1190, 280);
	glVertex2f(1190, 175);
	glEnd();

	// Top Window
	glBegin(GL_POLYGON);
	glColor3ub(window_top_r, window_top_g, window_top_b);
	glVertex2f(1130, 330);
	glVertex2f(1130, 370);
	glVertex2f(1190, 370);
	glColor3ub(window_bottom_r, window_bottom_g, window_bottom_b);
	glVertex2f(1190, 330);
	glEnd();

	// Top Window Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1130, 330);
	glVertex2f(1130, 370);
	glVertex2f(1190, 370);
	glVertex2f(1190, 330);
	glEnd();

	// Rectangular Window
	glBegin(GL_POLYGON);
	glColor3ub(59, 91, 132);
	glVertex2f(1240, 280);
	glVertex2f(1240, 240);
	glVertex2f(1355, 240);
	glColor3ub(97, 131, 159);
	glVertex2f(1355, 280);
	glEnd();

	// Rectangular Window Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1240, 280);
	glVertex2f(1240, 240);
	glVertex2f(1355, 240);
	glVertex2f(1355, 280);
	glEnd();

	// Rectangular Window Panes
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	glVertex2f(1297, 280);
	glVertex2f(1297, 240);
	glVertex2f(1355, 260);
	glVertex2f(1240, 260);
	glEnd();

	// Top Circle
	drawCircle(1160, 420,
		255, 255, 255,
		1, 1,
		10);
}

void HS_drawSchool() {
	// School Building
	glBegin(GL_POLYGON);
	glColor3ub(184, 88, 68);
	glVertex2f(400, 175);
	glVertex2f(1000, 175);
	glVertex2f(1000, 500);
	glColor3ub(241, 130, 94);
	glVertex2f(400, 500);
	glEnd();

	// School Building Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(400, 175);
	glVertex2f(1000, 175);
	glVertex2f(1000, 500);
	glVertex2f(400, 500);
	glEnd();

	// School Door
	glBegin(GL_POLYGON);
	glColor3ub(183, 184, 188);
	glVertex2f(600, 175);
	glVertex2f(600, 280);
	glVertex2f(800, 280);
	glVertex2f(800, 175);
	glEnd();

	// School Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(600, 175);
	glVertex2f(600, 280);
	glVertex2f(800, 280);
	glVertex2f(800, 175);
	glEnd();

	// School Door Divider
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	glVertex2f(700, 280);
	glVertex2f(700, 175);
	glEnd();

	// School Windows
	for (int i = 0; i <= 500; i += 100) {
		for (int j = 0; j <= 100; j += 80) {
			glBegin(GL_POLYGON);
			glColor3ub(59, 91, 132);
			glVertex2f(425 + i, 450 - j);
			glVertex2f(475 + i, 450 - j);
			glVertex2f(475 + i, 400 - j);
			glColor3ub(97, 131, 159);
			glVertex2f(425 + i, 400 - j);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glColor3ub(20, 20, 20);
			glVertex2f(425 + i, 450 - j);
			glVertex2f(475 + i, 450 - j);
			glVertex2f(475 + i, 400 - j);
			glVertex2f(425 + i, 400 - j);
			glEnd();

			glLineWidth(4);
			glBegin(GL_LINES);
			glColor3ub(140, 75, 55);
			glVertex2f(425 + i, 400 - j);
			glVertex2f(475 + i, 400 - j);
			glEnd();
			glLineWidth(1);
		}
	}

	glBegin(GL_POLYGON);
	glColor3ub(59, 91, 132);
	glVertex2f(425, 280);
	glVertex2f(475, 280);
	glVertex2f(475, 200);
	glColor3ub(97, 131, 159);
	glVertex2f(425, 200);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(425, 280);
	glVertex2f(475, 280);
	glVertex2f(475, 200);
	glVertex2f(425, 200);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(59, 91, 132);
	glVertex2f(525, 280);
	glVertex2f(575, 280);
	glVertex2f(575, 200);
	glColor3ub(97, 131, 159);
	glVertex2f(525, 200);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(525, 280);
	glVertex2f(575, 280);
	glVertex2f(575, 200);
	glVertex2f(525, 200);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(59, 91, 132);
	glVertex2f(825, 280);
	glVertex2f(875, 280);
	glVertex2f(875, 200);
	glColor3ub(97, 131, 159);
	glVertex2f(825, 200);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(825, 280);
	glVertex2f(875, 280);
	glVertex2f(875, 200);
	glVertex2f(825, 200);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(59, 91, 132);
	glVertex2f(925, 280);
	glVertex2f(975, 280);
	glVertex2f(975, 200);
	glColor3ub(97, 131, 159);
	glVertex2f(925, 200);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(925, 280);
	glVertex2f(975, 280);
	glVertex2f(975, 200);
	glVertex2f(925, 200);
	glEnd();
}

void HS_drawTuition() {
	// Tuition Building
	glBegin(GL_POLYGON);
	glColor3ub(151, 188, 207);
	glVertex2f(25, 175);
	glVertex2f(300, 175);
	glColor3ub(144, 180, 200);
	glVertex2f(300, 350);
	glVertex2f(25, 350);
	glEnd();

	// Tuition Building Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(25, 175);
	glVertex2f(300, 175);
	glVertex2f(300, 350);
	glVertex2f(25, 350);
	glEnd();

	// Tuition Board
	glBegin(GL_POLYGON);
	glColor3ub(255, 218, 154);
	glVertex2f(50, 375);
	glVertex2f(180, 375);
	glVertex2f(180, 325);
	glVertex2f(50, 325);
	glEnd();

	// Tuition Board Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(50, 375);
	glVertex2f(180, 375);
	glVertex2f(180, 325);
	glVertex2f(50, 325);
	glEnd();



	// Tuition Door
	glBegin(GL_POLYGON);
	glColor3ub(70, 39, 21);
	glVertex2f(55, 175);
	glVertex2f(55, 280);
	glVertex2f(115, 280);
	glVertex2f(115, 175);
	glEnd();

	// Tuition Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(55, 175);
	glVertex2f(55, 280);
	glVertex2f(115, 280);
	glVertex2f(115, 175);
	glEnd();

	// Tuition Rectangular Window
	glBegin(GL_POLYGON);
	glColor3ub(59, 91, 132);
	glVertex2f(155, 280);
	glVertex2f(155, 240);
	glVertex2f(270, 240);
	glColor3ub(97, 131, 159);
	glVertex2f(270, 280);
	glEnd();

	// Tuition Rectangular Window Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(155, 280);
	glVertex2f(155, 240);
	glVertex2f(270, 240);
	glVertex2f(270, 280);
	glEnd();

	// Tuition Rectangular Window Panes
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	glVertex2f(213, 280);
	glVertex2f(213, 240);
	glVertex2f(155, 260);
	glVertex2f(270, 260);
	glEnd();
}

void HS_drawLights() {
	// Left Light Pole
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor3ub(200, 200, 200);
	glVertex2f(350, 175);
	glVertex2f(350, 300);
	glEnd();
	glLineWidth(1);

	// Right Light Pole
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor3ub(200, 200, 200);
	glVertex2f(1050, 175);
	glVertex2f(1050, 300);
	glEnd();
	glLineWidth(1);

	// Left Bulb
	drawCircle(350, 300,
		window_top_r, window_top_g, window_top_b,
		1, 1,
		15);

	// Right Bulb
	drawCircle(1050, 300,
		window_top_r, window_top_g, window_top_b,
		1, 1,
		15);
}

void scene_Tow() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	HS_drawBackground();
	HS_drawSun();
	HS_drawRoad();

	HS_drawHome();
	HS_drawSchool();
	drawtower(90,125,.5,.5, 112, 128, 144);
	
	
	HS_drawLights();
	HS_drawStars();
}

void scene_One() {
	glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen


	HS_drawBackground();
	//drawtower(350,120, .5, 0.5, 96, 96, 96);
	HS_drawRoad();
	HS_drawSun();
	//drawTree(500, 175, 1, 1);
	drawTree(375, 175, .6, .6);
	drawTree(575, 175, 1, 1);
	drawTree(775, 175, .6, .6);
	drawTree(125, 175, 1, 1);
	drawTree(1275, 175, 1, 1);
	HS_drawStars();
	traffic();
}
// Function to Render Scene
void renderScene() {
	// Switch to know which scene is playing
	switch (SCENE_ID) {
	case 0:
		scene_One();
		break;
	case 1:
		scene_Tow();
		break;
	
	default:
		break;
	}
	// glFush sends it to the Display Buffer
	glFlush();
}



// Animator Updation Function
void update(int) {

		if (!sun_has_set) {
			if (sun_r <= 255)
				sun_r += .25;
			if (sun_g <= 255)
				sun_g += .25;
			if (sun_b <= 255)
				sun_b += .25;

			if (star_alpha <= 200)
				star_alpha += 1;

			if (grass_r <= 255)
				grass_r += .25;
			if (grass_g <= 220)
				grass_g += .25;
			if (grass_b >= 65)
				grass_b += .25;



			if (sky_r <= 0)
				sky_r += .25;
			if (sky_g >= 0)
				sky_g -= .25;
			if (sky_b >= 0)
				sky_b -= .25;

			if (sun_move_left < 1100)
				sun_move_left += 1.5;
			else
				sun_has_set = true;

			if (sun_move_left > 500)
				sun_moved_half = true;
		}
	
	// Recalls the Display Function
	glutPostRedisplay();

	// Creates a Timer of 25ms
	glutTimerFunc(25, update, 0);
}

// Keyboard Action
void keyPress(unsigned char key, int x, int y) {
	switch (key) {
		// Go to Previous Scene
	case 'b':
	case 'B':
		if (SCENE_ID == 0)
			break;
		SCENE_ID--;
		break;
		// Go to Next Scene
	case 'n':
	case 'N':
		if (SCENE_ID == 15)
			break;
		SCENE_ID++;
		break;
		// Quit Story
	case 'q':
	case 'Q':
		exit(0);
		break;
	case 's':
	case 'S':
		sky_r = 12, sky_g = 172, sky_b = 232,
		grass_r = 255, grass_g = 190, grass_b = 9,
		sun_r = 251, sun_g = 255, sun_b = 163;
		star_alpha = 0;
		stars_are_made = false;
	
			sun_move_left =0;
			
		break;
	case 'R':
	case 'r':
		if (SCENE_ID == 0) {
			if(traffic_r1 == 104 && traffic_g1 == 37 && traffic_b1 == 37 && traffic_r2 == 142&& traffic_g2 == 151&& traffic_b2 == 21&& traffic_r3 == 8&& traffic_g3 == 84&& traffic_b3 == 59 )
				traffic_r1 = 235, traffic_g1 = 85, traffic_b1 = 85;
			else if (traffic_r1 == 235 && traffic_g1 == 85 && traffic_b1 == 85 && traffic_r2 == 142 && traffic_g2 == 151 && traffic_b2 == 21 && traffic_r3 == 8 && traffic_g3 == 84 && traffic_b3 == 59) {
				traffic_r2 = 238, traffic_g2 = 253, traffic_b2 = 21;
				traffic_r1 = 104, traffic_g1 = 37, traffic_b1 = 37;
			}
			else if (traffic_r1 == 104 && traffic_g1 == 37 && traffic_b1 == 37 && traffic_r2 == 238 && traffic_g2 == 253 && traffic_b2 == 21 && traffic_r3 == 8 && traffic_g3 == 84 && traffic_b3 == 59) {
				traffic_r3 = 12, traffic_g3 = 176, traffic_b3 = 34;
				traffic_r2 = 142, traffic_g2 = 151, traffic_b2 = 21;

			}
			else {
				traffic_r1 = 235, traffic_g1 = 85, traffic_b1 = 85;
				traffic_r2 = 142, traffic_g2 = 151, traffic_b2 = 21;
				traffic_r3 = 8, traffic_g3 = 84, traffic_b3 = 59;
			}

		}
		break;
	case 'A':
	case 'a':
		glutTimerFunc(25, update, 0);
		sun_moved_half = false;
		sun_has_set = false;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

// Function to Initialize Screen
void initializeScreen() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1400, 0, 800); 
}

// Main Function
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1400, 800);
	glutCreateWindow("The Epilogue of Education");

	// Enables Transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Enable Smoothening
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Display Function
	glutDisplayFunc(renderScene);

	// Input Functions
	glutKeyboardFunc(keyPress);
	//glutMouseFunc(mouseClick);
	initializeScreen();
	//glutTimerFunc(25, update, 0);

	glutMainLoop();

	return 0;
}
