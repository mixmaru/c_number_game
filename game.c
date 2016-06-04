#include <stdio.h>

enum SqueezeSide { LEFT, RIGHT };//数字を絞る方向を記録
int main(){
	int start = 1;	//質問範囲の初め
	int end = 99;	//質問範囲の終わり
	int answer;	//答えの数字
	int start_limit;	//前半を絞り込む時の範囲の最大値
	int end_limit;		//後半を絞り込む時の範囲の最小値
	int answer_num = 0; 	//回答回数

	/*
	do{
		//答えを入力させる。
		//入力値のチェック
		if(入力値が正しくない){
			//正しく数値を入力してください
			int input_ok = false;
		}else{
			int input_ok = true;
		}
		
	}while(input_ok);

	//変数の初期化
	answer = 入力された数字
	start_limit = answer - 1;
	end_limit = answer + 1;

	//ゲームスタート
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
			//正解です。おめでとうございます。answer_num回で答えられました。プログラムの終了
			break;
		}
		//不正解。範囲を絞る。
		//2回いないに範囲を絞れない状況はゲームオーバー。LEFT側、RIGHT側どちらも範囲を絞れなかった = 最小まで絞っても答えられなかった。
		for(int i=0; i<2; i++){
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
		//ゲームオーバー
		return 0;
	}

	*/
	return 0;
}

