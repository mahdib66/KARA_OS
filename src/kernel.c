#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x07

/* Prototypes for hardware communication from keyboard.c */
unsigned char port_byte_in(unsigned short port);
char get_char_from_scancode(unsigned char scancode);

/* Global variables for terminal state */
int cursor_row = 0;
int cursor_col = 0;
char command_buffer[256];
int buffer_index = 0;

/* Internal function prototypes */
void clear_screen();
void kprint(char *message);
void kprint_char(char c, char attribute);
void handle_command(char *input);
void scroll_screen();

/**
 * Main execution loop
 */
void kernel_main(void) {
    clear_screen();
    kprint("#########################################\n");
    kprint("#           KARA OS v0.1                #\n");
    kprint("#########################################\n");
    kprint("Layout: AZERTY\n");
    kprint("welecome creator\n");
    kprint(">");

    while(1) {
        unsigned char scancode = port_byte_in(0x60);
        
        if (scancode < 0x80) { // Key down event
            char c = get_char_from_scancode(scancode);
            
            if (c != 0) {
                if (c == '\n') {
                    // Process the command when Enter is pressed
                    command_buffer[buffer_index] = '\0';
                    kprint("\n");
                    handle_command(command_buffer);
                    
                    // Reset buffer
                    buffer_index = 0;
                    kprint("\n> ");
                } 
                else if (buffer_index < 255) {
                    // Add char to buffer and display it
                    command_buffer[buffer_index++] = c;
                    kprint_char(c, WHITE_ON_BLACK);
                }
                
                // Debounce: Wait for key release
                while(port_byte_in(0x60) < 0x80);
            }
        }
    }
}

/**
 * Basic Logic for a Command Line Interface
 */
void handle_command(char *input) {
    // Simple manual string comparison
    if (input[0] == 'C' && input[1] == 'L' && input[2] == 'E' && input[3] == 'A' && input[4] == 'R') {
        clear_screen();
    } else if (input[0] == 'H' && input[1] == 'E' && input[2] == 'L' && input[3] == 'L' && input[4] == 'O') {
        kprint("Salutations from your custom kernel!");
    } else {
        kprint("Unknown Command: ");
        kprint(input);
    }
}

/**
 * Prints a single character and manages cursor position
 */
void kprint_char(char c, char attribute) {
    char *video_memory = (char *) VIDEO_ADDRESS;

    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
    } else {
        int offset = (cursor_row * MAX_COLS + cursor_col) * 2;
        video_memory[offset] = c;
        video_memory[offset + 1] = attribute;
        cursor_col++;
    }

    // Wrap line if it hits the edge
    if (cursor_col >= MAX_COLS) {
        cursor_col = 0;
        cursor_row++;
    }

    // Scroll if we hit the bottom
    if (cursor_row >= MAX_ROWS) {
        scroll_screen();
    }
}

void kprint(char *message) {
    int i = 0;
    while (message[i] != 0) {
        kprint_char(message[i], WHITE_ON_BLACK);
        i++;
    }
}

void clear_screen() {
    char *video_memory = (char *) VIDEO_ADDRESS;
    for (int i = 0; i < MAX_ROWS * MAX_COLS; i++) {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = WHITE_ON_BLACK;
    }
    cursor_row = 0;
    cursor_col = 0;
}

void scroll_screen() {
    char *video_memory = (char *) VIDEO_ADDRESS;
    // Move lines up
    for (int i = 1; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS * 2; j++) {
            video_memory[((i - 1) * MAX_COLS * 2) + j] = video_memory[(i * MAX_COLS * 2) + j];
        }
    }
    // Clear last line
    for (int j = 0; j < MAX_COLS * 2; j += 2) {
        video_memory[((MAX_ROWS - 1) * MAX_COLS * 2) + j] = ' ';
        video_memory[((MAX_ROWS - 1) * MAX_COLS * 2) + j + 1] = WHITE_ON_BLACK;
    }
    cursor_row = MAX_ROWS - 1;
}
