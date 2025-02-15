#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define KEY_SIZE 80

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <device> <key to check>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *device = argv[1];
    const char *user_key = argv[2];
    char otp_key[KEY_SIZE + 1];
    int fd;

    // Open the OTP device
    fd = open(device, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open OTP device");
        return EXIT_FAILURE;
    }

    // Init otp_key
    memset(otp_key, 0, KEY_SIZE + 1);

    // Read the key from the OTP device
    ssize_t bytes_read = read(fd, otp_key, KEY_SIZE);
    if (bytes_read < 0) {
        perror("Failed to read from OTP device");
        close(fd);
        return EXIT_FAILURE;
    }
    if (otp_key[bytes_read -1] == '\n') {
        bytes_read--;
    }
    otp_key[bytes_read] = '\0'; // Null-terminate the key

    // Close the OTP device
    close(fd);

    // Compare the keys
    if (strncmp(otp_key, user_key, KEY_SIZE) == 0) {
        printf("Key match successful.\n");
        memset(otp_key, 0, KEY_SIZE + 1);
        return EXIT_SUCCESS;
    } else {
        printf("Key match failed.\n");
        memset(otp_key, 0, KEY_SIZE + 1);
        return EXIT_FAILURE;
    }
}