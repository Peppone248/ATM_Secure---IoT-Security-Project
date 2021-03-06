///Define class for MQTT

#define debug
#define RESET_PIN 6
//#define OUT Serial

class SIM800L
{
private:
    int8_t mode = 0;
    int8_t sendATcommand(char *ATcommand, char *expected_answer, unsigned int timeout);
    Stream *OUT;

public:
    SIM800L();
    SIM800L(Stream &OUT);
    bool initialize(uint8_t mode, Stream *out);
    bool initModem();
    bool initNetwork();
    bool initGPRS();
    bool startTCP(char *servername, int port);
    bool closeTCP();
    bool setMode(uint8_t mode = 0);
    bool checkModem();
    bool checkNetwork();
    bool checkGPRS();
    bool getMACAddress();
    bool getIPAddress();
    short int getMode();
    void resetModem();
    char *getTCPStatus();
    void setAPN(char *APN, char *username, char *password);
    char *sendATCommandResponse(char *ATcommand, unsigned int timeout, char*response);
};
