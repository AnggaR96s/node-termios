import * as path from 'path';
export const native = require(path.join('..', 'build', 'Release', 'termios.node'));
const s = native.ALL_SYMBOLS;

export interface ICTermios {
    new (value?: ICTermios|number|null): ICTermios;
    (value?: ICTermios|number|null): ICTermios;
    c_iflag: number;
    c_oflag: number;
    c_cflag: number;
    c_lflag: number;
    c_cc: number[];
    writeTo(fd: number, action?: number): void;
    loadFrom(fd: number): void;
    getInputSpeed(): number;
    getInputSpeed(): number;
    setInputSpeed(baudrate: number): void;
    setOutputSpeed(baudrate: number): void;
    setSpeed(baudrate: number): void;
    setraw(): void;
    setcbreak(): void;
    __proto__: any;
}

export let Termios: ICTermios = native.CTermios;

class TermiosHelper extends Termios {
    writeTo(fd: number, action?: number): void {
        if (typeof action === 'undefined')
            action = s.TCSAFLUSH;
        native.tcsetattr(fd, action, this);
    }
    loadFrom(fd: number): void {
        native.tcgetattr(fd, this);
    }
    getInputSpeed(): number {
        return native.cfgetispeed(this);
    }
    getOutputSpeed(): number {
        return native.cfgetospeed(this);
    }
    setInputSpeed(baudrate: number): void {
        native.cfsetispeed(this, baudrate);
    }
    setOutputSpeed(baudrate: number): void {
        native.cfsetospeed(this, baudrate);
    }
    setSpeed(baudrate: number): void {
        native.cfsetispeed(this, baudrate);
        native.cfsetospeed(this, baudrate);
    }
    setraw(): void {
        this.c_iflag &= ~(s.BRKINT | s.ICRNL | s.INPCK | s.ISTRIP | s.IXON);
        this.c_oflag &= ~s.OPOST;
        this.c_cflag &= ~(s.CSIZE | s.PARENB);
        this.c_cflag |= s.CS8;
        this.c_lflag &= ~(s.ECHO | s.ICANON | s.IEXTEN | s.ISIG);
        this.c_cc[s.VMIN] = 1;
        this.c_cc[s.VTIME] = 0;
    }
    setcbreak(): void {
        this.c_lflag &= ~(s.ECHO | s.ICANON);
        this.c_cc[s.VMIN] = 1;
        this.c_cc[s.VTIME] = 0;
    }
}

TermiosHelper.prototype.__proto__ = {};
Termios.prototype.__proto__ = TermiosHelper.prototype;
