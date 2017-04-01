/* node_termios.h
 *
 * Copyright (C) 2017 Joerg Breitbart
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef NODE_TERMIOS_H
#define NODE_TERMIOS_H

#include "nan.h"
#include <termios.h>

using namespace node;
using namespace v8;
using namespace std;

#include <unordered_map>

typedef unordered_map<string, tcflag_t> flag_t;

// symbol maps
extern flag_t c_iflag;
extern flag_t c_oflag;
extern flag_t c_cflag;
extern flag_t c_lflag;
extern unordered_map<string, unsigned int> c_cc;
extern unordered_map<string, int> actions;
extern unordered_map<string, int> flushs;
extern unordered_map<string, int> flows;
extern unordered_map<string, int> baudrates;

#define TERMIOS_EXPORT(o, s) (o[#s] = s)
#define MODULE_EXPORT(name, symbol) (Nan::Set(target, Nan::New<String>(name).ToLocalChecked(), symbol))



#endif // NODE_TERMIOS_H