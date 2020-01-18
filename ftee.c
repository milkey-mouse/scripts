// https://stackoverflow.com/questions/7360473#7620387
// gcc ftee.c -O3 -o ftee

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int readfd, writefd;
    struct stat status;
    char* fifonam;
    //char buffer[BUFSIZ];
    char *buffer;
    ssize_t bufsiz;
    ssize_t bytes;

    signal(SIGPIPE, SIG_IGN);

    if (argc < 2 || argc > 3) {
        printf(
            "Usage:\n someprog 2>&1 | %s FIFO [BUFSIZ]\n FIFO - path to a"
            " named pipe, required argument\n BUFSIZ - chunk size to copy\n",
            argv[0]);
        exit(EXIT_FAILURE);
    }

    bufsiz = 0;
    if (argc == 3) {
        bufsiz = strtol(argv[2], NULL, 0);
    }
    if (bufsiz == 0) {
        bufsiz = BUFSIZ;
    }

    buffer = malloc(bufsiz);
    if (buffer == NULL) {
        printf("ftee: malloc failed");
        exit(EXIT_FAILURE);
    }

    fifonam = argv[1];

    readfd = open(fifonam, O_RDONLY | O_NONBLOCK);
    if (-1 == readfd) {
        perror("ftee: readfd: open()");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    if (-1 == fstat(readfd, &status)) {
        perror("ftee: fstat");
        close(readfd);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    if (!S_ISFIFO(status.st_mode)) {
        printf("ftee: %s is not a fifo!\n", fifonam);
        close(readfd);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    writefd = open(fifonam, O_WRONLY | O_NONBLOCK);
    if (-1 == writefd) {
        perror("ftee: writefd: open()");
        close(readfd);
        free(buffer);
        exit(EXIT_FAILURE);
    }

    close(readfd);

    while (1) {
        bytes = read(STDIN_FILENO, buffer, bufsiz);
        if (bytes < 0 && errno == EINTR)
            continue;
        if (bytes <= 0)
            break;

        bytes = write(STDOUT_FILENO, buffer, bytes);
        if (-1 == bytes) {
            perror("ftee: writing to stdout");
            break;
        }

        bytes = write(writefd, buffer, bytes);
        // ignoring FIFO write errors
        //if (-1 == bytes) {
        //    perror("ftee: writing to FIFO");
        //}
    }
    close(writefd);
    free(buffer);
    return (0);
}
