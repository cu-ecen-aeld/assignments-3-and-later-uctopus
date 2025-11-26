#include <stdio.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        syslog(LOG_ERR, "Usage: %s <filename> <string_to_write>", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error opening file %s", filename);
        return 1;
    }

    const char* writestr = argv[2];
    int res = fputs(writestr, file);
    if (res == EOF) {
        syslog(LOG_ERR, "Error writing to file %s", filename);
        fclose(file);
        return 1;
    }
    syslog(LOG_DEBUG, "“Writing %s to %s”", writestr, filename);

    res = fclose(file);
    if (res != 0) {
        syslog(LOG_ERR, "Error closing file %s", filename);
        return 1;
    }

    return 0;
}