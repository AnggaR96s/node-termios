/**
 * interface for legal iflags
 */
export interface IIFLAGS {
    IGNBRK: number;
    BRKINT: number;
    IGNPAR: number;
    PARMRK: number;
    INPCK: number;
    ISTRIP: number;
    INLCR: number;
    IGNCR: number;
    ICRNL: number;
    IUCLC?: number;
    IXON: number;
    IXANY: number;
    IXOFF: number;
    IMAXBEL: number;
    IUTF8?: number;
}

/**
 * interface for legal oflags
 */
export interface IOFLAGS {
    OPOST: number;
    OLCUC?: number;
    ONLCR: number;
    OCRNL: number;
    ONOCR: number;
    ONLRET: number;
    OFILL?: number;
    OFDEL?: number;
    NLDLY?: number;
    CRDLY?: number;
    TABDLY?: number;
    BSDLY?: number;
    VTDLY?: number;
    FFDLY?: number;
    TAB0?: number;
    TAB3?: number;
    ONOEOT?: number;
}

/**
 * interface for legal cflags
 */
export interface ICFLAGS {
    CBAUD?: number;
    CBAUDEX?: number;
    CSIZE: number;
    CS5: number;
    CS6: number;
    CS7: number;
    CS8: number;
    CSTOPB: number;
    CREAD: number;
    PARENB: number;
    PARODD: number;
    HUPCL: number;
    CLOCAL: number;
    LOBLK?: number;
    CIBAUD?: number;
    CMSPAR?: number;
    CRTSCTS: number;
    CCTS_OFLOW?: number;
    CRTS_IFLOW?: number;
    MDMBUF?: number;
}

/**
 * interface for legal lflags
 */
export interface ILFLAGS {
    ISIG: number;
    ICANON: number;
    XCASE?: number;
    ECHO: number;
    ECHOE: number;
    ECHOK?: number;
    ECHONL: number;
    ECHOCTL: number;
    ECHOPRT: number;
    ECHOKE: number;
    DEFECHO?: number;
    FLUSHO: number;
    NOFLSH: number;
    TOSTOP: number;
    PENDIN: number;
    IEXTEN: number;
    ALTWERASE?: number;
    EXTPROC?: number;
    NOKERNINFO?: number;
}

/**
 * interface for legal cc entries
 */
export interface ICC {
    VDISCARD: number;
    VDSUSP?: number;
    VEOF: number;
    VEOL: number;
    VEOL2: number;
    VERASE: number;
    VINTR: number;
    VKILL: number;
    VLNEXT: number;
    VMIN: number;
    VQUIT: number;
    VREPRINT: number;
    VSTART: number;
    VSTATUS?: number;
    VSTOP: number;
    VSUSP: number;
    VSWTCH?: number;
    VTIME: number;
    VWERASE: number;
}

// optional_actions for tcsetattr
export interface IACTION {
    TCSANOW: number;
    TCSADRAIN: number;
    TCSAFLUSH: number;
    TCSASOFT?: number;
}

// tcflush queue_selectors
export interface IFLUSH {
    TCIFLUSH: number;
    TCOFLUSH: number;
    TCIOFLUSH: number;
}

// tcflow actions
export interface IFLOW {
    TCOOFF: number;
    TCOON: number;
    TCIOFF: number;
    TCION: number;
}

// baud rates
export interface IBAUD {
    B0: number;
    B50: number;
    B75: number;
    B110: number;
    B134: number;
    B150: number;
    B200: number;
    B300: number;
    B600: number;
    B1200: number;
    B1800: number;
    B2400: number;
    B4800: number;
    B9600: number;
    B19200: number;
    B38400: number;
    B7200?: number;
    B14400?: number;
    B28800?: number;
    B57600: number;
    B76800?: number;
    B115200: number;
    B230400: number;
    B460800?: number;
    B500000?: number;
    B576000?: number;
    B921600?: number;
    B1000000?: number;
    B1152000?: number;
    B1500000?: number;
    B2000000?: number;
    B2500000?: number;
    B3000000?: number;
    B3500000?: number;
    B4000000?: number;
    EXTA?: number;
    EXTB?: number;
}

/**
 * native module exports
 */
export interface INative {
    isatty(fd: number): boolean;
    ttyname(fd: number): string;
    ptsname(fd: number): string;
    tcgetattr(fd: number, termios: ITermios): void;
    tcsetattr(fd: number, action: number, termios: ITermios): void;
    tcsendbreak(fd: number, duration: number): void;
    tcdrain(fd: number): void;
    tcflush(fd: number, queue_selector: number): void;
    tcflow(fd: number, action: number): void;
    cfgetispeed(termios: ITermios): number;
    cfgetospeed(termios: ITermios): number;
    cfsetispeed(termios: ITermios, speed: number): void;
    cfsetospeed(termios: ITermios, speed: number): void;
    CTermios: ITermios;
    ALL_SYMBOLS: IIFLAGS & IOFLAGS & ICFLAGS & ILFLAGS & ICC & IACTION & IFLUSH & IFLOW & IBAUD;
    IFLAGS: IIFLAGS;
    OFLAGS: IOFLAGS;
    CFLAGS: ICFLAGS;
    LFLAGS: ILFLAGS;
    CC: ICC;
    ACTION: IACTION;
    FLUSH: IFLUSH;
    FLOW: IFLOW;
    BAUD: IBAUD;
}

/**
 * interface of Termios
 */
export interface ITermios {
    new (value?: ITermios | number | null): ITermios;
    (value?: ITermios | number | null): ITermios;
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
    setcokked(): void;
    __proto__: any;  // needed to get awkward overloading done
}
