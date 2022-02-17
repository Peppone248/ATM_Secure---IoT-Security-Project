const int RED_PIN = A7;
const int GREEN_PIN = A6;
const int BLUE_PIN = A8;

class RGBLed
{
  public:
  
    void setup() 
    {
      pinMode(RED_PIN, OUTPUT);
      pinMode(GREEN_PIN, OUTPUT);
      pinMode(BLUE_PIN, OUTPUT);
    }

    void color(unsigned char red, unsigned char green, unsigned char blue)
    {
      analogWrite(RED_PIN, red);
      analogWrite(GREEN_PIN, green);
      analogWrite(BLUE_PIN, blue);
    }
};