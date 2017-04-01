/* node_termios.cpp
 *
 * Copyright (C) 2017 Joerg Breitbart
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "node_termios.h"
#include "CTermios.h"
#include "CCBuffer.h"

NAN_MODULE_INIT(init) {
    Nan::HandleScope scope;
    Nan::Set(target, Nan::New("CTermios").ToLocalChecked(),
        Nan::GetFunction(CTermios::init()).ToLocalChecked());
    Nan::Set(target, Nan::New("CCBuffer").ToLocalChecked(),
        Nan::GetFunction(CCBuffer::init()).ToLocalChecked());
}

NODE_MODULE(termios, init)
