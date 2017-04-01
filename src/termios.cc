#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "node_termios.h"




/*
 * some terminal helper functions
 */

NAN_METHOD(TermiosIsatty) {
  Nan::HandleScope scope;
  if (info.Length() != 1 || !info[0]->IsNumber()) {
    return Nan::ThrowError("usage: termios.isatty(fd)");
  }
  int tty = isatty(info[0]->IntegerValue());
  if (!tty && errno == EBADF) {
    string error(strerror(errno));
    return Nan::ThrowError((string("isatty failed - ") + error).c_str());
  }
  return info.GetReturnValue().Set(Nan::New<Boolean>(tty));
}


NAN_METHOD(TermiosTtyname) {
  Nan::HandleScope scope;
  if (info.Length() != 1 || !info[0]->IsNumber()) {
    return Nan::ThrowError("usage: termios.ttyname(fd)");
  }
  char *name = ttyname(info[0]->IntegerValue());
  return info.GetReturnValue().Set(
    (name) ? Nan::New<String>(name).ToLocalChecked() : Nan::EmptyString());
}


NAN_METHOD(TermiosPtsname) {
  Nan::HandleScope scope;
  if (info.Length() != 1 || !info[0]->IsNumber()) {
    return Nan::ThrowError("usage: termios.ptsname(fd)");
  }
  char *name = ptsname(info[0]->IntegerValue());
  return info.GetReturnValue().Set(
    (name) ? Nan::New<String>(name).ToLocalChecked() : Nan::EmptyString());
}


/*
 * termios attributes
 */

