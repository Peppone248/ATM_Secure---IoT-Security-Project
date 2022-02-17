const int BUZZER_PIN = 7;

class Buzzer
{
  public:

    void setup() {
      pinMode(BUZZER_PIN, OUTPUT);
    }

    void activate(unsigned int frequency, unsigned long duration) 
    {
      tone(BUZZER_PIN, frequency, duration);
    }

    void deactivate() 
    {
      noTone(BUZZER_PIN);
    }
};