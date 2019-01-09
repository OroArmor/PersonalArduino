int tick = 0;
int waitDelay = 30;
int redAv;
int blueAv;
int greenAv;
void setup() {
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(A3, INPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  tick++;
  if (tick%waitDelay == 0) {
    int errorFix = 255 / 6;
    writeColor(255 - errorFix * ((redAv) / (waitDelay)), 255 - errorFix * ((greenAv) / (waitDelay) ), 255 - errorFix * ((blueAv)  / (waitDelay) ));
    redAv = 0;
    greenAv = 0;
    blueAv = 0;
  }
  redAv += analogRead(A4);
  greenAv += analogRead(A3);
  blueAv += analogRead(A5);

  //writeColor(255,0,0);
}

void writeColor(int r, int g, int b) {

  if (r > 255) {
    r = 255;
  } else if (r < 0) {
    r = 0;
  }

  if (g > 255) {
    g = 255;
  } else if (g < 0) {
    g = 0;
  }

  if (b > 255) {
    b = 255;
  } else if (b < 0) {
    b = 0;
  }


  if (r == 0 && g == 0 && b == 0) {
    calculateRGB(tick/30 % 360);
    Serial.println(tick);
    return;
  }

//  Serial.println(r);
//  Serial.println(g);
//  Serial.println(b);
//  Serial.println();

  analogWrite(6, 255 - g);
  analogWrite(5, 255 - r);
  analogWrite(3, 255 - b);
}


void calculateRGB(double angle) {

  if (angle < 0) {
    angle = 0;
  }

  double l = 0.5;
  double s = 1.0;

  double temp1 = l + s - l * s;
  double temp2 = 2.0 * l - temp1;

  double hue = angle / 360.0;
  double tempRed = hue + 0.333;
  double tempGreen = hue;
  double tempBlue = hue - 0.333;

  if (tempRed > 1) {
    tempRed -= 1;
  }

  if (tempBlue < 0) {
    tempBlue += 1;
  }

  double red = 0;
  if (6 * tempRed < 1) {
    red = temp2 + (temp1 - temp2) * 6.0 * tempRed;
  } else if (2 * tempRed < 1) {
    red = temp1;
  } else if (3 * tempRed < 2 ) {
    red = temp2 + (temp1 - temp2) * (0.666 - tempRed) * 6.0;
  } else {
    red = temp2;
  }

  double green = 0;

  if (6 * tempGreen < 1) {
    green = temp2 + (temp1 - temp2) * 6.0 * tempGreen;
  } else if (2 * tempGreen < 1) {
    green = temp1;
  } else if (3 * tempGreen < 2 ) {
    green = temp2 + (temp1 - temp2) * (0.666 - tempGreen) * 6.0;
  } else {
    green = temp2;
  }

  double blue = 0;

  if (6 * tempBlue < 1) {
    blue = temp2 + (temp1 - temp2) * 6.0 * tempBlue;
  } else if (2 * tempBlue < 1) {
    blue = temp1;
  } else if (3 * tempBlue < 2 ) {
    blue = temp2 + (temp1 - temp2) * (0.666 - tempBlue) * 6.0;
  } else {
    blue = temp2;
  }
  writeColor(red * 255.0, green * 255.0, blue * 255.0);

}
