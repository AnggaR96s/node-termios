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

static flag_t c_iflag;
static flag_t c_oflag;
static flag_t c_cflag;
static flag_t c_lflag;
static unordered_map<string, unsigned int> c_cc;
static unordered_map<string, int> actions;
static unordered_map<string, int> flushs;
static unordered_map<string, int> flows;

#define TERMIOS_EXPORT(o, s) (o[#s] = s)





#endif // NODE_TERMIOS_H