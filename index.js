'use strict';

module.exports = require('./build/Release/termios.node');
const s = module.exports.ALL_SYMBOLS;
const t = module.exports;


class Termios extends t.CTermios {
    constructor(arg) {
        super(arg);
    }
    applyTo(fd, action) {
        if (typeof action === 'undefined')
            action = s.TCSAFLUSH;
        t.tcsetattr(fd, action, this);
    }
    loadFrom(fd) {
        t.tcgetattr(fd, this);
    }
    getInputSpeed() {
        return t.cfgetispeed(this);
    }
    getOutputSpeed() {
        return t.cfgetospeed(this);
    }
    setInputSpeed(baudrate) {
        t.cfsetispeed(this, baudrate);
    }
    setOutputSpeed(baudrate) {
        t.cfsetospeed(this, baudrate);
    }
    setSpeed(baudrate) {
        t.cfsetispeed(this, baudrate);
        t.cfsetospeed(this, baudrate);
    }
    setraw() {
        this.c_iflag &= ~(s.BRKINT | s.ICRNL | s.INPCK | s.ISTRIP | s.IXON);
        this.c_oflag &= ~s.OPOST;
        this.c_cflag &= ~(s.CSIZE | s.PARENB);
        this.c_cflag |= s.CS8;
        this.c_lflag &= ~(s.ECHO | s.ICANON | s.IEXTEN | s.ISIG);
        this.c_cc[s.VMIN] = 1;
        this.c_cc[s.VTIME] = 0;
    }
    setcbreak() {
        this.c_lflag &= ~(s.ECHO | s.ICANON);
        this.c_cc[s.VMIN] = 1;
        this.c_cc[s.VTIME] = 0;
    }
}
module.exports['Termios'] = Termios;
