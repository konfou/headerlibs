#include <stdio.h>
#include "fileops.h"


int main(void)
{
    char *teststr = "test string\n";
    FILE *fp = fopen("testfile1", "w+");
    fputs(teststr, fp);
    fclose(fp);
    cp("testfile1", "testfile2");
    mv("testfile1", "testfile3");
    cp("testfile3", "testfile1");
    cat("testfile1");
    cat("testfile2");
    cat("testfile3");
    cat("testfile1", "testfile2", "testfile3");
    unlink("testfile1");
    unlink("testfile2");
    unlink("testfile3");
    return 0;
}

