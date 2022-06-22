unsigned char spaceship_bottom[] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b11000,
	0b01111,
	0b01111,
	0b11000
};

unsigned char spaceship_top[] = {
	0b11000,
	0b01111,
	0b01111,
	0b11000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

unsigned char asteroid_bottom[] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b01110,
	0b01110,
	0b00000
};

unsigned char asteroid_top[] = {
	0b00000,
	0b01110,
	0b01110,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

unsigned char laser_bottom[] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b10101,
	0b01010,
	0b00000
};

unsigned char laser_top[] = {
	0b00000,
	0b01010,
	0b10101,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};

int spaceship_x = 0;
int spaceship_y = 4;
int asteroid1_x = 15;
int asteroid1_y = 4;
int asteroid2_x = 20;
int asteroid2_y = 1;
int asteroid3_x = 25;
int asteroid3_y = 3; 
int laser_x;
int laser_y;
int laser_count = 0;
