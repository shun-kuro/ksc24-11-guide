# SSH経由でリモートマシンのROOTを使うとき

SSH経由（`ssh -XY hogehoge@example.jp`）でリモートのターミナルからROOTを実行すればよいが、GUIを使うには事前にローカル（自分のPC）でX serverのインストールが必要。

## Windows

MobaXtermが便利。X serverの機能と、SSHクライアント、他多数の機能を持つソフト。

https://mobaxterm.mobatek.net/download.html

Home Editionの緑色Installer Editionをダウンロードして、zipを解凍してからインストール。

このソフトでSSHすれば、Windows上に、リモートマシンのROOTのGUIを表示できる。

### PowerShellを使いたいとき

Windows上のVSCodeからSSHをしようとすると、デフォルトでPowerShellが使われるので、PowerShellからのsshでもGUIを使いたいときがある。その対処法。

1. MobaXtermをインストール。

2. PowerShellを管理者として実行し、以下を実行。

```powershell
[System.Environment]::SetEnvironmentVariable("DISPLAY", "localhost:0.0", "User")
```

3. PowerShellを開きなおし、以下を実行して`localhost:0.0`と表示されればOK。

```powershell
$env:DISPLAY
```

4. PowerShellまたはVSCodeからSSHをする前に、バックグラウンドでMobaXtermを起動しておけばよい（MobaXtermからSSHする必要はない）。

## Mac

以下からxquartzをインストールすればよい（インストール後再起動が必要かも）。

https://www.xquartz.org/