void _create_termios_symbol_maps() {
  // no platform switches here, simply test for existance of questionable symbols
  // checked OS: linux, FreeBSD (partly darwin compatible)
  // TODO: OSX - doc specifies FreeBSD definitions but not all are actually implemented
  // TODO: Solaris, others?

  // c_iflag
  TERMIOS_EXPORT(c_iflag, IGNBRK);
  TERMIOS_EXPORT(c_iflag, BRKINT);
  TERMIOS_EXPORT(c_iflag, IGNPAR);
  TERMIOS_EXPORT(c_iflag, PARMRK);
  TERMIOS_EXPORT(c_iflag, INPCK);
  TERMIOS_EXPORT(c_iflag, ISTRIP);
  TERMIOS_EXPORT(c_iflag, INLCR);
  TERMIOS_EXPORT(c_iflag, IGNCR);
  TERMIOS_EXPORT(c_iflag, ICRNL);
#if defined(IUCLC)
  TERMIOS_EXPORT(c_iflag, IUCLC);
#endif
  TERMIOS_EXPORT(c_iflag, IXON);
  TERMIOS_EXPORT(c_iflag, IXANY);
  TERMIOS_EXPORT(c_iflag, IXOFF);
  TERMIOS_EXPORT(c_iflag, IMAXBEL);
#if defined(IUTF8)
  TERMIOS_EXPORT(c_iflag, IUTF8);
#endif

  // c_oflag
  TERMIOS_EXPORT(c_oflag, OPOST);
#if defined(OLCUC)
  TERMIOS_EXPORT(c_oflag, OLCUC);
#endif
  TERMIOS_EXPORT(c_oflag, ONLCR);
  TERMIOS_EXPORT(c_oflag, OCRNL);
  TERMIOS_EXPORT(c_oflag, ONOCR);
  TERMIOS_EXPORT(c_oflag, ONLRET);
#if defined(OFILL)
  TERMIOS_EXPORT(c_oflag, OFILL);
#endif
#if defined(OFDEL)
  TERMIOS_EXPORT(c_oflag, OFDEL);
#endif
#if defined(NLDLY)
  TERMIOS_EXPORT(c_oflag, NLDLY);
#endif
#if defined(CRDLY)
  TERMIOS_EXPORT(c_oflag, CRDLY);
#endif
  TERMIOS_EXPORT(c_oflag, TABDLY);
#if defined(BSDLY)
  TERMIOS_EXPORT(c_oflag, BSDLY);
#endif
#if defined(VTDLY)
  TERMIOS_EXPORT(c_oflag, VTDLY);
#endif
#if defined(FFDLY)
  TERMIOS_EXPORT(c_oflag, FFDLY);
#endif
#if defined(TAB0)
  TERMIOS_EXPORT(c_oflag, TAB0);
#endif
#if defined(TAB3)
  TERMIOS_EXPORT(c_oflag, TAB3);
#endif
#if defined(ONOEOT)
  TERMIOS_EXPORT(c_oflag, ONOEOT);
#endif

  // c_cflag
#if defined(CBAUD)
  TERMIOS_EXPORT(c_cflag, CBAUD);
#endif
#if defined(CBAUDEX)
  TERMIOS_EXPORT(c_cflag, CBAUDEX);
#endif
  TERMIOS_EXPORT(c_cflag, CSIZE);
  TERMIOS_EXPORT(c_cflag, CS5);
  TERMIOS_EXPORT(c_cflag, CS6);
  TERMIOS_EXPORT(c_cflag, CS7);
  TERMIOS_EXPORT(c_cflag, CS8);
  TERMIOS_EXPORT(c_cflag, CSTOPB);
  TERMIOS_EXPORT(c_cflag, CREAD);
  TERMIOS_EXPORT(c_cflag, PARENB);
  TERMIOS_EXPORT(c_cflag, PARODD);
  TERMIOS_EXPORT(c_cflag, HUPCL);
  TERMIOS_EXPORT(c_cflag, CLOCAL);
#if defined(LOBLK)
  TERMIOS_EXPORT(c_cflag, LOBLK);
#endif
#if defined(CIBAUD)
  TERMIOS_EXPORT(c_cflag, CIBAUD);
#endif
#if defined(CMSPAR)
  TERMIOS_EXPORT(c_cflag, CMSPAR);
#endif
  TERMIOS_EXPORT(c_cflag, CRTSCTS);
#if defined(CCTS_OFLOW)
  TERMIOS_EXPORT(c_cflag, CCTS_OFLOW);
#endif
#if defined(CRTS_IFLOW)
  TERMIOS_EXPORT(c_cflag, CRTS_IFLOW);
#endif
#if defined(MDMBUF)
  TERMIOS_EXPORT(c_cflag, MDMBUF);
#endif

  // c_lflag
  TERMIOS_EXPORT(c_lflag, ISIG);
  TERMIOS_EXPORT(c_lflag, ICANON);
#if defined(XCASE)
  TERMIOS_EXPORT(c_lflag, XCASE);
#endif
  TERMIOS_EXPORT(c_lflag, ECHO);
  TERMIOS_EXPORT(c_lflag, ECHOE);
#if defined(ECHOK)
  TERMIOS_EXPORT(c_lflag, ECHOK);
#endif
  TERMIOS_EXPORT(c_lflag, ECHONL);
  TERMIOS_EXPORT(c_lflag, ECHOCTL);
  TERMIOS_EXPORT(c_lflag, ECHOPRT);
  TERMIOS_EXPORT(c_lflag, ECHOKE);
#if defined(DEFECHO)
  TERMIOS_EXPORT(c_lflag, DEFECHO);
#endif
  TERMIOS_EXPORT(c_lflag, FLUSHO);
  TERMIOS_EXPORT(c_lflag, NOFLSH);
  TERMIOS_EXPORT(c_lflag, TOSTOP);
  TERMIOS_EXPORT(c_lflag, PENDIN);
  TERMIOS_EXPORT(c_lflag, IEXTEN);
#if defined(ALTWERASE)
  TERMIOS_EXPORT(c_lflag, ALTWERASE);
#endif
#if defined(EXTPROC)
  TERMIOS_EXPORT(c_lflag, EXTPROC);
#endif
#if defined(NOKERNINFO)
  TERMIOS_EXPORT(c_lflag, NOKERNINFO);
#endif

  // c_cc
  TERMIOS_EXPORT(c_cc, VDISCARD);
#if defined(VDSUSP)
  TERMIOS_EXPORT(c_cc, VDSUSP);
#endif
  TERMIOS_EXPORT(c_cc, VEOF);
  TERMIOS_EXPORT(c_cc, VEOL);
  TERMIOS_EXPORT(c_cc, VEOL2);
  TERMIOS_EXPORT(c_cc, VERASE);
  TERMIOS_EXPORT(c_cc, VINTR);
  TERMIOS_EXPORT(c_cc, VKILL);
  TERMIOS_EXPORT(c_cc, VLNEXT);
  TERMIOS_EXPORT(c_cc, VMIN);
  TERMIOS_EXPORT(c_cc, VQUIT);
  TERMIOS_EXPORT(c_cc, VREPRINT);
  TERMIOS_EXPORT(c_cc, VSTART);
#if defined(VSTATUS)
  TERMIOS_EXPORT(c_cc, VSTATUS);
#endif
  TERMIOS_EXPORT(c_cc, VSTOP);
  TERMIOS_EXPORT(c_cc, VSUSP);
#if defined(VSWTCH)
  TERMIOS_EXPORT(c_cc, VSWTCH);
#endif
  TERMIOS_EXPORT(c_cc, VTIME);
  TERMIOS_EXPORT(c_cc, VWERASE);

  // optional_actions
  TERMIOS_EXPORT(actions, TCSANOW);
  TERMIOS_EXPORT(actions, TCSADRAIN);
  TERMIOS_EXPORT(actions, TCSAFLUSH);

  // tcflush queue_selectors
  TERMIOS_EXPORT(flushs, TCIFLUSH);
  TERMIOS_EXPORT(flushs, TCOFLUSH);
  TERMIOS_EXPORT(flushs, TCIOFLUSH);

  // tcflow actions
  TERMIOS_EXPORT(flows, TCOOFF);
  TERMIOS_EXPORT(flows, TCOON);
  TERMIOS_EXPORT(flows, TCIOFF);
  TERMIOS_EXPORT(flows, TCION);
}


