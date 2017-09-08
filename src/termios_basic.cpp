/* termios_basic.cpp
 *
 * Copyright (C) 2017 Joerg Breitbart
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "termios_basic.h"
#include "CTermios.h"
#include <errno.h>

NAN_METHOD(Isatty)
{
    Nan::HandleScope scope;
    if (info.Length() != 1 || !info[0]->IsNumber()) {
        return Nan::ThrowError("usage: termios.isatty(fd)");
    }
    int tty = isatty(info[0]->IntegerValue());
    if (!tty && errno == EBADF) {
        std::string error(strerror(errno));
        return Nan::ThrowError((std::string("isatty failed - ") + error).c_str());
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
    int res;
    TEMP_FAILURE_RETRY(res = tcgetattr(info[0]->IntegerValue(), t));
    if (res) {
        std::string error(strerror(errno));
        return Nan::ThrowError((std::string("tcgetattr failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}


NAN_METHOD(Tcsetattr)
{
    Nan::HandleScope scope;
    if (info.Length() != 3
          || !info[0]->IsNumber()
          || !info[1]->IsNumber()
          || !info[2]->IsObject()
          || !CTermios::IsInstance(info[2])) {
        return Nan::ThrowError("Usage: tcsetattr(fd, action, ctermios)");
    }
    struct termios *t = Nan::ObjectWrap::Unwrap<CTermios>(info[2]->ToObject())->data();
    int res;
    TEMP_FAILURE_RETRY(res = tcsetattr(info[0]->IntegerValue(), info[1]->IntegerValue(), t));
    if (res) {
        std::string error(strerror(errno));
        return Nan::ThrowError((std::string("tcsetattr failed - ") + error).c_str());
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
    int res;
    TEMP_FAILURE_RETRY(res = tcsendbreak(info[0]->IntegerValue(), info[1]->IntegerValue()));
    if (res) {
        std::string error(strerror(errno));
        return Nan::ThrowError((std::string("tcsendbreak failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}


NAN_METHOD(Tcdrain)
{
    Nan::HandleScope scope;
    if (info.Length() != 1 || !info[0]->IsNumber()) {
        return Nan::ThrowError("usage: termios.tcdrain(fd)");
    }
    int res;
    TEMP_FAILURE_RETRY(res = tcdrain(info[0]->IntegerValue()));
    if (res) {
        std::string error(strerror(errno));
        return Nan::ThrowError((std::string("tcdrain failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}


NAN_METHOD(Tcflush)
{
    Nan::HandleScope scope;
    if (info.Length() != 2
          || !info[0]->IsNumber()
          || !info[1]->IsNumber()) {
        return Nan::ThrowError("usage: termios.tcflush(fd, queue_selector)");
    }
    int res;
    TEMP_FAILURE_RETRY(res = tcflush(info[0]->IntegerValue(), info[1]->IntegerValue()));
    if (res) {
        std::string error(strerror(errno));
        return Nan::ThrowError((std::string("tcflush failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}


NAN_METHOD(Tcflow)
{
    Nan::HandleScope scope;
    if (info.Length() != 2
          || !info[0]->IsNumber()
          || !info[1]->IsNumber()) {
        return Nan::ThrowError("usage: termios.tcflow(fd, action)");
    }
    int res;
    TEMP_FAILURE_RETRY(res = tcflow(info[0]->IntegerValue(), info[1]->IntegerValue()));
    if (res) {
        std::string error(strerror(errno));
        return Nan::ThrowError((std::string("tcflow failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}


NAN_METHOD(Cfgetispeed)
{
    Nan::HandleScope scope;
    if (info.Length() != 1
          || !info[0]->IsObject()
          || !CTermios::IsInstance(info[0])) {
        return Nan::ThrowError("usage: termios.cfgetispeed(ctermios)");
    }
    struct termios *t = Nan::ObjectWrap::Unwrap<CTermios>(info[0]->ToObject())->data();
    info.GetReturnValue().Set(Nan::New<Number>(cfgetispeed(t)));
}


NAN_METHOD(Cfgetospeed)
{
    Nan::HandleScope scope;
    if (info.Length() != 1
          || !info[0]->IsObject()
          || !CTermios::IsInstance(info[0])) {
        return Nan::ThrowError("usage: termios.cfgetospeed(ctermios)");
    }
    struct termios *t = Nan::ObjectWrap::Unwrap<CTermios>(info[0]->ToObject())->data();
    info.GetReturnValue().Set(Nan::New<Number>(cfgetospeed(t)));
}


NAN_METHOD(Cfsetispeed)
{
    Nan::HandleScope scope;
    if (info.Length() != 2
          || !info[0]->IsObject()
          || !CTermios::IsInstance(info[0])
          || !info[1]->IsNumber()) {
        return Nan::ThrowError("usage: termios.cfsetispeed(ctermios, speed)");
    }
    struct termios *t = Nan::ObjectWrap::Unwrap<CTermios>(info[0]->ToObject())->data();
    if (cfsetispeed(t, info[1]->IntegerValue())) {
        std::string error(strerror(errno));
        return Nan::ThrowError((std::string("cfsetispeed failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}


NAN_METHOD(Cfsetospeed)
{
    Nan::HandleScope scope;
    if (info.Length() != 2
          || !info[0]->IsObject()
          || !CTermios::IsInstance(info[0])
          || !info[1]->IsNumber()) {
        return Nan::ThrowError("usage: termios.cfsetospeed(ctermios, speed)");
    }
    struct termios *t = Nan::ObjectWrap::Unwrap<CTermios>(info[0]->ToObject())->data();
    if (cfsetospeed(t, info[1]->IntegerValue())) {
        std::string error(strerror(errno));
        return Nan::ThrowError((std::string("cfsetospeed failed - ") + error).c_str());
    }
    info.GetReturnValue().SetUndefined();
}

