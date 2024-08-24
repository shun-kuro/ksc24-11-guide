// chkhit.C
// Usage : .x chkhit.C("Aug24_N2_1400sec")
// テキストファイルを読んでhit数別にイベント数を出力

//#include "ROOTHeaders.h"

void chkhit(TString filename){

  TString filepath = Form("./data/%s", filename.Data());

	std::ifstream ifs(filepath.Data());
  if(!ifs){
    cerr << "Error: file not opened." << endl;
    return;
  }
	std::string str_row; // 1行目の文字列データ
	std::string str; // 1行目の文字列データをスペース区切りで格納する変数
  Int_t hit1 = 0;
  Int_t hit2 = 0;
  Int_t hit3 = 0;
  Int_t hit4 = 0;
	while(std::getline(ifs,str_row)){ // デフォルトは\n区切り
    Int_t hit_num = 0;
    Int_t data_num = 0;
    std::istringstream str_stream(str_row);
	  while(std::getline(str_stream, str, ' ')){ // デフォルトは\nなので、スペース区切りに変更
      // str_streamからスペース区切りでstrに次々と文字列を格納し、列数をカウント
      if(stoi(str) < 4095 && data_num > 6){
        hit_num++;
      }
      data_num++;
    };
    if(hit_num == 1){
      hit1++;
    }else if(hit_num == 2){
      hit2++;
    }else if(hit_num == 3){
      hit3++;
    }else if(hit_num > 3){
      hit4++;
    }
  }
	cout << "1-hits -> " << hit1 << endl;
	cout << "2-hits -> " << hit2 << endl;
	cout << "3-hits -> " << hit3 << endl;
	cout << "more hits -> " << hit4 << endl;

  TString name_text = Form("./data/%s_report.txt", filename.Data());
  ofstream reportfile(name_text.Data(), std::ios::trunc); // std::ios::truncで前の内容を消して上書き
  reportfile << "1-hits -> " << hit1 << endl;
  reportfile << "2-hits -> " << hit2 << endl;
  reportfile << "3-hits -> " << hit3 << endl;
  reportfile << "more-hits -> " << hit4 << endl;

  reportfile.close();
}