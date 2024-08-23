// tdcfit.C
// Usage：.x tdcfit.C("Aug22_300sec")

//#include "ROOTHeaders.h"

void tdcfit(TString filename){

  gROOT->SetBatch();

  TString filepath_root;

  Int_t num_plot = 7;

  Int_t tdc_min_gaus[num_plot];
  Int_t tdc_max_gaus[num_plot];
  Int_t init_const[num_plot];

  for(Int_t i = 0; i < num_plot; i++){
    cout << "Input fit range for TDC histogram [" << i << "]  :" << endl;
    cin >> tdc_min_gaus[i] >> tdc_max_gaus[i] >> init_const[i];
  }

  // 生成済のrootファイルを開く
  filepath_root = Form("./analysis/%s.root", filename.Data());
  TFile *file_root = new TFile(filepath_root, "update");

  // plotのcanvasごとcloneしてきて、graphを取り出す
  TString name_canvas_tdc[num_plot];
  TCanvas *c_tdc_fit[num_plot];
  TH1F *hist_fit[num_plot];
  TF1 *fit_expo[num_plot];
  for(Int_t i = 0; i < num_plot; i++){
    name_canvas_tdc[i] = Form("c_tdc%d_fit_%d-%d", i + 1, tdc_min_gaus[i], tdc_max_gaus[i]);
    c_tdc_fit[i] = new TCanvas();
    c_tdc_fit[i] = (TCanvas*)file_root->Get(Form("c_tdc%d", i + 1))->Clone();
    c_tdc_fit[i]->SetName(name_canvas_tdc[i]);
    hist_fit[i] = (TH1F*)c_tdc_fit[i]->FindObject(Form("tdchist%d", i + 1));

    fit_expo[i] = new TF1(Form("fit_expo_%d", i + 1), "expo+[2]", tdc_min_gaus[i], tdc_max_gaus[i]);
    fit_expo[i]->SetParameter(3, init_const[i]);
    // fit_expo[i]->SetParLimits(3, 0, 4);

    hist_fit[i]->SetTitle(Form("TDC ch vs count (fit %d - %d)", tdc_min_gaus[i], tdc_max_gaus[i]));
    fit_expo[i]->SetNpx(500); // fit_gaus描画時の点を増やす
    hist_fit[i]->Fit(Form("fit_expo_%d", i + 1), "R");
    hist_fit[i]->SetMaximum(50000);
  }

  //rootファイル保存
  TString name_save = Form("./analysis/%s", filename.Data());

  //先にファイル出力するとrootファイルにもsetoptfitが反映されてfit parameterが表示される
  for(Int_t i = 0; i < num_plot; i++){
    TString name_save_png = Form("%s_tdchist%d.png", name_save.Data(), i + 1);
    c_tdc_fit[i]->Print(name_save_png);
  }

  //既存の同名canvasがあれば削除
  for(Int_t i = 0; i < num_plot; i++){
    file_root->Delete(Form("%s;*", name_canvas_tdc[i].Data()));
  }

  //graphデータ書き込み
  for(Int_t i = 0; i < num_plot; i++){
    c_tdc_fit[i]->Write();
  }

  file_root->Close();

}

