◯suid_chmodについて
　　シェルプログラム(home/script/shell/sendml/apache_ses.sh)の代替品
　　C言語で作成した実行モジュールなのでSUIDを使用することができます。
　　コンパイル方法について：
　　◯ gcc suid_chmod.c -o suid_mod
　　◯ sudo chown root.root suid_mod
　　◯ sudo chmod u+s suid_chmod


◯機能内容について
　　シェルプログラム(home/script/shell/sendml/apache_ses.sh)と同様の機能を実行する
　　◯指定配下のファイル/ディレクトリを全て「eigyo」グループに変更
　　◯指定配下のファイル/ディレクトリを全てモード「777」に変更

