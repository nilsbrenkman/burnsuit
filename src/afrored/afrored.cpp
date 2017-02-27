#include "afrored.h"

// Currently the protocol is hard-coded here.
// It could be become more general by moving these variables to public member variables.
const std::array<int,2> afrored::BURST_LENGTH = {300,600};
const std::array<int,4> afrored::START_SEQ = {300,700,500,500};
const std::array<int,1> afrored::END_SEQ = {800};
const int afrored::COOL_DOWN_TIME = 450;
const int afrored::BURST_TIME_OUT = 1000;
const int afrored::PWM_RES = 8;
const int afrored::PWM_DUTY = 127;
const int afrored::TIME_TOL = 120;

afrored::afrored(const int msg_length, const int carrier_frequency) :
  carrier_frequency(carrier_frequency),
  msg_length(msg_length)
{
  num_bursts_start = START_SEQ.size();
  num_bursts_end =  END_SEQ.size();
  num_bursts = num_bursts_start + msg_length * 2 + num_bursts_end;

  // make sure no pin is used withouth attaching first
  pin_receiver = -1;
  pin_led = -1;
}

void afrored::attachreceiver(const int pin_receiver)
{
  this->pin_receiver = pin_receiver;
  isnewmsg = false;
  signal_in.reserve(num_bursts);
  std::fill(signal_in.begin(), signal_in.end(), 0);
  pinMode(pin_receiver, INPUT);
}

void afrored::attachtransmitter(const int pin_led)
{
  this->pin_led = pin_led;
  pinMode(pin_led, OUTPUT);
  analogWriteResolution(pin_led, PWM_RES);
}

void afrored::sendmsg(int data)
{
  // first we build the complete signal as one array filled with the on and off times
  std::vector<int> signal_out;
  signal_out.reserve(num_bursts);
  signal_out.insert(signal_out.end(), START_SEQ.begin(), START_SEQ.end() );
  for (int i = 0; i<msg_length; i++)
  {
    signal_out.push_back (BURST_LENGTH[(data >> i) & 1]);
    signal_out.push_back (COOL_DOWN_TIME);
  }
  signal_out.insert( signal_out.end(), END_SEQ.begin(), END_SEQ.end() );

  // here we send the data
  int high_low = 1;
  for (auto pulse : signal_out)
  {
      analogWrite(pin_led, high_low*PWM_DUTY, carrier_frequency);
      delayMicroseconds(pulse);
      high_low = (high_low + 1) % 2;
  }
  digitalWrite(pin_led, LOW);
}

void afrored::listen()
{
  isnewmsg = true;
  bool isreceiving = true;
  int burst_counter = 0;
  long time_now = micros();
  long time_last_change = micros();
  int input;
  int input_prev = digitalRead(pin_receiver);

  while(isreceiving)
  {
    input = digitalRead(pin_receiver);
    time_now = micros();
    if (time_now - time_last_change > BURST_TIME_OUT)
    {
      isreceiving = false;
    }
    if (input != input_prev)
    {
      signal_in[burst_counter] = time_now - time_last_change;
      time_last_change = time_now;
      burst_counter++;
      input_prev = input;
    }
    if (burst_counter == num_bursts)
    {
      isreceiving = false;
    }
  }
}

int afrored::debugmsg()
{
  isnewmsg = false;
  for (int i = 0; i < num_bursts_start; i++) // check start sequence
  {
    if(!tolcheck(signal_in[i], START_SEQ[i]))
      return -1;
  }
  for (int i = 0; i < num_bursts_end; i++) // check final sequence
  {
    if(!tolcheck(signal_in[num_bursts - num_bursts_end + i], END_SEQ[i]))
      return -2;
  }
  for (int i = 0; i < msg_length; i++) // check cool down pulses
  {
    if(!tolcheck(signal_in[num_bursts_start + 2*i + 1], COOL_DOWN_TIME))
      return -3;
  }
  for (int i = 0; i < msg_length; i++) // check data pulses
  {
    if(!tolcheck(signal_in[num_bursts_start + 2*i],BURST_LENGTH[0]) &&
       !tolcheck(signal_in[num_bursts_start + 2*i],BURST_LENGTH[1]))
      return -4;
  }
  return 1;
}

void afrored::printrawinput()
{
  for(int i = 0; i <num_bursts; i++)
  {
      Serial.print(signal_in[i]);
      Serial.print(",");
  }
  Serial.println(" ");
}

bool afrored::checkmsg()
{
  return (debugmsg() == 1);
}

int afrored::getmsg()
{
  isnewmsg = false;
  int data = 0;

  for (int i = 0; i < msg_length; i++)
  {
    // we only check the bits that are "1". the "0" bits require no action
    if(tolcheck(signal_in[num_bursts_start + 2*i],BURST_LENGTH[1]))
      data = data + (1 << i);
  }
  return data;
}

bool afrored::tolcheck(int measured_pulse, int intended_pulse)
{
  bool istoohigh = measured_pulse - TIME_TOL > intended_pulse;
  bool istoolow = measured_pulse + TIME_TOL < intended_pulse;
  return !istoohigh && !istoolow;
}
