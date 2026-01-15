/* keyboard.c - AZERTY Layout and Port I/O */

/**
 * Reads a byte from the specified hardware port.
 */
unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

/**
 * Maps hardware scancodes to AZERTY characters.
 */
char get_char_from_scancode(unsigned char scancode) {
    switch(scancode) {
        // Top Row Numbers (AZERTY standard)
        case 0x02: return '1';
        case 0x03: return '2';
        case 0x04: return '3';
        case 0x05: return '4';
        case 0x06: return '5';
        case 0x07: return '6';
        case 0x08: return '7';
        case 0x09: return '8';
        case 0x0A: return '9';
        case 0x0B: return '0';

        // Letter Rows (AZERTY Mapping)
        case 0x10: return 'A'; // Swapped with Q
        case 0x11: return 'Z'; // Swapped with W
        case 0x12: return 'E';
        case 0x13: return 'R';
        case 0x14: return 'T';
        case 0x15: return 'Y';
        case 0x16: return 'U';
        case 0x17: return 'I';
        case 0x18: return 'O';
        case 0x19: return 'P';
        
        case 0x1E: return 'Q'; // Swapped with A
        case 0x1F: return 'S';
        case 0x20: return 'D';
        case 0x21: return 'F';
        case 0x22: return 'G';
        case 0x23: return 'H';
        case 0x24: return 'J';
        case 0x25: return 'K';
        case 0x26: return 'L';
        case 0x27: return 'M'; // M position in AZERTY
        
        case 0x2C: return 'W'; // Swapped with Z
        case 0x2D: return 'X';
        case 0x2E: return 'C';
        case 0x2F: return 'V';
        case 0x30: return 'B';
        case 0x31: return 'N';

        // Special Keys
        case 0x39: return ' ';  // Space
        case 0x1C: return '\n'; // Enter (New Line)
        
        // Return 0 for keys we haven't mapped yet (like Shift/Ctrl)
        default: return 0;
    }
}
