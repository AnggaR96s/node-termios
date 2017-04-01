/* CTermios.cpp
 *
 * Copyright (C) 2017 Joerg Breitbart
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "CTermios.h"
#include "CCBuffer.h"


Local<FunctionTemplate> CTermios::init() {
    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("CTermios").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(3);

    // register methods
    Nan::SetPrototypeMethod(tpl, "toBuffer", ToBuffer);

    // register properties
    Nan::SetAccessor(
        tpl->InstanceTemplate(),
        Nan::New<String>("c_cc").ToLocalChecked(),
        (Nan::GetterCallback) (
            [] (Local<String> property,
                const Nan::PropertyCallbackInfo<Value>& info) {
                CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
            info.GetReturnValue().Set(Nan::New(obj->ccbuffer));
            }),
            nullptr,
        Nan::New<Value>(Nan::New<Number>(0)),
        DEFAULT,
        static_cast<PropertyAttribute>(
          PropertyAttribute::DontDelete | PropertyAttribute::ReadOnly)
    );
    Nan::SetAccessor(
      tpl->InstanceTemplate(),
      Nan::New<String>("c_lflag").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (Local<String> property,
            const Nan::PropertyCallbackInfo<Value>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          info.GetReturnValue().Set(Nan::New<Number>(obj->value_.c_lflag));
        }),
      (Nan::SetterCallback) (
        [] (Local<String> property,
            Local<Value> value,
            const Nan::PropertyCallbackInfo<void>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          obj->value_.c_lflag = (tcflag_t) value->Uint32Value();
        }),
      Nan::New<Value>(Nan::New<Number>(0)),
      DEFAULT,
      PropertyAttribute::DontDelete
    );
    Nan::SetAccessor(
      tpl->InstanceTemplate(),
      Nan::New<String>("c_cflag").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (Local<String> property,
            const Nan::PropertyCallbackInfo<Value>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          info.GetReturnValue().Set(Nan::New<Number>(obj->value_.c_cflag));
        }),
      (Nan::SetterCallback) (
        [] (Local<String> property,
            Local<Value> value,
            const Nan::PropertyCallbackInfo<void>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          obj->value_.c_cflag = (tcflag_t) value->Uint32Value();
        }),
      Nan::New<Value>(Nan::New<Number>(0)),
      DEFAULT,
      PropertyAttribute::DontDelete
    );
    Nan::SetAccessor(
      tpl->InstanceTemplate(),
      Nan::New<String>("c_oflag").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (Local<String> property,
            const Nan::PropertyCallbackInfo<Value>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          info.GetReturnValue().Set(Nan::New<Number>(obj->value_.c_oflag));
        }),
      (Nan::SetterCallback) (
        [] (Local<String> property,
            Local<Value> value,
            const Nan::PropertyCallbackInfo<void>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          obj->value_.c_oflag = (tcflag_t) value->Uint32Value();
        }),
      Nan::New<Value>(Nan::New<Number>(0)),
      DEFAULT,
      PropertyAttribute::DontDelete
    );
    Nan::SetAccessor(
      tpl->InstanceTemplate(),
      Nan::New<String>("c_iflag").ToLocalChecked(),
      (Nan::GetterCallback) (
        [] (Local<String> property,
            const Nan::PropertyCallbackInfo<Value>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          info.GetReturnValue().Set(Nan::New<Number>(obj->value_.c_iflag));
        }),
      (Nan::SetterCallback) (
        [] (Local<String> property,
            Local<Value> value,
            const Nan::PropertyCallbackInfo<void>& info) {
          CTermios *obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
          obj->value_.c_iflag = (tcflag_t) value->Uint32Value();
        }),
      Nan::New<Value>(Nan::New<Number>(0)),
      DEFAULT,
      PropertyAttribute::DontDelete
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


Nan::Persistent<FunctionTemplate> & CTermios::tmpl()
{
    static Nan::Persistent<FunctionTemplate> my_template;
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
            } else if (info[0]->IsObject() && ctorTemplate()->HasInstance(info[0])) {
                old = &Nan::ObjectWrap::Unwrap<CTermios>(info[0]->ToObject())->value_;
            } else
                return Nan::ThrowError("first argument must be CTermios or file descriptor");
        }
        CTermios *obj = new CTermios(old);

        // set c_cc as CCBuffer
        Local<Function> ctor_buf = Nan::GetFunction(CCBuffer::init()).ToLocalChecked();
        Local<Object> buf = Nan::NewInstance(ctor_buf).ToLocalChecked();
        obj->ccbuffer.Reset(buf);
        // CCBuffer values
        CCBuffer *cbuf = Nan::ObjectWrap::Unwrap<CCBuffer>(buf);
        cbuf->value_ = obj->value_.c_cc;
        cbuf->length_ = NCCS;

        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        int argc = info.Length();
        Local<Value> argv[argc];
        for (int i=0; i<argc; ++i)
            argv[i] = info[i];
        Local<Function> ctor = Nan::GetFunction(ctorTemplate()).ToLocalChecked();
        info.GetReturnValue().Set(Nan::NewInstance(ctor, argc, argv).ToLocalChecked());
    }
}


NAN_METHOD(CTermios::ToBuffer)
{
    CTermios* obj = Nan::ObjectWrap::Unwrap<CTermios>(info.Holder());
    info.GetReturnValue().Set(
      Nan::CopyBuffer((const char *) &obj->value_, sizeof(obj->value_)).ToLocalChecked());
}
