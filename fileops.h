#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define cat(...) cat_unwrapped(__VA_ARGS__, NULL)


FILE *fopen_or_abort(const char *fname, const char *mode)
{
    FILE *fp = fopen(fname, mode);;
    if (!fp) {
        fprintf(stderr, "Fatal: cannot open file %s\n.", fname);
        abort();
    }
    return fp;
}


/* cat() - concatenate files and print on standard output
 *
 * cat(char *file, ...)
 *
 * Concatenate FILE(s) to standard output.
 */
void cat_unwrapped(const char *fname, ...)
{
    FILE *fp;
    char c;
    va_list arg;
    va_start(arg, fname);
    while (fname) {
        fp = fopen_or_abort(fname, "r");
        c = fgetc(fp);
        while (c != EOF) {
            printf("%c", c);
            c = fgetc(fp);
        }
        fclose(fp);
        fname = va_arg(arg, const char *);
    }
}


/* cp() - copy file
 *
 * cp(char *source, char *dest)
 *
 * Copy SOURCE to DEST.
 */
void cp(const char *source, const char *dest)
{
    FILE *fsource, *fdest;
    char c;
    fsource = fopen_or_abort(source, "r");
    fdest = fopen_or_abort(dest, "a");
    c = fgetc(fsource);
    while (c != EOF) {
        fputc(c, fdest);
        c = fgetc(fsource);
    }
    fclose(fsource);
    fclose(fdest);
}


/* mv() - move file
 *
 * mv(char *source, char *dest)
 *
 * Move SOURCE to DEST.
 */
void mv(const char *source, const char *dest)
{
    int err;
    err = rename(source, dest);
    if (err) {
        cp(source, dest);
        unlink(source);
    }
}
