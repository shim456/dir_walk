#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
//
void walk_dir(char *);
int change_own(char *file);
int change_mod(char *file);
//int  para_check(int argc, char* argv[]);

//これは以下のシェルの代用として作成した：
///home/script/shell/sendml/apache_ses.sh
int main(int argc, char *argv[])
{
//  パラメータチェック
    if (argc != 2) {
        fprintf(stderr, "Error: wrong arguments\n");
        exit(1);
    }
    if (strlen(argv[1]) == 1 ) {
        fprintf(stderr, "Error: wrong directory(/ only not allowed)\n");
        exit(1);
    }
    char wstr[10];
    strncpy(wstr, argv[1], 1);
    if ( wstr[0] != '/' ) {
        fprintf(stderr, "Error: wrong directory\n");
        exit(1);
    }
    //実ユーザ&実効ユーザを表示する
    uid_t uid  = {0};
    uid_t euid = {0};
    uid  = getuid();
    euid = geteuid();
    printf("実ユーザID=%d 実効ユーザID=%d\n", uid, euid);
    //まず、トップディレクトリを処理する
    int ret;
    printf("%s\n", argv[1]);
    ret = change_mod(argv[1]);
    ret = change_own(argv[1]);
    walk_dir(argv[1]);

    exit(EXIT_SUCCESS);
}

//ディレクトリを再帰的に処理する
void walk_dir(char *dir)
{
    DIR *dp;
    struct dirent *ent;
    struct stat statbuf;
    int ret;

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(EXIT_FAILURE);
    }
    //カレント・ディレクトリ変更
    chdir(dir);
    while ((ent = readdir(dp)) != NULL) {
        lstat(ent->d_name, &statbuf);

        //FullPathに変換する
        char fpath[1024] = "";
        strcpy(fpath, dir);
        strcat(fpath,"/");
        strcat(fpath, ent->d_name);
 
        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(".", ent->d_name) == 0 ||
                strcmp("..", ent->d_name) == 0)
                continue;
            printf("%s\n", fpath);
            ret = change_mod(fpath);
            ret = change_own(fpath);
            walk_dir(fpath);
        }
        else {
            printf("%s\n", fpath);
            ret = change_mod(fpath);
            ret = change_own(fpath);
        }
    }
    chdir("..");
    closedir(dp);
}

