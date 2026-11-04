# cp

競技プログラミング用の C++ ライブラリと開発環境を管理するリポジトリです。

## 主な機能

- 問題の準備
    - テンプレートの配置
    - サンプルケースの取得
- サンプルテスト
- 提出コードの生成
    - oj-bundle によるライブラリの展開
    - 不要なテンプレート要素の削除
- ストレステスト
    - 愚直解との出力比較
    - 失敗したテストケースの保存

## 必要な環境

WSL (Ubuntu) + VS Code での使用を想定しています。

- Bash
- g++（C++23 対応）
- Python 3
- Git
- [online-judge-tools](https://github.com/online-judge-tools/oj)（`oj`）
- [online-judge-template-generator](https://github.com/online-judge-tools/template-generator)（`oj-bundle`）
- [atcoder-cli](https://github.com/Tatamo/atcoder-cli)（`acc`）

## セットアップ

```bash
git clone https://github.com/Attsu-dev/cp.git ~/cp
cd ~/cp
git submodule update --init third_party/acl third_party/nyaan
```

`~/.bashrc` などに設定を追加します。

```bash
export CP_ROOT="$HOME/cp"
source "$CP_ROOT/tools/commands.sh"
```

設定を反映させるため、ターミナルを再起動するか、次のコマンドを実行します。

```bash
source ~/.bashrc
```

作業用ディレクトリを作成します。

```bash
mkdir -p "$CP_ROOT/contests/atcoder" "$CP_ROOT/contests/cf" "$CP_ROOT/workspace"
```

解答コードのテンプレートを反映させます。（accの初期設定が完了していることが前提です）

```bash
mkdir -p "$HOME/.config/atcoder-cli-nodejs/cpp"
apply-settings
```

## 基本的な使い方

### 1. 問題を準備する

任意の作業ディレクトリで、問題 URL から解答ファイルとサンプルケースを用意します。

```bash
n https://atcoder.jp/contests/abc001/tasks/abc001_1
```

AtCoder のコンテストを開始するときは、次のコマンドを使用します。

```bash
atcoder-start abc001
```

同じコンテスト内の別の問題へは `to` で移動できます。

```bash
to b
```

### 2. 解答をテストする

```bash
t
```

`t` は提出用の `submit.cpp` を生成してクリップボードへコピーした後、`main.cpp` をコンパイルし、`oj t` でサンプルテストを実行します。

ACL を展開したい場合は `-acl` を指定します。

```bash
t -acl
```

### 3. 提出コードを生成する

テストを実行せず、提出コードの生成とクリップボードへのコピーだけを行う場合は `s` を使います。

```bash
s
s -acl
```

### 4. ストレステストを実行する

```bash
stress-init
```

`main.cpp` を `naive.cpp` にコピーし、入力生成器 `generate.py` を配置します。`naive.cpp` に愚直解、`generate.py` にテストケース生成処理を書いた後、次を実行します。

```bash
stress
```

解答と愚直解の出力を繰り返し比較し、不一致や実行時エラーが発生すると停止します。

失敗したテストケースは、次のコマンドでサンプルテスト用に保存できます。

```bash
stress-save
```

### その他の機能
その他のコマンドについては、[tools/commands.sh](tools/commands.sh) のコメントを参照してください。


## ディレクトリ構成

```text
.
├── .vscode/       VS Code の設定・生成されたスニペット
├── library/       自作ライブラリ
├── snippets/      スニペットの生成元（*.hpp）
├── templates/     解答・ランダム入力生成用テンプレート
├── third_party/   外部ライブラリ（Git submodule）
├── tools/         シェル関数・提出コード加工等のスクリプト
├── contests/      コンテスト別の作業場所
└── workspace/     単発の問題等を解く作業場所
```

解答コードの保存は目的としていないため、`contests/` と `workspace/` は Git 管理外です。


## ライセンス

このリポジトリの自作部分は [CC0 1.0 Universal](LICENSE) で公開しています。
外部ライブラリにはそれぞれのライセンスが適用されます。
