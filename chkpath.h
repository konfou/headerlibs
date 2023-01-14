#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void *malloc_or_abort(size_t n)
{
    void *p = malloc(n);
    if (!p) {
        fprintf(stderr, "Fatal: failed to allocate.\n");
        abort();
    }
    return p;
}


/* which() - shows the full path of commands.
 *
 * which(char *command)
 *
 * It returns the full path of the executable that would have been
 * executed had `command` been entered at shell prompt that has
 * environment same to the program calling the function. It does this
 * by searching for an executable or script in the directories listed
 * in the environment variable PATH. Returns empty string if no such
 * path is found.
 */
char *which(const char *cmd)
{
    char *fname;

    // if cmd given is with path
    if (strchr(cmd, '/')) {
        if (access(cmd, X_OK) == 0) {
            fname = malloc_or_abort(strlen(cmd));
            strcat(fname, cmd);
            return fname;
        } else
            return "";
    }
    // if cmd given is only name
    const char *path;
    char *p;

    path = getenv("PATH");
    if (!path) {
        // probably but not mandatorily fatal
        fprintf(stderr, "PATH variable not set.\n");
        return "";
    }
    // /path/to/some/directory + / + cmd + \0
    fname = malloc_or_abort(strlen(path) + strlen(cmd) + 2);

    p = fname;
    for (; *path; ++path, ++p) {
        *p = *path;
        if (*p == ':') {
            *p = '/';
            *(++p) = '\0';
            strcat(fname, cmd);
            if (access(fname, X_OK) == 0)
                return fname;
            p = fname;
            p--;
        }
    }

    *p = '/';
    *(++p) = '\0';
    strcat(fname, cmd);
    if (access(fname, X_OK) == 0)
        return fname;

    free(fname);
    return "";
}


bool iscmdavail(const char *cmd)
{
    char *cmdpath = which(cmd);
    return cmdpath[0];
}
