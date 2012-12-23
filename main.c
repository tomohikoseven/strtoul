/*
 *  strtoul()研究
 *      数値文字列のみ数値へ変換し、文字を含む数値文字列をエラーとしたい。
 *     そのためには、どのようなエラー条件を設定すればよいか。
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define SIZE 11

/* strtoul()の戻り値、endptr、errnoの調査用関数 */
void
_my_strtoul( char *strNum )
{
    unsigned long   _ret        = 0L;
    char            *_endptr    = NULL;

    errno   = 0;

    _ret    = strtoul( strNum, &_endptr, 10 );

    printf("%11s %11lu %11s %11d\n", strNum, _ret, _endptr, errno );
}

/* エラー判定ができているか調査する関数 */
void
_err_judge( char *strNum )
{
    unsigned long   _ret        = 0L;
    char            *_endptr    = NULL;

    errno = 0;
    _ret    = strtoul( strNum, &_endptr, 10 );
    if( 0 != strlen( _endptr ) || 0 != errno )
    {
        printf("error:(%s)\n", strNum );
    }
}

int
main( int argc, char** argv )
{
    unsigned long   _ret        = 0L;

    printf(" === strtoul 研究 ( ERANGE=%d )===\n", ERANGE );
    printf("%11s %11s %11s %11s\n", "input", "return", "endptr", "errno" );

    /* 数値 */
    _my_strtoul( "-1" );
    _my_strtoul( "0" );
    _my_strtoul( "1" );
    _my_strtoul( "100" );
    _my_strtoul( "4294967295" );    // ULONG_MAX    (32bit 環境のため)
    _my_strtoul( "4294967296" );    // ULONG_MAX+1  (32bit 環境のため)

    /* 文字含む */
    _my_strtoul( "a" );
    _my_strtoul( "ab" );
    _my_strtoul( "10ab" );
    _my_strtoul( "a10b" );
    _my_strtoul( "ab10" );

    /* エラー判定 */
    printf(" === エラー判定結果(エラーであるもののみ出力される) ===\n");
    _err_judge( "-1" );         // OK
    _err_judge( "0" );          // OK
    _err_judge( "1" );          // OK
    _err_judge( "100" );        // OK
    _err_judge( "4294967295" ); // OK
    _err_judge( "4294967296" ); // NG ===> error:(4294967296)

    /* 文字含む */
    _err_judge( "a" );          // NG ===> error:(a)
    _err_judge( "ab" );         // NG ===> error:(ab)
    _err_judge( "10ab" );       // NG ===> error:(10ab)
    _err_judge( "a10b" );       // NG ===> error:(a10b)
    _err_judge( "ab10" );       // NG ===> error:(ab10)

    return 0;
}