NAN_METHOD(TermiosTcgetattr) {
  Nan::HandleScope scope;

  struct termios t = termios();

  if (info.Length() == 1) {
    if (info[0]->IsNumber()) {
      if (tcgetattr(info[0]->IntegerValue(), &t)) {
        string error(strerror(errno));
        return Nan::ThrowError((string("tcgetattr failed - ") + error).c_str());
      }
    } else if (!info[0]->IsNull()) {
      return Nan::ThrowError("Usage: pty.tcgetattr(fd|null)");
    }
  }

  Local<Object> obj = Nan::New<Object>();

  Local<Object> js_c_iflag = Nan::New<Object>();
  for (auto &entry: c_iflag) {
    Nan::Set(js_c_iflag,
      Nan::New<String>(entry.first).ToLocalChecked(),
      Nan::New<Boolean>(t.c_iflag & entry.second));
  }
  Nan::Set(obj,
    Nan::New<String>("c_iflag").ToLocalChecked(), js_c_iflag);

  Local<Object> js_c_oflag = Nan::New<Object>();
    for (auto &entry: c_oflag) {
      Nan::Set(js_c_oflag,
        Nan::New<String>(entry.first).ToLocalChecked(),
        Nan::New<Boolean>(t.c_oflag & entry.second));
    }
  Nan::Set(obj,
    Nan::New<String>("c_oflag").ToLocalChecked(), js_c_oflag);

  Local<Object> js_c_cflag = Nan::New<Object>();
    for (auto &entry: c_cflag) {
      Nan::Set(js_c_cflag,
        Nan::New<String>(entry.first).ToLocalChecked(),
        Nan::New<Boolean>(t.c_cflag & entry.second));
    }
  Nan::Set(obj,
    Nan::New<String>("c_cflag").ToLocalChecked(), js_c_cflag);

  Local<Object> js_c_lflag = Nan::New<Object>();
    for (auto &entry: c_lflag) {
      Nan::Set(js_c_lflag,
        Nan::New<String>(entry.first).ToLocalChecked(),
        Nan::New<Boolean>(t.c_lflag & entry.second));
    }
  Nan::Set(obj,
    Nan::New<String>("c_lflag").ToLocalChecked(), js_c_lflag);

  Local<Object> js_c_cc = Nan::New<Object>();
    for (auto &entry: c_cc) {
      uint16_t ti = t.c_cc[entry.second];
      if ((entry.second == VMIN) || (entry.second == VTIME)) {
        Nan::Set(js_c_cc,
          Nan::New<String>(entry.first).ToLocalChecked(),
          Nan::New<Number>(ti));
      } else {
        Nan::Set(js_c_cc,
          Nan::New<String>(entry.first).ToLocalChecked(),
          Nan::New<String>(&ti, 1).ToLocalChecked());
      }
    }
  Nan::Set(obj,
    Nan::New<String>("c_cc").ToLocalChecked(), js_c_cc);

  return info.GetReturnValue().Set(obj);
}


inline void _set_termios_flag_t(v8::Local<v8::Object> &obj, flag_t *mapper, tcflag_t *part) {
  Nan::MaybeLocal<v8::Array> maybe_obj_keys(Nan::GetOwnPropertyNames(obj));
  if (maybe_obj_keys.IsEmpty())
    return;
  v8::Local<v8::Array> objkeys(maybe_obj_keys.ToLocalChecked());
  int objlength = objkeys->Length();
  for (int j=0; j<objlength; ++j) {
    string objkey(*static_cast<v8::String::Utf8Value>(objkeys->Get(j)));
    flag_t::iterator it = mapper->find(objkey);
    if (it != mapper->end()) {
      v8::Local<v8::Value> v(obj->Get(objkeys->Get(j)));
      if (!v->IsBoolean())
        continue;
      if (v->ToBoolean()->Value())
        *part |= it->second;
      else
        *part &= ~it->second;
    }
  }
}


