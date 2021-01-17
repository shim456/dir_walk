#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
//#define _XOPEN_SOURCE_EXTENDED 1
#include <libgen.h>

void walk_dir(char *);
void do_action(char *);
//int  para_check(int argc, char* argv[]);

//これは以下のシェルの代用として作成した：
///home/script/shell/sendml/apache_ses.sh
FILE* fp;

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
    //walkした結果をファイルに保存するバージョン
    char *dir_name = "";
    char *base_name = "";
    char wpath1[1024] = "";
    char wpath2[1024] = "";
    strcpy(wpath1, argv[0]);
    strcpy(wpath2, argv[0]);
    dir_name = dirname(wpath1);
    base_name = basename(wpath2);
    printf("%s %s\n", dir_name, base_name);

   // ファイルを読み書き両用でオープン
    char list_file[1024] = "";
    strcpy(list_file, dir_name);   
    strcat(list_file, "/");   
    strcat(list_file, base_name);   
    strcat(list_file, ".list");   
    printf("%s\n", list_file);
    fp = fopen( list_file, "w+" );
    if( fp == NULL ){
//        fprintf(fp,  "%s\n",  );
        exit( EXIT_FAILURE );
    }

    //まず、トップディレクトリを処理する
    int ret;
    printf("%s\n", argv[1]);
    fprintf(fp, "%s\n", argv[1]);
//    ret = change_mod(argv[1]);
//    ret = change_own(argv[1]);


    walk_dir(argv[1]);

    fclose(fp);

    do_action(list_file);

    //
    char cmd[1024] = "sort -r /home/shim123/dir_walk/dir_walk2.list -o /home/shim123/dir_walk/dir_walk2.sort";
    int rt;
    rt = system(cmd);
    printf("%s %d\n", "issue system cmd return", rt);

    exit(EXIT_SUCCESS);
}


// システムコールchownを使用してchownする
// chown .eigyo fileコマンド相当
int change_own(char *file) {
    int  ret;
/*    struct passwd *pswd = NULL; */
/*    pswd = getpwnam("shim123"); */
//    ret = chown(file, pswd->pw_uid, pswd->pw_gid);
    struct group *grp = NULL;
//    grp = getgrnam("eigyo");    //「eigyo」のGIDを取得する
    grp = getgrnam("shim123");    //GIDを取得する
    ret = chown(file, -1, grp->gr_gid);
    if ( ret != 0 ) {
        printf("%s\n","chown aborted!!");
    }
}

// stat.hライブラリを使用してchmodする
// chmod 777 fileコマンド相当
int change_mod(char *file) {
/*    char file[1024] ="/home/shim123/dir_walk/dir"; */
    int  ret;
    ret = chmod(file,
	S_IRUSR | S_IWUSR | S_IXUSR |    /* rwx */
	S_IRGRP | S_IWGRP | S_IXGRP |    /* rwx */
	S_IROTH | S_IWOTH | S_IXOTH );   /* rwx */
    if ( ret != 0 ) {
        printf("%s\n","chmod aborted!!");
    }

}
//do_action()
void do_action(char *file) {
printf("%s\n", "***********************************************************");
// 読み取り用にテキストファイルをオープン
    FILE* list_fp = fopen( file, "r" );
    if( list_fp == NULL ){
        fputs( "ファイルオープンに失敗しました。\n", stderr );
        exit( EXIT_FAILURE );
    }
// 各行を読み取りながら、標準出力へ出力
    for( ;; ){
        char buf[1024];
        if( fgets( buf, sizeof(buf), fp ) == NULL ){
            if( feof( fp ) ){
                break;
            }
            else{
                fputs( "エラーが発生しました。\n", stderr );
                exit( EXIT_FAILURE );
            }
        }
        printf("%s", buf);
    }

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
            fprintf(fp, "%s\n", fpath); 
//            ret = change_mod(fpath);
//            ret = change_own(fpath);
            walk_dir(fpath);
        }
        else {
            printf("%s\n", fpath);
            fprintf(fp, "%s\n", fpath); 
//            ret = change_mod(fpath);
//            ret = change_own(fpath);
        }
    }
    chdir("..");
    closedir(dp);
}

