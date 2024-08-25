// hist.C

//#include "ROOTHeaders.h"

void histTdc7(TString filename) {

  TString filepath;

  // treeの作成
  TTree *tree = new TTree("tree", "tree");

  // テキストファイルの読み込み
  filepath = Form("./data/%s", filename.Data());
  tree->ReadFile(filepath, "adc1/I:adc2/I:adc3:adc4:adc5:adc6:tdc1:tdc2:tdc3:tdc4:tdc5:tdc6:tdc7");

  // canvasの作成
  TString name_canvas_tdc = "c_tdc";
  TString name_canvas_adc = "c_adc";
  TCanvas *tdc_c[7];
  TH1F *tdchist[7];
  TCanvas *adc_c[6];
  TH1F *adchist[6];

  for(Int_t i = 0; i < 7; i++){
    tdc_c[i] = new TCanvas(Form("%s%d", name_canvas_tdc.Data(), i + 1), "canvas", 800, 600);
    tdchist[i] = new TH1F(Form("tdchist%d", i + 1), ";TDC Ch;Count",2250, 0, 4500);
  }

  for(Int_t i = 0; i < 6; i++){
    adc_c[i] = new TCanvas(Form("%s%d", name_canvas_adc.Data(), i + 1), "canvas", 800, 600);
    adchist[i] = new TH1F(Form("adchist%d", i + 1), ";ADC Ch;Count",2250, 0, 4500);
  }

  // ヒストグラムの描画
  for(Int_t i = 0; i < 7; i++){
    tdc_c[i]->cd();
    tree->Draw(Form("tdc%d>>tdchist%d", i + 1, i + 1));
  }

  for(Int_t i = 0; i < 6; i++){
    adc_c[i]->cd();
    tree->Draw(Form("adc%d>>adchist%d", i + 1, i + 1));
  }

  // rootファイル保存
  TString name_save = Form("./analysis/%s", filename.Data());
  TString name_root = Form("%s.root", name_save.Data());
  TFile *file_root = new TFile(name_root, "update");
  // 既存の同名treeがあれば削除
  file_root->Delete("tree;1");

  for(Int_t i = 0; i < 7; i++){
    file_root->Delete(Form("%s%d;*", name_canvas_tdc.Data(), i + 1));
  }

  for(Int_t i = 0; i < 6; i++){
    file_root->Delete(Form("%s%d;*", name_canvas_adc.Data(), i + 1));
  }
  // treeデータ（数値データ）書き込み
  tree->Write();
  // histデータ書き込み
  for(Int_t i = 0; i < 7; i++){
    tdc_c[i]->Write();
  }

  for(Int_t i = 0; i < 6; i++){
    adc_c[i]->Write();
  }

  file_root->Close();

  for(Int_t i = 0; i < 7; i++){
    delete tdc_c[i];
  }

  for(Int_t i = 0; i < 6; i++){
    delete adc_c[i];
  }
}
