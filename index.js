'use strict';

module.exports = require('./build/Release/termios.node');
var t = module.exports;
var CTermios = t.CTermios;
var s = module.exports.ALL_SYMBOLS;

CTermios.prototype.writeTo = function (fd, action) {
    if (typeof action === 'undefined')
        action = s.TCSAFLUSH;
    t.tcsetattr(fd, action, this);
};
CTermios.prototype.loadFrom = function (fd) {
    t.tcgetattr(fd, this);
};
CTermios.prototype.getInputSpeed = function () {
    return t.cfgetispeed(this);
};
CTermios.prototype.getOutputSpeed = function () {
    return t.cfgetospeed(this);
};
CTermios.prototype.setInputSpeed = function (baudrate) {
    t.cfsetispeed(this, baudrate);
};
CTermios.prototype.setOutputSpeed = function (baudrate) {
    t.cfsetospeed(this, baudrate);
};
CTermios.prototype.setSpeed = function (baudrate) {
    t.cfsetispeed(this, baudrate);
    t.cfsetospeed(this, baudrate);
};
CTermios.prototype.setraw = function () {
    this.c_iflag &= ~(s.BRKINT | s.ICRNL | s.INPCK | s.ISTRIP | s.IXON);
    this.c_oflag &= ~s.OPOST;
    this.c_cflag &= ~(s.CSIZE | s.PARENB);
    this.c_cflag |= s.CS8;
    this.c_lflag &= ~(s.ECHO | s.ICANON | s.IEXTEN | s.ISIG);
    this.c_cc[s.VMIN] = 1;
    this.c_cc[s.VTIME] = 0;
};
CTermios.prototype.setcbreak = function () {
    this.c_lflag &= ~(s.ECHO | s.ICANON);
    this.c_cc[s.VMIN] = 1;
    this.c_cc[s.VTIME] = 0;
};

module.exports['Termios'] = CTermios;
