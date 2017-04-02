/* termios_basic.cpp
 *
 * Copyright (C) 2017 Joerg Breitbart
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "termios_basic.h"
#include "CTermios.h"

NAN_METHOD(Isatty)
{
    Nan::HandleScope scope;
    if (info.Length() != 1 || !info[0]->IsNumber()) {
        return Nan::ThrowError("usage: termios.isatty(fd)");
    }
    int tty = isatty(info[0]->IntegerValue());
    if (!tty && errno == EBADF) {
        string error(strerror(errno));
        return Nan::ThrowError((string("isatty failed - ") + error).c_str());
    }
    info.GetReturnValue().Set(Nan::New<Boolean>(tty));
}


NAN_METHOD(Ttyname)
{
    Nan::HandleScope scope;
    if (info.Length() != 1 || !info[0]->IsNumber()) {
        return Nan::ThrowError("usage: termios.ttyname(fd)");
    }
    char *name = ttyname(info[0]->IntegerValue());
    info.GetReturnValue().Set(
        (name) ? Nan::New<String>(name).ToLocalChecked() : Nan::EmptyString());
}


NAN_METHOD(Ptsname)
{
    Nan::HandleScope scope;
    if (info.Length() != 1 || !info[0]->IsNumber()) {
        return Nan::ThrowError("usage: termios.ptsname(fd)");
    }
    char *name = ptsname(info[0]->IntegerValue());
    info.GetReturnValue().Set(
        (name) ? Nan::New<String>(name).ToLocalChecked() : Nan::EmptyString());
}


NAN_METHOD(Tcgetattr)
{
    Nan::HandleScope scope;
    if (info.Length() != 2
          || !info[0]->IsNumber()
          || !info[1]->IsObject()
          || !CTermios::IsInstance(info[1])) {
        return Nan::ThrowError("Usage: tcgetattr(fd, ctermios)");
    }
    struct termios *t = Nan::ObjectWrap::Unwrap<CTermios>(info[1]->ToObject())->data();
    if (tcgetattr(info[0]->IntegerValue(), t)) {
        string error(strerror(errno));
        return Nan::ThrowError((string("tcgetattr failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}

// FIXME: use int values instead of strings
NAN_METHOD(Tcsetattr)
{
    Nan::HandleScope scope;
    if (info.Length() != 3
          || !info[0]->IsNumber()
          || !info[1]->IsString()
          || !info[2]->IsObject()
          || !CTermios::IsInstance(info[2])) {
        return Nan::ThrowError("Usage: tcsetattr(fd, action, ctermios)");
    }
    string action_str(*static_cast<String::Utf8Value>(info[1]->ToString()));
    unordered_map<string, int>::iterator it;
    it = actions.find(action_str);
    if (it == actions.end())
        return Nan::ThrowError("action must be one of 'TCSANOW', 'TCSADRAIN', 'TCSAFLUSH'");
    int action = it->second;
    struct termios *t = Nan::ObjectWrap::Unwrap<CTermios>(info[2]->ToObject())->data();
    if (tcsetattr(info[0]->IntegerValue(), action, t)) {
        string error(strerror(errno));
        return Nan::ThrowError((string("tcsetattr failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}


NAN_METHOD(Tcsendbreak)
{
    Nan::HandleScope scope;
    if (info.Length() != 2
          || !info[0]->IsNumber()
          || !info[1]->IsNumber()) {
        return Nan::ThrowError("usage: termios.tcsendbreak(fd, duration)");
    }
    if (tcsendbreak(info[0]->IntegerValue(), info[1]->IntegerValue())) {
        string error(strerror(errno));
        return Nan::ThrowError((string("tcsendbreak failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}


NAN_METHOD(Tcdrain)
{
    Nan::HandleScope scope;
    if (info.Length() != 1 || !info[0]->IsNumber()) {
        return Nan::ThrowError("usage: termios.tcdrain(fd)");
    }
    if (tcdrain(info[0]->IntegerValue())) {
        string error(strerror(errno));
        return Nan::ThrowError((string("tcdrain failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}


// FIXME: use int values instead of strings
NAN_METHOD(Tcflush)
{
    Nan::HandleScope scope;
    if (info.Length() != 2
          || !info[0]->IsNumber()
          || !info[1]->IsString()) {
        return Nan::ThrowError("usage: termios.tcflush(fd, queue_selector)");
    }
    string queue_str(*static_cast<String::Utf8Value>(info[1]->ToString()));
    unordered_map<string, int>::iterator it;
    it = flushs.find(queue_str);
    if (it == flushs.end())
        return Nan::ThrowError("action must be one of 'TCIFLUSH', 'TCOFLUSH', 'TCIOFLUSH'");
    if (tcflush(info[0]->IntegerValue(), it->second)) {
        string error(strerror(errno));
        return Nan::ThrowError((string("tcflush failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}


// FIXME: use int values instead of strings
NAN_METHOD(Tcflow)
{
    Nan::HandleScope scope;
    if (info.Length() != 2
          || !info[0]->IsNumber()
          || !info[1]->IsString()) {
        return Nan::ThrowError("usage: termios.tcflow(fd, action)");
    }
    string action_str(*static_cast<String::Utf8Value>(info[1]->ToString()));
    unordered_map<string, int>::iterator it;
    it = flows.find(action_str);
    if (it == flows.end())
        return Nan::ThrowError("action must be one of 'TCOOFF', 'TCOON', 'TCIOFF', 'TCION'");
    if (tcflow(info[0]->IntegerValue(), it->second)) {
        string error(strerror(errno));
        return Nan::ThrowError((string("tcflow failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}

/*
speed_t cfgetispeed(const struct termios *termios_p);
speed_t cfgetospeed(const struct termios *termios_p);
int cfsetispeed(struct termios *termios_p, speed_t speed);
int cfsetospeed(struct termios *termios_p, speed_t speed);
*/
