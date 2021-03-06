#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { LEFT, RIGHT } NextSqueezeSide ;//数字を絞る方向を記録

typedef struct {
	int start;	//質問範囲の初め
	int end;	//質問範囲の終わり
	int answer;	//答えの数字
} GAME_PROP;

typedef struct {
	int result;	//ゲーム結果　0:失敗、1:成功
	int answer_num;	//回答回数
} GAME_RESULT;

//プロトタイプ宣言
void desideAnswer(GAME_PROP *game_prop);
int choiceNumber(int from, int to);
void executeQuize(GAME_PROP *game_prop, GAME_RESULT *game_result);
int squeeze(GAME_PROP *game_prop, NextSqueezeSide *next_squeeze_side);
void dump_game_prop(GAME_PROP *game_prop);


//答えの値を入力させて、GAME_PROP->answerにセットする。
void desideAnswer(GAME_PROP *game_prop){
	while(1){
		//答えを入力させる
		int answer = 0;
		int success = 0;
		printf("正解の数値を入力（親が入力）: \n");
		success = scanf("%d", &answer); //文字列を入れられるとおかしくなるが、とりあえず数値を入れることを前提にする。。
		if(success == EOF){
			printf("入力エラー\n");
		}else{
			//入力値のチェック
			if(game_prop->start <= answer && answer <= game_prop->end){
				//startとendの間で指定されている
				game_prop->answer = answer;
				return;
			}else{
				printf("%dから%dの間で指定してください。 \n", game_prop->start, game_prop->end);
			}
		}
	}
}

//回答入力を求めて、入力値から正解、不正解を判断し、正解ならGAME_RESULT->result = 1を代入する。
//不正解なら、ゲームオーバーとするのか、最チャレンジさせるのか判断する。
//ゲームオーバーとする場合はGAME_RESULT->result = 0を代入する。
//再チャレンジさせる場合は何もせず処理を終了する
void executeQuize(GAME_PROP *game_prop, GAME_RESULT *game_result){
	int input_num;
	while(1){
		//質問する。start-1 < x < end + 1 x = ?
		printf("%d < x < %d  x = ? \n", game_prop->start-1, game_prop->end+1);
		//入力させる
		int success = scanf("%d", &input_num);
		if(success){
			break;
		}
		//正しく数値を入力してください
		printf("正しく数値を入力してください\n");
	}
	//回答回数を追加
	game_result->answer_num++;

	//正解チェック
	if(input_num == game_prop->answer){
		//正解
		game_result->result = 1;
		return;
	}else{
		//不正解。もう絞る範囲がない場合ゲームオーバー判定。
		if(game_prop->start >= game_prop->answer && 
		   game_prop->end <= game_prop->answer){
				game_result->result = 0;
				return;
		}
	}
}

//出題範囲を絞る。「GAME_PROP->start側を絞る -> GAME_PROP->end側を絞る」と交互に絞る。
//ただし、片方がたまたま絞られなかったり、絞る範囲がなければもう片方が連続で絞られることになる。
//どちらも絞る範囲が充分に小さくて絞れない場合は失敗として0を返す。
//どちらかが絞れた時は成功として1を返す。
int squeeze(GAME_PROP *game_prop, NextSqueezeSide *next_squeeze_side){
	//まだ絞れる範囲があるか判断
	if(game_prop->start >= game_prop->answer && 
	   game_prop->end <= game_prop->answer){
		return 0;
	}
	if(*next_squeeze_side == LEFT){
		//前半を絞る
		//startからanswerまでの中からランダムで一つ選んでstartに代入する。
		int choiced_number = choiceNumber(game_prop->start, game_prop->answer);
		//もし選んだものがstartだった場合は後半を絞る
		if(choiced_number == game_prop->start){
			game_prop->end = choiceNumber(game_prop->answer, game_prop->end-1);
			*next_squeeze_side = LEFT;
		}else{
			game_prop->start = choiced_number;
			*next_squeeze_side = RIGHT;
		}

	}else{
		//後半を絞る
		//endからanswerまでの中からランダムで一つ選んでendに代入する。
		int choiced_number = choiceNumber(game_prop->answer, game_prop->end);
		//もし選んだものがendだった場合は前半を絞る
		if(choiced_number == game_prop->end){
			game_prop->start = choiceNumber(game_prop->start+1, game_prop->answer);
			*next_squeeze_side = RIGHT;
		}else{
			game_prop->end = choiced_number;
			*next_squeeze_side = LEFT;
		}
	}
	return 1;
}

//fromからtoの数値の中から一つをランダムに選んで返す。from, toを含む。
//とりあえずrand関数を使っている
int choiceNumber(int from, int to){
	int num_count = to - from + 1;
	int rand_num = rand();
	return rand_num % num_count + from;
}



void dump_game_prop(GAME_PROP *game_prop){
	printf("game_prop->start: %d\n", game_prop->start);
	printf("game_prop->end: %d\n", game_prop->end);
	printf("game_prop->answer: %d\n", game_prop->answer);
}

int main(){
	//rand用seedの初期化
	srand((unsigned)time(NULL));

	GAME_PROP game_prop = {1, 99, -1};	//答えが確定していない時は-1を入れておく
	GAME_RESULT game_result = {-1, 0};	//resultが確定していない時は-1を入れておく
	NextSqueezeSide next_squeeze_side = RIGHT;

	//回答の入力決定
	desideAnswer(&game_prop);
	//dump_game_prop(&game_prop);//テスト出力

	printf("%dから%dの自然数を当ててください\n", game_prop.start, game_prop.end);
	while(1){
		executeQuize(&game_prop, &game_result);

		if(game_result.result != -1){
			//結果が確定した。
			break;
		}else{
			if(!squeeze(&game_prop, &next_squeeze_side)){
				//エラー。これ以上絞れない。executeQuizeでゲームオーバーと判定されているはずで、ここに流れてくるケースはないはず。
				return 1;
			}
		}
	}

	if(game_result.result){
		//ゲームクリア。game_result.answre_num回でクリアしました
		printf("正解！%d回の入力で正解しました。\n", game_result.answer_num);
	}else{
		//ゲームオーバー。
		printf("ゲームオーバーです\n");
	}
	return 0;
}