inline void _set_termios_c_cc(v8::Local<v8::Object> &obj,
                              unordered_map<string, unsigned int> *mapper,
                              cc_t *part) {
  Nan::MaybeLocal<v8::Array> maybe_obj_keys(Nan::GetOwnPropertyNames(obj));
  if (maybe_obj_keys.IsEmpty())
    return;
  v8::Local<v8::Array> objkeys(maybe_obj_keys.ToLocalChecked());
  int objlength = objkeys->Length();
  for (int j=0; j<objlength; ++j) {
    string objkey(*static_cast<v8::String::Utf8Value>(objkeys->Get(j)));
    unordered_map<string, unsigned int>::iterator it = mapper->find(objkey);
    if (it != mapper->end()) {
      v8::Local<v8::Value> v(obj->Get(objkeys->Get(j)));
      uint16_t value;
      if (!v->IsString()) {
        if ((objkey != "VMIN") && (objkey != "VTIME"))
          continue;
        if (!v->IsNumber())
          continue;
        value = v->Uint32Value();
      } else {
        v8::String::Value v8_value(v->ToString());
        if (v8_value.length() != 1)
          continue;
        value = *((uint16_t *) *v8_value);
      }
      if (value>>8)
        continue;
      *(part+it->second) = (cc_t) value;
    }
  }
}


NAN_METHOD(TermiosTcsetattr) {
  Nan::HandleScope scope;

  if (info.Length() != 3
      || !info[0]->IsNumber()
      || !info[1]->IsObject()
      || !info[2]->IsString()) {
    return Nan::ThrowError("usage: pty.tcsetattr(fd, attrs, action)");
  }

  // get all parameters
  int fd = info[0]->IntegerValue();
  v8::Local<v8::Object> attrs(info[1]->ToObject());
  string action_str(*static_cast<v8::String::Utf8Value>(info[2]->ToString()));
  unordered_map<string, int>::iterator it;
  it = actions.find(action_str);
  if (it == actions.end())
    return Nan::ThrowError("action must be one of 'TCSANOW', 'TCSADRAIN', 'TCSAFLUSH'");
  int action = it->second;

  // prepare termios struct
  struct termios t = termios();

  // to allow subsets in attrs prepopulate with current attributes
  if (tcgetattr(fd, &t)) {
    string error(strerror(errno));
    return Nan::ThrowError((string("tcgetattr failed - ") + error).c_str());
  }

  // get attrs properties
  Nan::MaybeLocal<v8::Array> maybe_keys(Nan::GetOwnPropertyNames(attrs));
  if (maybe_keys.IsEmpty())
    return;
  v8::Local<v8::Array> keys(maybe_keys.ToLocalChecked());
  int length = keys->Length();

  // walk over properties and set matching values
  for (int i=0; i<length; ++i) {
    v8::Local<v8::Value> value(attrs->Get(keys->Get(i)));
    if (!value->IsObject())
      continue;
    v8::Local<v8::Object> obj(value->ToObject());

    // make sure only known struct fields are handled
    string key(*static_cast<v8::String::Utf8Value>(keys->Get(i)));
    if (key == "c_cc") {
      _set_termios_c_cc(obj, &c_cc, &t.c_cc[0]);
    } else if (key == "c_iflag") {
      _set_termios_flag_t(obj, &c_iflag, &t.c_iflag);
    } else if (key == "c_oflag") {
      _set_termios_flag_t(obj, &c_oflag, &t.c_oflag);
    } else if (key == "c_cflag") {
      _set_termios_flag_t(obj, &c_cflag, &t.c_cflag);
    } else if (key == "c_lflag") {
      _set_termios_flag_t(obj, &c_lflag, &t.c_lflag);
    }
  }

  // finally set the attributes
  if (tcsetattr(fd, action, &t)) {
    string error(strerror(errno));
    return Nan::ThrowError((string("tcsetattr failed - ") + error).c_str());
  }
}


// FIXME: respect errors
NAN_METHOD(TermiosTcsendbreak) {
  Nan::HandleScope scope;
  if (info.Length() != 2 || !info[0]->IsNumber() || !info[1]->IsNumber()) {
    return Nan::ThrowError("usage: termios.tcsendbreak(fd, duration)");
  }
  tcsendbreak(info[0]->IntegerValue(), info[1]->IntegerValue());
}


// FIXME: respect errors
NAN_METHOD(TermiosTcdrain) {
  Nan::HandleScope scope;
  if (info.Length() != 1 || !info[0]->IsNumber()) {
    return Nan::ThrowError("usage: termios.tcdrain(fd)");
  }
  tcdrain(info[0]->IntegerValue());
}


// FIXME: respect errors
NAN_METHOD(TermiosTcflush) {
  Nan::HandleScope scope;
  if (info.Length() != 2 || !info[0]->IsNumber() || !info[1]->IsString()) {
    return Nan::ThrowError("usage: termios.tcflush(fd, queue_selector)");
  }
  string queue_str(*static_cast<v8::String::Utf8Value>(info[1]->ToString()));
  unordered_map<string, int>::iterator it;
  it = flushs.find(queue_str);
  if (it == flushs.end())
    return Nan::ThrowError("action must be one of 'TCIFLUSH', 'TCOFLUSH', 'TCIOFLUSH'");
  tcflush(info[0]->IntegerValue(), it->second);
}


