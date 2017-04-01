#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "node_termios.h"


/*
 * termios attributes
 */








/* TODO */
/*
void cfmakeraw(struct termios *termios_p);
speed_t cfgetispeed(const struct termios *termios_p);
speed_t cfgetospeed(const struct termios *termios_p);
int cfsetispeed(struct termios *termios_p, speed_t speed);
int cfsetospeed(struct termios *termios_p, speed_t speed);
int cfsetspeed(struct termios *termios_p, speed_t speed);
*/


//NODE_MODULE(termios, Termios::Init)


NAN_MODULE_INIT(init) {
  Nan::HandleScope scope;
  Nan::Set(target,
    Nan::New<String>("tcgetattr").ToLocalChecked(),
    Nan::New<FunctionTemplate>(TermiosTcgetattr)->GetFunction());
  Nan::Set(target,
    Nan::New<String>("tcsetattr").ToLocalChecked(),
    Nan::New<FunctionTemplate>(TermiosTcsetattr)->GetFunction());
  Nan::Set(target,
    Nan::New<String>("tcsendbreak").ToLocalChecked(),
    Nan::New<FunctionTemplate>(TermiosTcsendbreak)->GetFunction());
  Nan::Set(target,
    Nan::New<String>("tcdrain").ToLocalChecked(),
    Nan::New<FunctionTemplate>(TermiosTcdrain)->GetFunction());
  Nan::Set(target,
    Nan::New<String>("tcflush").ToLocalChecked(),
    Nan::New<FunctionTemplate>(TermiosTcflush)->GetFunction());
  Nan::Set(target,
    Nan::New<String>("tcflow").ToLocalChecked(),
    Nan::New<FunctionTemplate>(TermiosTcflow)->GetFunction());
  Nan::Set(target,
    Nan::New<String>("cfmakeraw").ToLocalChecked(),
    Nan::New<FunctionTemplate>(TermiosCfmakeraw)->GetFunction());

  _create_termios_symbol_maps();
}

NODE_MODULE(termios, init)