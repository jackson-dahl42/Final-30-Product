unsigned char dinosaur1 [ ] = { 
  0b00111,
	0b01010,
	0b01111,
	0b01110,
	0b01110,
	0b11110,
	0b01110,
	0b00011 
};

unsigned char dinosaur2 [ ] = { 
  0b00111,
	0b01010,
	0b01111,
  0b01110,
	0b01110,
	0b11110,
	0b01011,
	0b01100 
};

unsigned char cactus [ ] = { 
  0b00100,
	0b10100,
	0b10100,
	0b10101,
	0b11101,
  0b00111,
	0b00100,
	0b00100
};

unsigned char bird1 [ ] = { 
  0b00000,
	0b00000,
	0b00000,
	0b01000,
	0b11111,
	0b00110,
	0b00110,
	0b00100 
};

unsigned char bird2 [ ] = {	
  0b00000,
	0b00100,
	0b00110,
	0b01110,
  0b11111,
	0b00000,
	0b00000,
	0b00000 
};

bool jumping = false;
char jump_count = 0;
char animation_count = 0;
int x, y;
int speed_count = 0;
int speed = 3;
int loop_count = 0;
bool second_cactus = false;
char dino = 0;
bool dino_animation = false;
char bird = 3;
bool bird_animation = false;
char dino_pos = 64;
char cactus1_pos = 79;
char cactus2_pos = 80;
signed char bird_pos = 22;
bool game_1 = true;
int score = 0;
bool game_console = true;
bool dino_game = false;
bool defender_game = false;
