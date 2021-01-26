#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

// システムコールchownを使用してchownする
// // chown .eigyo fileコマンド相当

int change_own(char *file) {
    int  ret;
    struct group *grp = NULL;
//    grp = getgrnam("root");    //GIDを取得する
    grp = getgrnam("eigyo");    //GIDを取得する
    ret = chown(file, -1, grp->gr_gid);
    if ( ret != 0 ) {
        printf("%s\n","chown aborted!!");
    }
    return 0;
}
