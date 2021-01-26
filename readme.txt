◯suid_chmodについて
　　シェルプログラム(home/script/shell/sendml/apache_ses.sh)の代替品
　　C言語で作成した実行モジュールなのでSUIDを使用することができます。
　　コンパイル方法について：

　　◯ make
　　◯ sudo chown root.root suid_mod
　　◯ sudo chmod u+s suid_chmod


◯機能内容について
　　シェルプログラム(home/script/shell/sendml/apache_ses.sh)と同様の機能を実行する
　　◯指定配下のファイル/ディレクトリを全て「eigyo」グループに変更
　　◯指定配下のファイル/ディレクトリを全てモード「777」に変更


◯使用方法は例えば、以下です：
        /home/shimura/dir_walk/suid_chmod /home/sendml >/dev/null
        ※全て絶対パスを指定して起動する必要があります

◯ソースファイルについて
        ◯suid_chmod.ca メインプログラム、ディレクトリを再帰的に歩き回る
        ◯change_own.ca ファイルディレクトリの所有者を変更する
        ◯change_mod.ca ファイルディレクトリのモードを変更する(SUID設定)

