#include <stdio.h>

enum SqueezeSide { LEFT, RIGHT };//数字を絞る方向を記録

typedef struct {
	int start;	//質問範囲の初め
	int end;	//質問範囲の終わり
	int answer;	//答えの数字
} GAME_PROP;

typedef struct {
	int result;	//ゲーム結果　0:失敗、1:成功
	int answer_num;	//回答回数
} GAME_RESULT;

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

//結果(クリア or ゲームオーバー)とクリアの場合は回答回数を返す
void executeGame(GAME_PROP *game_prop, GAME_RESULT *game_result){
	game_result->result = 1;
	game_result->answer_num = 10;
	//ゲームスタート
	/*
	while(true){
		//質問する。start-1 < x < end + 1 x = ?
		//入力させる
		//入力値のチェック
		if(入力値が正しくない){
			//正しく数値を入力してください
			continue;
		}
		//回答回数を追加
		answer_num = answer_num + 1;

		//正解チェック
		if(入力値 == answer){
			//正解
			*result = 1;
			return;
		}

		//不正解。範囲を絞る。
		//2回いないに範囲を絞れない状況はゲームオーバー。LEFT側、RIGHT側どちらも範囲を絞れなかった = 最小まで絞っても答えられなかった。
		int try_count=0;
		for(; trytry_count<2; trtrytry_count++){
			if(SqueezeSide == LEFT){
				//前半を絞る
				//startからstart_limitの中からランダムで一つ選んでstartに代入する。
				SqueezeSide = RIGHT;
				//もし選んだものがstartだった場合は後半を絞る
				if(startが選ばれた){
					continue;
				}else{
					continue2;
				}

			}else{
				//後半を絞る
				//endからend_limitの中からランダムで一つ選んでendに代入する。
				SqueezeSide = LEFT;
				//もし選んだものがendだった場合は前半を絞る
				if(endが選ばれた){
					continue;
				}else{
					continue2
				}
			}
		}
		if(trytry_count >= 2){
			//ゲームオーバー
			*result = 0;
			return;
		}
	}
	*/
}

int main(){
	GAME_PROP game_prop = {1, 99, -1};	//答えはとりあえず-1を入れておく
	GAME_RESULT game_result = {0, 0};

	//回答の入力決定
	desideAnswer(&game_prop);

	executeGame(&game_prop, &game_result);

	if(game_result.result){
		//ゲームクリア。game_result.answre_num回でクリアしました
		printf("正解！%d回の入力で正解しました。\n", game_result.answer_num);
	}else{
		//ゲームオーバー。
		printf("ゲームオーバーです\n");
	}
	return 0;
}