// FIXME: respect errors
NAN_METHOD(TermiosTcflow) {
  Nan::HandleScope scope;
  if (info.Length() != 2 || !info[0]->IsNumber() || !info[1]->IsString()) {
    return Nan::ThrowError("usage: termios.tcflow(fd, action)");
  }
  string action_str(*static_cast<v8::String::Utf8Value>(info[1]->ToString()));
  unordered_map<string, int>::iterator it;
  it = flows.find(action_str);
  if (it == flows.end())
    return Nan::ThrowError("action must be one of 'TCOOFF', 'TCOON', 'TCIOFF', 'TCION'");
  tcflow(info[0]->IntegerValue(), it->second);
}

#include <iostream>
// FIXME: respect errors
/*
----------> how to do this one?
*/
NAN_METHOD(TermiosCfmakeraw) {
  Nan::HandleScope scope;
  if (info.Length() != 1 || !info[0]->IsObject()) {
    return Nan::ThrowError("usage: termios.cfmakeraw(attrs)");
  }

  v8::Local<v8::Object> attrs(info[0]->ToObject());

  // prepare termios struct
  struct termios t = termios();

  // get attrs properties
  Nan::MaybeLocal<v8::Array> maybe_keys(Nan::GetOwnPropertyNames(attrs));
  if (maybe_keys.IsEmpty())
    return;
  v8::Local<v8::Array> keys(maybe_keys.ToLocalChecked());
  int length = keys->Length();

  // walk over properties and set matching values
  for (int i=0; i<length; ++i) {
    v8::Local<v8::Value> value(attrs->Get(keys->Get(i)));
    if (!value->IsObject())
      continue;
    v8::Local<v8::Object> obj(value->ToObject());

    // make sure only known struct fields are handled
    string key(*static_cast<v8::String::Utf8Value>(keys->Get(i)));
    if (key == "c_cc") {
      _set_termios_c_cc(obj, &c_cc, &t.c_cc[0]);
    } else if (key == "c_iflag") {
      _set_termios_flag_t(obj, &c_iflag, &t.c_iflag);
    } else if (key == "c_oflag") {
      _set_termios_flag_t(obj, &c_oflag, &t.c_oflag);
    } else if (key == "c_cflag") {
      _set_termios_flag_t(obj, &c_cflag, &t.c_cflag);
    } else if (key == "c_lflag") {
      _set_termios_flag_t(obj, &c_lflag, &t.c_lflag);
    }
  }

  // apply cfmakeraw
  cfmakeraw(&t);

  // return new attrs
  Local<Object> obj = Nan::New<Object>();

  Local<Object> js_c_iflag = Nan::New<Object>();
  for (auto &entry: c_iflag) {
    Nan::Set(js_c_iflag,
      Nan::New<String>(entry.first).ToLocalChecked(),
      Nan::New<Boolean>(t.c_iflag & entry.second));
  }
  Nan::Set(obj,
    Nan::New<String>("c_iflag").ToLocalChecked(), js_c_iflag);

  Local<Object> js_c_oflag = Nan::New<Object>();
    for (auto &entry: c_oflag) {
      Nan::Set(js_c_oflag,
        Nan::New<String>(entry.first).ToLocalChecked(),
        Nan::New<Boolean>(t.c_oflag & entry.second));
    }
  Nan::Set(obj,
    Nan::New<String>("c_oflag").ToLocalChecked(), js_c_oflag);

  Local<Object> js_c_cflag = Nan::New<Object>();
    for (auto &entry: c_cflag) {
      Nan::Set(js_c_cflag,
        Nan::New<String>(entry.first).ToLocalChecked(),
        Nan::New<Boolean>(t.c_cflag & entry.second));
    }
  Nan::Set(obj,
    Nan::New<String>("c_cflag").ToLocalChecked(), js_c_cflag);

  Local<Object> js_c_lflag = Nan::New<Object>();
    for (auto &entry: c_lflag) {
      Nan::Set(js_c_lflag,
        Nan::New<String>(entry.first).ToLocalChecked(),
        Nan::New<Boolean>(t.c_lflag & entry.second));
    }
  Nan::Set(obj,
    Nan::New<String>("c_lflag").ToLocalChecked(), js_c_lflag);

  Local<Object> js_c_cc = Nan::New<Object>();
    for (auto &entry: c_cc) {
      uint16_t ti = t.c_cc[entry.second];
      if ((entry.second == VMIN) || (entry.second == VTIME)) {
        Nan::Set(js_c_cc,
          Nan::New<String>(entry.first).ToLocalChecked(),
          Nan::New<Number>(ti));
      } else {
        Nan::Set(js_c_cc,
          Nan::New<String>(entry.first).ToLocalChecked(),
          Nan::New<String>(&ti, 1).ToLocalChecked());
      }
    }
  Nan::Set(obj,
    Nan::New<String>("c_cc").ToLocalChecked(), js_c_cc);

  return info.GetReturnValue().Set(obj);
}


