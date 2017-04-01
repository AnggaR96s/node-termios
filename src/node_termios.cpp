/* node_termios.cpp
 *
 * Copyright (C) 2017 Joerg Breitbart
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "node_termios.h"
#include "termios_basic.h"
#include "CTermios.h"

// symbol maps
flag_t c_iflag;
flag_t c_oflag;
flag_t c_cflag;
flag_t c_lflag;
unordered_map<string, unsigned int> c_cc;
unordered_map<string, int> actions;
unordered_map<string, int> flushs;
unordered_map<string, int> flows;
unordered_map<string, int> baudrates;


void populate_symbol_maps()
{
    // no platform switches here, simply test for existance of questionable symbols
    // TODO: explicit checks on linux, OSX, FreeBSD, Solaris, other BSDs

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

    // optional_actions for tcsetattr
    TERMIOS_EXPORT(actions, TCSANOW);
    TERMIOS_EXPORT(actions, TCSADRAIN);
    TERMIOS_EXPORT(actions, TCSAFLUSH);
#if defined(TCSASOFT)
    TERMIOS_EXPORT(actions, TCSASOFT);
#endif

    // tcflush queue_selectors
    TERMIOS_EXPORT(flushs, TCIFLUSH);
    TERMIOS_EXPORT(flushs, TCOFLUSH);
    TERMIOS_EXPORT(flushs, TCIOFLUSH);

    // tcflow actions
    TERMIOS_EXPORT(flows, TCOOFF);
    TERMIOS_EXPORT(flows, TCOON);
    TERMIOS_EXPORT(flows, TCIOFF);
    TERMIOS_EXPORT(flows, TCION);

    // baud rates
    TERMIOS_EXPORT(baudrates, B0);
    TERMIOS_EXPORT(baudrates, B50);
    TERMIOS_EXPORT(baudrates, B75);
    TERMIOS_EXPORT(baudrates, B110);
    TERMIOS_EXPORT(baudrates, B134);
    TERMIOS_EXPORT(baudrates, B150);
    TERMIOS_EXPORT(baudrates, B200);
    TERMIOS_EXPORT(baudrates, B300);
    TERMIOS_EXPORT(baudrates, B600);
    TERMIOS_EXPORT(baudrates, B1200);
    TERMIOS_EXPORT(baudrates, B1800);
    TERMIOS_EXPORT(baudrates, B2400);
    TERMIOS_EXPORT(baudrates, B4800);
    TERMIOS_EXPORT(baudrates, B9600);
    TERMIOS_EXPORT(baudrates, B19200);
    TERMIOS_EXPORT(baudrates, B38400);
#if defined(B7200)
    TERMIOS_EXPORT(baudrates, B7200);
#endif
#if defined(B14400)
    TERMIOS_EXPORT(baudrates, B14400);
#endif
#if defined(B28800)
    TERMIOS_EXPORT(baudrates, B28800);
#endif
    TERMIOS_EXPORT(baudrates, B57600);
#if defined(B76800)
    TERMIOS_EXPORT(baudrates, B76800);
#endif
    TERMIOS_EXPORT(baudrates, B115200);
    TERMIOS_EXPORT(baudrates, B230400);
#if defined(B460800)
    TERMIOS_EXPORT(baudrates, B460800);
#endif
#if defined(B500000)
    TERMIOS_EXPORT(baudrates, B500000);
#endif
#if defined(B576000)
    TERMIOS_EXPORT(baudrates, B576000);
#endif
#if defined(B921600)
    TERMIOS_EXPORT(baudrates, B921600);
#endif
#if defined(B1000000)
    TERMIOS_EXPORT(baudrates, B1000000);
#endif
#if defined(B1152000)
    TERMIOS_EXPORT(baudrates, B1152000);
#endif
#if defined(B1500000)
    TERMIOS_EXPORT(baudrates, B1500000);
#endif
#if defined(B2000000)
    TERMIOS_EXPORT(baudrates, B2000000);
#endif
#if defined(B2500000)
    TERMIOS_EXPORT(baudrates, B2500000);
#endif
#if defined(B3000000)
    TERMIOS_EXPORT(baudrates, B3000000);
#endif
#if defined(B3500000)
    TERMIOS_EXPORT(baudrates, B3500000);
#endif
#if defined(B4000000)
    TERMIOS_EXPORT(baudrates, B4000000);
#endif
#if defined(EXTA)
    TERMIOS_EXPORT(baudrates, EXTA);
#endif
#if defined(EXTB)
    TERMIOS_EXPORT(baudrates, EXTB);
#endif
}


NAN_MODULE_INIT(init) {
    Nan::HandleScope scope;
    populate_symbol_maps();

    // helper functions
    MODULE_EXPORT("isatty", Nan::New<FunctionTemplate>(Isatty)->GetFunction());
    MODULE_EXPORT("ttyname", Nan::New<FunctionTemplate>(Ttyname)->GetFunction());
    MODULE_EXPORT("ptsname", Nan::New<FunctionTemplate>(Ptsname)->GetFunction());

    // termios functions
    MODULE_EXPORT("tcgetattr", Nan::New<FunctionTemplate>(Tcgetattr)->GetFunction());
    MODULE_EXPORT("tcsetattr", Nan::New<FunctionTemplate>(Tcsetattr)->GetFunction());
    MODULE_EXPORT("tcsendbreak", Nan::New<FunctionTemplate>(Tcsendbreak)->GetFunction());
    MODULE_EXPORT("tcdrain", Nan::New<FunctionTemplate>(Tcdrain)->GetFunction());
    MODULE_EXPORT("tcflush", Nan::New<FunctionTemplate>(Tcflush)->GetFunction());
    MODULE_EXPORT("tcflow", Nan::New<FunctionTemplate>(Tcflow)->GetFunction());

    // objects
    MODULE_EXPORT("CTermios", Nan::GetFunction(CTermios::init()).ToLocalChecked());
}

NODE_MODULE(termios, init)
