/*
** @method startComm
** @desc start serial port if DEBUG is defined
*/
void startComm()
{
  #ifdef DEBUG
    Serial.begin(115200);
    delay(1000);
  #endif
};

/*
** @method listenComm
** @desc listen to serial port if DEBUG is defined
*/
void listenComm()
{
  if(Serial.available() > 0)
  {
    String data = Serial.readStringUntil('\n');
    String message;
  }
};

/*
** @method printComm
** @param str (String)
** @desc print string to serial port if DEBUG is defined
*/
void printComm(String str)
{
  #ifdef DEBUG
    Serial.println(str);
  #endif
};
