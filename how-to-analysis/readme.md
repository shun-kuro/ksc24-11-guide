# 解析の方法

## 解析スクリプトと、取得データ

スクリプトはLinux PCのDownload以下と、このgithubの[scripts](https://github.com/shun-kuro/ksc24-11-guide/tree/main/scripts)にあります。
LinuxPCからは、Powershell (Macの人はターミナル)で以下を実行するとダウンロードできます（filenameを適宜読み替えてください）。

```bash
cd ksc24
scp ksc@192.168.1.202:~/Download/filename ./
```

データはLinux PCのDownload以下にあります。（filenameを適宜読み替えてください）。

```bash
cd ksc24/data
scp ksc@192.168.1.202:~/Download/filename ./
```

## 解析スクリプトの実行方法

ROOTを開く

```bash
`C:\root_v6.32.02\bin\thisroot.bat`
root

# rootの中で
root[0] .x histTdc1.C("Aug22_1000sec")

```

実行すると、analysisフォルダの中に.rootファイルが保存される。

## .rootファイルの開き方

### まだROOTを開いていないとき

```bash
root -l analysis/Aug22_1000sec.root

# rootの中で
root[0] .ls

root[1] c_adc4->Draw()
```

### 既にROOTファイルを開いているとき
```bash
# rootの中で
root[0] TFile *_file0 = TFile::Open("analysis/Aug22_1000sec.root")

root[1] .ls

root[2] c_adc4->Draw()
```
