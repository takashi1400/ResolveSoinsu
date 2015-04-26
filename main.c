/*
 * main.c
 *
 *  Created on: 2015/04/26
 *      Author: koji
 */
#include <stdio.h>
#include <math.h>

//#define DEBUG
#define SPLIT_NUM		(20)
#define SPLIT_LENGTH	(3)
#define ERR_COUNT_MAX	(15)

/**
 *	@brief	答え用構造体
 **/
typedef struct{
	int a;
	int b;
	int c;
	int d;
} Answer;

/**
 * @brief	αx2+βx＋γ=0を解いて(ax+b)(cx+d)におけるa,b,c,dを求める
 * @return Answer*
 */
Answer* calc( int alpha, int beta, int ganma, Answer *ans ){
	//解の公式で正の解・負の解を取得
	float neg_ret = ( -beta - sqrt( pow( beta, 2 ) - 4 * alpha * ganma )  ) / (2 * alpha);
	float pos_ret = ( -beta + sqrt( pow( beta, 2 ) - 4 * alpha * ganma )  ) / (2 * alpha);

	float a = 1;		//答えのa
	float c = 1;		//答えのb
	float b = neg_ret;	//答えのc
	float d = pos_ret;	//答えのd

	float f;			//テンポラリ
	float neg_shousuu;	//
	float pos_shousuu;	//

	neg_shousuu = modff( b, &f );

#ifdef DEBUG
	printf( "neg_shousuu\t:%f\n", neg_shousuu );
	printf( "pos_shousuu\t:%f\n", pos_shousuu );
	printf( "a\t:%f\n", a );
	printf( "b\t:%f\n", b );
	printf( "pos_ret\t:%f\n", pos_ret );
	printf( "neg_ret\t:%f\n", neg_ret );
#endif

	//小数部がなくなるまで答えを倍にしていく
	while( (neg_shousuu = modff( b, &f )) != 0 ){
		//カウンタインクリメント
		a++;
		b += neg_ret;

		//怖いのでブレークポイント設定
		if( a >100 ){ return NULL; }
	}
	while( (pos_shousuu = modff( d, &f )) != 0 ){
		//カウンタインクリメント
		c++;
		d += pos_ret;

		//怖いのでブレークポイント設定
		if( c >100 ){ return NULL; }
	}

#ifdef DEBUG
	printf( "neg_shousuu\t:%f\n", neg_shousuu );
	printf( "pos_shousuu\t:%f\n", pos_shousuu );
	printf( "a\t:%f\n", a );
	printf( "b\t:%f\n", b );
	printf( "pos_ret\t:%f\n", pos_ret );
	printf( "neg_ret\t:%f\n", neg_ret );
#endif

	ans->a = (int)a;	//
	ans->b = (int)-b;	//因数分解の結果なので符号を逆にする
	ans->c = (int)c;	//
	ans->d = (int)-d;	//因数分解の結果なので符号を逆にする

	return ans;
}

int main( int argv, char** argc ){
	//αx2+βx＋γ。適当な組み合わせで初期化しておく
	int alpha	= 6;	//α
	int beta	= -1;	//β
	int ganma	= -15;	//γ

	//答え用構造体初期化
	Answer ans = {
		0, 0, 0, 0,
	};

	//コマンドライン引数解釈--------------------
	{
		char in_strs[ SPLIT_NUM ][ SPLIT_LENGTH ] = { 0 };	//split用
		char* p  = argc[ 1 ];		//

		//コマンドライン引数が存在すれば実行
		if( p ){
			int i = 0;
			int j = 0;
			int err_count = 0;

			while( i < SPLIT_NUM && err_count < ERR_COUNT_MAX && *p != 0 ){
				switch( *p ){
				//スプリット記号だったら
				case ',':
					//エスケープ記号入れて
					in_strs[i][j] = 0;
					//次の配列要素に以降
					j = 0;
					i++;
					break;

				//対象となる文字だったら
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				case '-':
					//配列にコピー
					in_strs[i][j] = *p;
					j++;
					break;

				//何もしない
				default:
					break;
				}

				//10文字以内でないとエスケープ
				err_count++;
				p++;
			}

#ifdef DEBUG
			{
				int i;	//カウンタ
				for( i = 0 ; i < SPLIT_NUM; ++i )
					printf( "%s\n", in_strs[ i ] );

				printf( "______________\n\n" );
			}
#endif

			//最後に値をセット
			alpha	= atoi( in_strs[0] );
			beta	= atoi( in_strs[1] );
			ganma	= atoi( in_strs[2] );

		}
	}	//end of コマンドライン引数解釈-----

	//実際の計算実行
	if( calc( alpha, beta, ganma, &ans) == NULL ){
		printf("エラー\n");
		return 1;
	}else{
		printf( "%d,%d,%d,%d\n", ans.a, ans.b, ans.c, ans.d );
		return 0;
	}
}

