#include <LPC21xx.H>


enum DetectorState {ACTIVE,INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo
{
enum ServoState eState;
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
};


void DetectorInit(void);
enum DetectorState eReadDetector(void);
void Automat(void);
void ServoCallib(void);
void ServoInit(unsigned int uiServoFrequency);
void ServoGoTo(unsigned int uiPosition);


