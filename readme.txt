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


◯使用方法は例えば、以下です：
	/home/shimura/dir_walk/suid_chmod /home/sendml >/dev/null
	※全て絶対パスを指定して起動する必要があります


内容を変更してみる、Git pullコマンド確認のため

再変更、Git fetch/mergeの確認のため

2021/01/23 追加　08:33
