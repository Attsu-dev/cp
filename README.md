# cp

C++で競技プログラミングに取り組むための個人用環境です。

問題ごとのテンプレート、自作ライブラリ、VS Codeスニペット、サンプルテストやランダムテストを実行するためのシェル関数をまとめています。

## 必要な環境

- Bash
- C++23に対応したG++
- Python 3
- [online-judge-tools](https://github.com/online-judge-tools/oj)（`oj`）
- [online-judge-template-generator](https://github.com/online-judge-tools/template-generator)（`oj-bundle`）
- [atcoder-cli](https://github.com/Tatamo/atcoder-cli)（`acc`）
- Visual Studio Codeのコマンドラインツール（`code`）

`s`および`t`コマンドは、WSLからWindowsのクリップボードを利用するために`iconv`と`clip.exe`も使用します。

## セットアップ

リポジトリをクローンし、使用する外部ライブラリを取得します。

```bash
git clone https://github.com/Attsu-dev/cp.git ~/cp
cd ~/cp
git submodule update --init third_party/acl third_party/nyaan
```

ACLがテスト用に参照しているサブモジュールは、この環境を使うだけなら初期化不要です。

環境変数とシェル関数を読み込みます。継続して使用する場合は、次の内容を`~/.bashrc`などに追加します。

```bash
export CP_ROOT="$HOME/cp"
source "$CP_ROOT/tools/commands.sh"
```

コンテスト用ディレクトリはGitで管理しないため、初回のみ作成します。

```bash
mkdir -p "$CP_ROOT/contests/atcoder" "$CP_ROOT/contests/cf"
```

`acc`の設定後、AtCoder用テンプレートとVS Codeスニペットを反映できます。

```bash
apply-settings
```

## 基本的な使い方

### 1問だけ解く

作業ディレクトリで問題URLを指定すると、`main.cpp`の作成、サンプルケースのダウンロード、VS Codeでのファイル表示を行います。

```bash
n https://atcoder.jp/contests/abc001/tasks/abc001_1
```

解答を書いたら、提出コードの生成とサンプルテストを実行します。

```bash
t
```

AtCoder Libraryを使用している場合は、`-acl`を指定します。

```bash
t -acl
```

`t`は、最初に`s`を実行してから、sanitizer付きで`main.cpp`をコンパイルして`oj t`を実行します。

サンプルテストを行わず、提出コードの生成だけを行うこともできます。

```bash
s
s -acl
```

`s`は次の処理を行います。

1. 自作ライブラリとNyaanのライブラリを`oj-bundle`で展開する
2. 未使用のテンプレート要素を削除して`submit.cpp`を生成する
3. `-acl`指定時はACLも展開する
4. 提出コードをWindowsのクリップボードへコピーする

`s`または`t`を実行すると、既存の`submit.cpp`は上書きされます。

### コンテストを開始する

AtCoderでは、`acc`を使ってコンテスト用ディレクトリを作成します。

```bash
atcoder-start abc001
```

Codeforcesでは、AからHまでの作業ディレクトリを作成し、各問題のサンプルケースを取得します。

```bash
cf-start 1234
```

同じコンテスト内の別問題へ移動するときは、次のように指定します。

```bash
to b
```

### コンパイルする

`g`はインクルードパス、警告、AddressSanitizer、UndefinedBehaviorSanitizerを設定したG++のラッパーです。

```bash
g main.cpp
g -O2 main.cpp -o main
```

### ランダムテストを行う

まず、現在の解答を愚直解としてコピーし、入力生成器を用意します。

```bash
randomtest-init
```

`naive.cpp`に愚直解、`generate.py`に入力生成処理を書いた後、ランダムテストを開始します。

```bash
randomtest
```

出力が一致しなかった入力と期待値は、`test/random-N.in`と`test/random-N.out`に保存されます。

## コマンド一覧

| コマンド | 内容 |
| --- | --- |
| `g ...` | sanitizerと警告を有効にしてC++をコンパイルする |
| `n URL` | テンプレートとサンプルケースを用意する |
| `s` | 提出コードを生成し、クリップボードへコピーする |
| `s -acl` | ACLを含む提出コードを生成する |
| `t` | `s`を実行してからサンプルテストを行う |
| `t -acl` | `s -acl`を実行してからサンプルテストを行う |
| `atcoder-start ID` | AtCoderのコンテストを開始する |
| `cf-start ID` | Codeforcesのコンテストを開始する |
| `to NAME` | 同じコンテスト内の別ディレクトリへ移動する |
| `randomtest-init` | 愚直解と入力生成器の雛形を用意する |
| `randomtest` | 解答と愚直解をランダムテストで比較する |
| `zip2test ID` | ダウンロードしたサンプルZIPを`test/`へ展開する |
| `apply-settings` | AtCoder用テンプレートとVS Codeスニペットを更新する |
| `save-lib MESSAGE` | 設定を反映し、全変更をコミットして`main`へpushする |

`save-lib`は内部で`git add .`を実行します。意図しないファイルを含めないよう、実行前に`git status`を確認してください。

## ディレクトリ構成

```text
.
├── library/       自作ライブラリと共通テンプレート
├── snippets/      VS Codeスニペットの生成元
├── templates/     通常・Codeforces・ICPC用のコード雛形
├── third_party/   ACLとNyaanのライブラリ（Git submodule）
├── tools/         シェル関数とコード生成用スクリプト
├── contests/      コンテストごとの解答（Git管理外）
└── workspace/     一時的な作業場所（Git管理外）
```

`snippets/*.hpp`を変更した後は、`apply-settings`または次のコマンドで`.vscode/cpp.code-snippets`を再生成します。

```bash
python3 "$CP_ROOT/tools/make_snippets.py"
```

## 外部ライブラリ

- [AtCoder Library](https://github.com/atcoder/ac-library)
- [Nyaan's Library](https://github.com/NyaanNyaan/library)

外部ライブラリには、それぞれのリポジトリに含まれるライセンスが適用されます。

## License

このリポジトリの自作部分は[CC0 1.0 Universal](LICENSE)で公開しています。
