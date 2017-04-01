/* CTermios.cpp
 *
 * Copyright (C) 2017 Joerg Breitbart
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "CTermios.h"
#include "CCBuffer.h"


v8::Local<v8::FunctionTemplate> CTermios::init() {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("CTermios").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(3);

    // register methods
    Nan::SetPrototypeMethod(tpl, "toBuffer", ToBuffer);

    // register properties
    Nan::SetAccessor(
        tpl->InstanceTemplate(),
        Nan::New<String>("c_cc").ToLocalChecked(),
        (Nan::GetterCallback) (
            [] (v8::Local<v8::String> property,
                const Nan::PropertyCallbackInfo<v8::Value>& info) {
                CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
            info.GetReturnValue().Set(Nan::New(obj->ccbuffer));
            }),
            nullptr,
        Nan::New<v8::Value>(Nan::New<Number>(0)),
        v8::DEFAULT,
        static_cast<v8::PropertyAttribute>(
          v8::PropertyAttribute::DontDelete | v8::PropertyAttribute::ReadOnly)
    );
    Nan::SetAccessor(
      tpl->InstanceTemplate(),
      Nan::New<String>("c_lflag").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (v8::Local<v8::String> property,
            const Nan::PropertyCallbackInfo<v8::Value>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          info.GetReturnValue().Set(Nan::New<Number>(obj->value_.c_lflag));
        }),
      (Nan::SetterCallback) (
        [] (v8::Local<v8::String> property,
            v8::Local<v8::Value> value,
            const Nan::PropertyCallbackInfo<void>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          obj->value_.c_lflag = (tcflag_t) value->Uint32Value();
        }),
      Nan::New<v8::Value>(Nan::New<Number>(0)),
      v8::DEFAULT,
      v8::PropertyAttribute::DontDelete
    );
    Nan::SetAccessor(
      tpl->InstanceTemplate(),
      Nan::New<String>("c_cflag").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (v8::Local<v8::String> property,
            const Nan::PropertyCallbackInfo<v8::Value>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          info.GetReturnValue().Set(Nan::New<Number>(obj->value_.c_cflag));
        }),
      (Nan::SetterCallback) (
        [] (v8::Local<v8::String> property,
            v8::Local<v8::Value> value,
            const Nan::PropertyCallbackInfo<void>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          obj->value_.c_cflag = (tcflag_t) value->Uint32Value();
        }),
      Nan::New<v8::Value>(Nan::New<Number>(0)),
      v8::DEFAULT,
      v8::PropertyAttribute::DontDelete
    );
    Nan::SetAccessor(
      tpl->InstanceTemplate(),
      Nan::New<String>("c_oflag").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (v8::Local<v8::String> property,
            const Nan::PropertyCallbackInfo<v8::Value>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          info.GetReturnValue().Set(Nan::New<Number>(obj->value_.c_oflag));
        }),
      (Nan::SetterCallback) (
        [] (v8::Local<v8::String> property,
            v8::Local<v8::Value> value,
            const Nan::PropertyCallbackInfo<void>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          obj->value_.c_oflag = (tcflag_t) value->Uint32Value();
        }),
      Nan::New<v8::Value>(Nan::New<Number>(0)),
      v8::DEFAULT,
      v8::PropertyAttribute::DontDelete
    );
    Nan::SetAccessor(
      tpl->InstanceTemplate(),
      Nan::New<String>("c_iflag").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (v8::Local<v8::String> property,
            const Nan::PropertyCallbackInfo<v8::Value>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          info.GetReturnValue().Set(Nan::New<Number>(obj->value_.c_iflag));
        }),
      (Nan::SetterCallback) (
        [] (v8::Local<v8::String> property,
            v8::Local<v8::Value> value,
            const Nan::PropertyCallbackInfo<void>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          obj->value_.c_iflag = (tcflag_t) value->Uint32Value();
        }),
      Nan::New<v8::Value>(Nan::New<Number>(0)),
      v8::DEFAULT,
      v8::PropertyAttribute::DontDelete
    );

    // make function template persistent
    tmpl().Reset(tpl);

    return tpl;
}


CTermios::CTermios(struct termios *value = nullptr)
  : value_()
{
    if (value)
        memcpy(&value_, value, sizeof(value_));
}


CTermios::~CTermios()
{
    ccbuffer.Reset();
}


Nan::Persistent<v8::FunctionTemplate> & CTermios::tmpl()
{
    static Nan::Persistent<v8::FunctionTemplate> my_template;
    return my_template;
}


NAN_METHOD(CTermios::New)
{
    if (info.IsConstructCall()) {

        // allow other Termios object as parameter
        struct termios *old = nullptr;
        if (info.Length() > 1)
            return Nan::ThrowError("to many arguments");
        if (info.Length() == 1) {
            if (info[0]->IsNumber()) {
                // FIXME test for isatty
                struct termios fromfd = termios();
                old = &fromfd;
                tcgetattr(info[0]->Uint32Value(), old);
            } else if (info[0]->IsObject() && Nan::New(CTermios::tmpl())->HasInstance(info[0])) {
                old = &Nan::ObjectWrap::Unwrap<CTermios>(info[0]->ToObject())->value_;
            } else
                return Nan::ThrowError("first argument must be CTermios or file descriptor");
        }
        CTermios *obj = new CTermios(old);

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
        v8::Local<v8::Function> ctor = Nan::GetFunction(Nan::New(tmpl())).ToLocalChecked();
        info.GetReturnValue().Set(Nan::NewInstance(ctor, argc, argv).ToLocalChecked());
    }
}


NAN_METHOD(CTermios::ToBuffer)
{
    CTermios* obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
    info.GetReturnValue().Set(
      Nan::CopyBuffer((const char *) &obj->value_, sizeof(obj->value_)).ToLocalChecked());
}
