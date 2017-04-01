/* CCBuffer.cpp
 *
 * Copyright (C) 2017 Joerg Breitbart
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "CCBuffer.h"


v8::Local<v8::FunctionTemplate> CCBuffer::init()
{
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


CCBuffer::CCBuffer(cc_t *value, int length)
    : value_(value),
      length_(length)
{
}


CCBuffer::~CCBuffer()
{
}


NAN_METHOD(CCBuffer::New)
{
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


NAN_METHOD(CCBuffer::ToBuffer)
{
    CCBuffer* obj = Nan::ObjectWrap::Unwrap<CCBuffer>(info.Holder());
    info.GetReturnValue().Set(Nan::CopyBuffer((const char *) obj->value_, obj->length_).ToLocalChecked());
}


inline Nan::Persistent<v8::Function> & CCBuffer::constructor()
{
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
}


inline Nan::Persistent<v8::FunctionTemplate> & CCBuffer::tmpl()
{
    static Nan::Persistent<v8::FunctionTemplate> my_template;
    return my_template;
}


NAN_INDEX_GETTER(CCBuffer::IndexGetter)
{
    CCBuffer* obj = Nan::ObjectWrap::Unwrap<CCBuffer>(info.Holder());
    if (index >= obj->length_)
        return;
    info.GetReturnValue().Set(Nan::New<Number>(obj->value_[index]));
}


NAN_INDEX_SETTER(CCBuffer::IndexSetter)
{
    CCBuffer* obj = Nan::ObjectWrap::Unwrap<CCBuffer>(info.Holder());
    if (index < obj->length_ && value->IsNumber()) {
        obj->value_[index] = (cc_t) value->Uint32Value();
        info.GetReturnValue().Set(Nan::New<Number>(obj->value_[index]));
    } else
        info.GetReturnValue().SetUndefined();
}


NAN_INDEX_ENUMERATOR(CCBuffer::IndexEnumerator)
{
    CCBuffer* obj = Nan::ObjectWrap::Unwrap<CCBuffer>(info.Holder());
    v8::Local<v8::Array> arr(Nan::New<Array>(obj->length_));
    for (int i=0; i<obj->length_; ++i)
        arr->Set(i, Nan::New<Number>(i));
    info.GetReturnValue().Set(arr);
}

NAN_INDEX_DELETER(CCBuffer::IndexDeleter)
{
    info.GetReturnValue().Set(Nan::New<Boolean>(0));
}


NAN_INDEX_QUERY(CCBuffer::IndexQuery)
{
    // TODO
}