#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Check for the arguments to avoid segfaults
    if (argc != 2) {
        printf("Usage: brightness [+-]\n");
        return 1;
    }

    // The step for brightness inc/dec (might be modified)
    int step = 20;

    // Get the max_brightness value
    FILE *stream;
    char s[4];

    if ((stream = fopen("/sys/class/backlight/intel_backlight/max_brightness", "r")) == NULL) {
        printf("Error: Couldn't read /sys/class/backlight/intel_backlight/max_brightness\n");
        return 1;
    }

    const int max_brightness = atoi(fgets(s, 4, stream));

    if (fclose(stream) != 0) {
        printf("Error: Couldn't close /sys/class/backlight/intel_backlight/max_brightness correctly\n");
        return 1;
    }

    // Get the current brightness value
    if ((stream = fopen("/sys/class/backlight/intel_backlight/brightness", "r+")) == NULL) {
        printf("Error: Couldn't read /sys/class/backlight/intel_backlight/brightness\n");
        return 1;
    }

    const int curr_brightness = atoi(fgets(s, 4, stream));

    // Compute the next brightness
    int next_brightness;
    switch (*argv[1]) {
    case '+':
        next_brightness = curr_brightness + step;

        if (next_brightness > max_brightness)
            next_brightness = max_brightness;
        break;
    case '-':
        next_brightness = curr_brightness - step;

        if (next_brightness < 0)
            next_brightness = 0;
        break;
    default:
        next_brightness = curr_brightness;
        printf("Usage: brightness [+-]\n");
    }

    // Write the new brightness
    rewind(stream);
    int num_bytes = fprintf(stream, "%d", next_brightness);
    if (num_bytes < 0)
        printf("Error: Couldn't write new brightness value in file\n");

    // Don't forget to close the stream
    if (fclose(stream) != 0) {
        printf("Error: Couldn't close /sys/class/backlight/intel_backlight/brightness correctly\n");
        return 1;
    }

    // Truncate file so that it correctly overrides previous value
    if (truncate("/sys/class/backlight/intel_backlight/brightness", num_bytes + 1) != 0)
        printf("Error: Couldn't truncate file\n");

    return 0;
}
