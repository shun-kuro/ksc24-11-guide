// tdccalib.C
// TDCの線形性の確認

// Usage : .x tdccalib.C("tdccalib") (dataフォルダにtdccalib.datを置く)

//#include "ROOTHeaders.h"

void tdccalib(TString filename){

  TCanvas *pol1fit_c = new TCanvas("pol1fit_c", "hist", 800, 600);
  TTree* tree_tdc = new TTree("tree_tdc","tree_tdc");

  // 保存用ファイル名生成
  TString name_save = Form("./analysis/%s_%s", filename.Data(), "tdccalib_fit");
  TString name_root = Form("%s.root", name_save.Data());
  TString name_png = Form("%s.png", name_save.Data());

  TString file_tdcfit = Form("./data/%s.dat", filename.Data());

  tree_tdc->ReadFile(file_tdcfit, "delay/I:tdc");

  Int_t n_tree = tree_tdc->GetEntries();

  tree_tdc->Draw("delay:tdc");

  TGraph *g = new TGraph(n_tree, tree_tdc->GetV1(), tree_tdc->GetV2());

  TF1 *fit1 = new TF1("fit1", "pol1");
  pol1fit_c->SetGrid();

  // fitの初期値の設定
  //fit1->SetParameter(0, 20);
  //fit1->SetParameter(1, 0.1);

  fit1->SetNpx(500); // fit_gaus描画時の点を増やす
  g->Fit("fit1");

  g->GetHistogram()->SetMaximum(4000);
  g->GetHistogram()->SetMinimum(0);

  g->SetMarkerStyle(4);
  g->SetMarkerSize(1);
  g->SetTitle(Form("TDC calibration (%s);Delay;TDC", filename.Data()));

  //軸ラベルを表示させる
  pol1fit_c->Modified();
  pol1fit_c->Update();
  gStyle->SetOptStat(2211);
  gStyle->SetOptFit(222);
  gStyle->SetStatH(0.12);
  gStyle->SetStatY(0.5);

  g->Draw("AP");

  //Fit結果保存
  pol1fit_c->Print(name_png);

  TFile *file_root = new TFile(name_root, "update");
  file_root->Delete("pol1fit_c;*");
  pol1fit_c->Write();

  delete tree_tdc;
  delete pol1fit_c;
  delete g;
  delete fit1;
  file_root->Close();

}
