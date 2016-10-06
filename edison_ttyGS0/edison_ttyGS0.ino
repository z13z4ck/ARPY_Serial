/*
 * Serial echo for verifying communication with a PC based program
 * On Edison this can talk to a process on the host
 * if you setup socat to create some devices.
 */

 // V0.1:
//    - 

//Edison, setup ring buffer and TTYUARTClass
RingBuffer rx_buffer_S1;
TTYUARTClass mySerial(&rx_buffer_S1, 3, false); 
long Bstate = 0;
int RecievedData = 0;

void setup() {
  // system("nohup socat pty,link=$HOME/tty0,raw,echo=0 pty,link=$HOME/tty1,raw,echo=0 &");
  // system("echo test > /dev/ttyGS0");
  //for Edison specify the host TTY to connect to

  mySerial.init_tty("/home/root/tty0"); 
  // mySerial.init_tty("/dev/ttyGS0");


  //now the mySerial instance can be treated just like any Serial instance
  mySerial.begin(115200);

  

  // mySerial.write("Starting Balacing Stick\n");
  // mySerial.write("Please insert the command to start the operation!");
  
}


void loop()
{
  
  if (mySerial.available()){
    RecievedData = PyComs(RecievedData);
  }
  // mySerial.write("TETSETSETSET\naaaaaa\n");
  // mySerial.write("A");
  // if(mySerial.available()) {
  //   char in = mySerial.read();
  //   switch (in) {
  //       case 'A':
  //         mySerial.write("Input is A");
  //         // do something
  //         break;
  //       case 'B':
  //         mySerial.write("Input is B");

  //         // do something
  //         break;
  //       // default:
  //         // do something
  //   }
  // }
  // delay(500);
}

int DataNotSent = 0;
long PyComs(long sendData){
  //send data to host
  if(DataNotSent != 1) mySerial.write(sendData);
  
  DataNotSent = 0;
  long RecievedData = 0;

  //recieve data from host
  if (mySerial.available()){
      RecievedData = mySerial.read();
    }
  else DataNotSent = 1;

  return RecievedData;
}

