/* CTermios.h
 *
 * Copyright (C) 2017 Joerg Breitbart
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef CTERMIOS_H
#define CTERMIOS_H

#include "node_termios.h"

class CTermios : public Nan::ObjectWrap {
public:
    static v8::Local<v8::FunctionTemplate> init();
    static Nan::Persistent<v8::FunctionTemplate> & getTemplate() { return tmpl(); }
    struct termios* data() { return &value_; }
private:
    explicit CTermios(struct termios *value);
    ~CTermios();
    static Nan::Persistent<v8::FunctionTemplate> & tmpl();

    // JS methods
    static NAN_METHOD(New);
    static NAN_METHOD(ToBuffer);

    struct termios value_;
    Nan::Persistent<v8::Object> ccbuffer;
};

#endif // CTERMIOS_H
