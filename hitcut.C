// hitcut.C
// Usage : .x hitcut.C("Aug24_N2_1400sec")
// テキストファイルを読んでhitの有無を0と1で出力

#include "ROOTHeaders.h"

void hitcut(TString filename){

  TString filepath = Form("./data/%s", filename.Data());

	std::ifstream ifs(filepath.Data());
  if(!ifs){
    cerr << "Error: file not opened." << endl;
    return;
  }

  std::string str_row; // 1行の文字列データ
  std::string str; // 1行の文字列データをスペース区切りで格納する変数

  TString name_text = Form("./data/%s_cut", filename.Data());
  ofstream reportfile(name_text.Data(), std::ios::trunc); // std::ios::truncで前の内容を消して上書き

	while(std::getline(ifs,str_row)){ // デフォルトは\n区切り
    Int_t tdchit[6] = {0, 0, 0, 0, 0, 0};
    Int_t data_num = 0;
    std::istringstream str_stream(str_row);
	  while(std::getline(str_stream, str, ' ')){ // デフォルトは\nなので、スペース区切りに変更
      // str_streamからスペース区切りでstrに次々と文字列を格納し、列数をカウント
      if(data_num == 7 && stoi(str) < 4095){
        tdchit[0]++;
      }
      if(data_num == 8 && stoi(str) < 4095){
        tdchit[1]++;
      }
      if(data_num == 9 && stoi(str) < 4095){
        tdchit[2]++;
      }
      if(data_num == 10 && stoi(str) < 4095){
        tdchit[3]++;
      }
      if(data_num == 11 && stoi(str) < 4095){
        tdchit[4]++;
      }
      if(data_num == 12 && stoi(str) < 4095){
        tdchit[5]++;
      }
      data_num++;
    }
  }
  cout << "all hits after cut -> " << event_num << endl;

  reportfile.close();
}