/* TODO */
/*
void cfmakeraw(struct termios *termios_p);
speed_t cfgetispeed(const struct termios *termios_p);
speed_t cfgetospeed(const struct termios *termios_p);
int cfsetispeed(struct termios *termios_p, speed_t speed);
int cfsetospeed(struct termios *termios_p, speed_t speed);
int cfsetspeed(struct termios *termios_p, speed_t speed);
*/

class Termios;

class IFlag: public Nan::ObjectWrap {
friend Termios;
public:
  static v8::Local<v8::FunctionTemplate> init() {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("IFlag").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    tmpl().Reset(tpl);
    return tpl;
  }
private:
  explicit IFlag(tcflag_t *flag) : value_(flag) {}
  ~IFlag() {}

  static NAN_METHOD(New) {
    if (info.IsConstructCall()) {
      IFlag *obj = new IFlag(nullptr);
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {

    }
  }
  static inline Nan::Persistent<v8::Function> & constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }
  static inline Nan::Persistent<v8::FunctionTemplate> & tmpl() {
    static Nan::Persistent<v8::FunctionTemplate> my_template;
    return my_template;
  }
  tcflag_t *value_;
};

class CCBuffer: public Nan::ObjectWrap {
friend Termios;
public:
  static v8::Local<v8::FunctionTemplate> init() {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("CCBuffer").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "toBuffer", ToBuffer);

    Nan::SetIndexedPropertyHandler(
      tpl->InstanceTemplate(),
      IndexGetter,
      IndexSetter,
      IndexQuery,
      IndexDeleter,
      IndexEnumerator
    );
    Nan::SetAccessor(
          tpl->InstanceTemplate(),
          Nan::New<String>("length").ToLocalChecked(),
          (Nan::GetterCallback) (
            [] (v8::Local<v8::String> property,
                const Nan::PropertyCallbackInfo<v8::Value>& info) {
              CCBuffer *obj = Nan::ObjectWrap::Unwrap<CCBuffer>(info.Holder());
              info.GetReturnValue().Set(Nan::New<Number>(obj->length_));
            }),
          nullptr,
          Nan::New<v8::Value>(Nan::New<Number>(0)),
          v8::DEFAULT,
          v8::PropertyAttribute::DontDelete
        );

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    tmpl().Reset(tpl);
    return tpl;
  }
private:
  explicit CCBuffer(cc_t *value, int length) : value_(value), length_(length) {}
  ~CCBuffer() {}

  static NAN_METHOD(New) {
    if (info.IsConstructCall()) {
      CCBuffer *obj = new CCBuffer(nullptr, 0);
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      int argc = info.Length();
      v8::Local<v8::Value> argv[argc];
      for (int i=0; i<argc; ++i)
        argv[i] = info[i];
      info.GetReturnValue().Set(Nan::New(constructor())->NewInstance(argc, argv));
    }
  }
  static inline Nan::Persistent<v8::Function> & constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }
  static inline Nan::Persistent<v8::FunctionTemplate> & tmpl() {
    static Nan::Persistent<v8::FunctionTemplate> my_template;
    return my_template;
  }
  static NAN_METHOD(ToBuffer) {
    CCBuffer* obj = Nan::ObjectWrap::Unwrap<CCBuffer>(info.Holder());
    info.GetReturnValue().Set(Nan::CopyBuffer((const char *) obj->value_, obj->length_).ToLocalChecked());
  }

  static NAN_INDEX_GETTER(IndexGetter) {
    CCBuffer* obj = Nan::ObjectWrap::Unwrap<CCBuffer>(info.Holder());
    if (index >= obj->length_)
      return;
    info.GetReturnValue().Set(Nan::New<Number>(obj->value_[index]));
  }

  static NAN_INDEX_SETTER(IndexSetter) {
    CCBuffer* obj = Nan::ObjectWrap::Unwrap<CCBuffer>(info.Holder());
    if (index < obj->length_ && value->IsNumber()) {
      obj->value_[index] = (cc_t) value->Uint32Value();
      info.GetReturnValue().Set(Nan::New<Number>(obj->value_[index]));
    } else
      info.GetReturnValue().SetUndefined();
  }

  static NAN_INDEX_ENUMERATOR(IndexEnumerator) {
    CCBuffer* obj = Nan::ObjectWrap::Unwrap<CCBuffer>(info.Holder());
    v8::Local<v8::Array> arr(Nan::New<Array>(obj->length_));
    for (int i=0; i<obj->length_; ++i)
      arr->Set(i, Nan::New<Number>(i));
    info.GetReturnValue().Set(arr);
  }

  static NAN_INDEX_DELETER(IndexDeleter) {
    info.GetReturnValue().Set(Nan::New<Boolean>(0));
  }

  static NAN_INDEX_QUERY(IndexQuery) {
    // TODO
  }

  cc_t *value_;
  unsigned int length_;
};


