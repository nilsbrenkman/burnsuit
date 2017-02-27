
/*
Infrared sender-receiver library using a simple pulse-length based protocol
The concept is conventional but the specific implementation does not relate to any standard protocol

notes:
- This is a very simple version and various generelizations could be implemented
- The code readability could be improved
- The data spead is quite close to the limits of the hardware
- The user is responsible to implement a method of calling listen() at the right moment (interrupt)
*/

#include "application.h"

class afrored
{
  private:
  bool tolcheck(int measured_pulse, int intended_pulse);
  int carrier_frequency;
  int pin_led;
  int pin_receiver;
  int msg_length;
  int num_bursts_start;
  int num_bursts_end;
  int num_bursts;
  
  
  std::vector<int> signal_in;
  static const std::array<int,2> BURST_LENGTH;
  static const std::array<int,4> START_SEQ;
  static const std::array<int,1> END_SEQ;
  static const int COOL_DOWN_TIME;
  static const int BURST_TIME_OUT;
  static const int PWM_RES;
  static const int PWM_DUTY;
  static const int TIME_TOL;

  public:
  afrored(const int msg_length, const int carrier_frequency);
  void attachreceiver(const int pin_receiver);
  void attachtransmitter(const int pin_receiver);
  void sendmsg(int data);
  void listen();
  bool checkmsg();
  int  getmsg();
  int  debugmsg();
  void printrawinput();
  bool isnewmsg;

};
