Cライブラリのstrtoul()について、少し調査した。  
そのときの生成物を置く。

[調査内容]
  数値文字列のみ数値へ変換し、文字を含む数値文字列をエラーとしたい。
 そのためには、どのようなエラー条件を設定すればよいか。

[具体例]
 -1             #=> OK
 10             #=> OK
 a10            #=> NG(エラー)
 10a9           #=> NG(エラー)
 ULONG_MAX + 1  #=> NG(エラー)

[結果]
 errno と strtoul()の第2引数(endptr)の長さで判定する。