class Termios : public Nan::ObjectWrap {
 public:
  static v8::Local<v8::FunctionTemplate> init() {
    v8::Local<v8::FunctionTemplate> TermiosTpl = Nan::New<v8::FunctionTemplate>(New);
    TermiosTpl->SetClassName(Nan::New("Termios").ToLocalChecked());
    TermiosTpl->InstanceTemplate()->SetInternalFieldCount(3);

    // register methods
    Nan::SetPrototypeMethod(TermiosTpl, "toBuffer", ToBuffer);

    // register properties

    Nan::SetAccessor(
      TermiosTpl->InstanceTemplate(),
      Nan::New<String>("c_cc").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (v8::Local<v8::String> property,
            const Nan::PropertyCallbackInfo<v8::Value>& info) {
          Termios *obj = Nan::ObjectWrap::Unwrap<Termios>(info.Holder());
          info.GetReturnValue().Set(Nan::New(obj->ccbuffer));
        }),
        nullptr,
      Nan::New<v8::Value>(Nan::New<Number>(0)),
      v8::DEFAULT,
      static_cast<v8::PropertyAttribute>(v8::PropertyAttribute::DontDelete | v8::PropertyAttribute::ReadOnly)
    );
    Nan::SetAccessor(
      TermiosTpl->InstanceTemplate(),
      Nan::New<String>("c_lflag").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (v8::Local<v8::String> property,
            const Nan::PropertyCallbackInfo<v8::Value>& info) {
          Termios *obj = Nan::ObjectWrap::Unwrap<Termios>(info.Holder());
          info.GetReturnValue().Set(Nan::New<Number>(obj->value_.c_lflag));
        }),
      (Nan::SetterCallback) (
        [] (v8::Local<v8::String> property,
            v8::Local<v8::Value> value,
            const Nan::PropertyCallbackInfo<void>& info) {
          Termios *obj = Nan::ObjectWrap::Unwrap<Termios>(info.Holder());
          obj->value_.c_lflag = (tcflag_t) value->Uint32Value();
        }),
      Nan::New<v8::Value>(Nan::New<Number>(0)),
      v8::DEFAULT,
      v8::PropertyAttribute::DontDelete
    );
    Nan::SetAccessor(
      TermiosTpl->InstanceTemplate(),
      Nan::New<String>("c_cflag").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (v8::Local<v8::String> property,
            const Nan::PropertyCallbackInfo<v8::Value>& info) {
          Termios *obj = Nan::ObjectWrap::Unwrap<Termios>(info.Holder());
          info.GetReturnValue().Set(Nan::New<Number>(obj->value_.c_cflag));
        }),
      (Nan::SetterCallback) (
        [] (v8::Local<v8::String> property,
            v8::Local<v8::Value> value,
            const Nan::PropertyCallbackInfo<void>& info) {
          Termios *obj = Nan::ObjectWrap::Unwrap<Termios>(info.Holder());
          obj->value_.c_cflag = (tcflag_t) value->Uint32Value();
        }),
      Nan::New<v8::Value>(Nan::New<Number>(0)),
      v8::DEFAULT,
      v8::PropertyAttribute::DontDelete
    );
    Nan::SetAccessor(
      TermiosTpl->InstanceTemplate(),
      Nan::New<String>("c_oflag").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (v8::Local<v8::String> property,
            const Nan::PropertyCallbackInfo<v8::Value>& info) {
          Termios *obj = Nan::ObjectWrap::Unwrap<Termios>(info.Holder());
          info.GetReturnValue().Set(Nan::New<Number>(obj->value_.c_oflag));
        }),
      (Nan::SetterCallback) (
        [] (v8::Local<v8::String> property,
            v8::Local<v8::Value> value,
            const Nan::PropertyCallbackInfo<void>& info) {
          Termios *obj = Nan::ObjectWrap::Unwrap<Termios>(info.Holder());
          obj->value_.c_oflag = (tcflag_t) value->Uint32Value();
        }),
      Nan::New<v8::Value>(Nan::New<Number>(0)),
      v8::DEFAULT,
      v8::PropertyAttribute::DontDelete
    );
    Nan::SetAccessor(
      TermiosTpl->InstanceTemplate(),
      Nan::New<String>("c_iflag").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (v8::Local<v8::String> property,
            const Nan::PropertyCallbackInfo<v8::Value>& info) {
          Termios *obj = Nan::ObjectWrap::Unwrap<Termios>(info.Holder());
          info.GetReturnValue().Set(Nan::New<Number>(obj->value_.c_iflag));
        }),
      (Nan::SetterCallback) (
        [] (v8::Local<v8::String> property,
            v8::Local<v8::Value> value,
            const Nan::PropertyCallbackInfo<void>& info) {
          Termios *obj = Nan::ObjectWrap::Unwrap<Termios>(info.Holder());
          obj->value_.c_iflag = (tcflag_t) value->Uint32Value();
        }),
      Nan::New<v8::Value>(Nan::New<Number>(0)),
      v8::DEFAULT,
      v8::PropertyAttribute::DontDelete
    );

    constructor().Reset(Nan::GetFunction(TermiosTpl).ToLocalChecked());
    tmpl().Reset(TermiosTpl);

    return TermiosTpl;
  }

 private:
  explicit Termios(struct termios *value = nullptr) : value_() {
    if (value)
      memcpy(&value_, value, sizeof(*value));
  }
  ~Termios() {
    ccbuffer.Reset();
  }

  static NAN_METHOD(New) {
    if (info.IsConstructCall()) {

      // allow other Termios object as parameter
      struct termios *old = nullptr;
      if (info.Length() > 1)
        return Nan::ThrowError("to many arguments");
      if (!info[0]->IsUndefined()) {
        if (!info[0]->IsObject() || !Nan::New(Termios::tmpl())->HasInstance(info[0]))
          return Nan::ThrowError("first argument must be Termios type");
        old = &Nan::ObjectWrap::Unwrap<Termios>(info[0]->ToObject())->value_;
      }

            struct termios t = termios();
            tcgetattr(0, &t);
            Termios *obj = new Termios(&t);

      //Termios *obj = new Termios(old);
      obj->iflag = new IFlag(&obj->value_.c_iflag);

      // set c_cc as CCBuffer
      v8::Local<v8::Function> ctor_buf = Nan::GetFunction(CCBuffer::init()).ToLocalChecked();
      v8::Local<v8::Object> buf = Nan::NewInstance(ctor_buf).ToLocalChecked();
      obj->ccbuffer.Reset(buf);
      // CCBuffer values
      CCBuffer *cbuf = Nan::ObjectWrap::Unwrap<CCBuffer>(buf);
      cbuf->value_ = obj->value_.c_cc;
      cbuf->length_ = NCCS;

      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      int argc = info.Length();
      v8::Local<v8::Value> argv[argc];
      for (int i=0; i<argc; ++i)
        argv[i] = info[i];
      info.GetReturnValue().Set(Nan::New(constructor())->NewInstance(argc, argv));
    }
  }

  static NAN_METHOD(ToBuffer) {
    Termios* obj = Nan::ObjectWrap::Unwrap<Termios>(info.Holder());
    info.GetReturnValue().Set(Nan::CopyBuffer((const char *) &obj->value_, sizeof(obj->value_)).ToLocalChecked());
  }

  static inline Nan::Persistent<v8::Function> & constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }
  static inline Nan::Persistent<v8::FunctionTemplate> & tmpl() {
    static Nan::Persistent<v8::FunctionTemplate> my_template;
    return my_template;
  }

  struct termios value_;
  IFlag *iflag;
  //CCBuffer *ccbuffer;
  //v8::Local<v8::Object> ccbuffer;
  Nan::Persistent<v8::Object> ccbuffer;
};


//NODE_MODULE(termios, Termios::Init)


NAN_MODULE_INIT(init) {
  Nan::HandleScope scope;
  Nan::Set(target,
    Nan::New<String>("isatty").ToLocalChecked(),
    Nan::New<FunctionTemplate>(TermiosIsatty)->GetFunction());
  Nan::Set(target,
    Nan::New<String>("ttyname").ToLocalChecked(),
    Nan::New<FunctionTemplate>(TermiosTtyname)->GetFunction());
  Nan::Set(target,
    Nan::New<String>("ptsname").ToLocalChecked(),
    Nan::New<FunctionTemplate>(TermiosPtsname)->GetFunction());
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

  // objects
  Nan::Set(target, Nan::New("Termios").ToLocalChecked(),
    Nan::GetFunction(Termios::init()).ToLocalChecked());
  Nan::Set(target, Nan::New("CCBuffer").ToLocalChecked(),
    Nan::GetFunction(CCBuffer::init()).ToLocalChecked());
}

NODE_MODULE(termios, init)