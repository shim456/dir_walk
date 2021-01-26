#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

// stat.hライブラリを使用してchmodする
// // chmod 777 fileコマンド相当

int change_mod(char *file) {
    int  ret;
    ret = chmod(file,
        S_IRUSR | S_IWUSR | S_IXUSR |    /* rwx */
        S_IRGRP | S_IWGRP | S_IXGRP |    /* rwx */
        S_IROTH | S_IWOTH | S_IXOTH );   /* rwx */
    if ( ret != 0 ) {
        printf("%s\n","chmod aborted!!");
    }
    return 0;

}
