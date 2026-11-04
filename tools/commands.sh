# オプションを指定してコンパイル（追加オプションも指定可能）
# 例1: g main.cpp
# 例2: g main.cpp -O2 -o main
function g() {
    g++ -std=c++23 \
        -I "$CP_ROOT/library" \
        -I "$CP_ROOT/third_party" \
        -I "$CP_ROOT/third_party/acl" \
        -g -Wall -Wextra \
        -fsanitize=address,undefined \
        "$@"
}

# 現在のディレクトリに解答コードとサンプルを用意する
# 例: n https://atcoder.jp/contests/abc001/tasks/abc001_1
function n() {
    cp "$CP_ROOT/templates/main.cpp" main.cpp || return
    rm -r test/
    oj d "$1"
    code --goto main.cpp:4:3
}

# 提出コードをクリップボードにコピー
# 例1: s
# 例2: s -acl （ACLも展開する）
function s() {
    [[ -f main.cpp ]] || return
    oj-bundle \
        -I "$CP_ROOT/library/" \
        -I "$CP_ROOT/third_party/" \
        main.cpp > bundled.cpp 2>/dev/null || return
    python3 "$CP_ROOT/tools/cleaner.py" < bundled.cpp > submit.cpp || return
    rm bundled.cpp

    if [[ "${1:-}" == "-acl" ]]; then
        python3 "$CP_ROOT/third_party/acl/expander.py" \
            --lib "$CP_ROOT/third_party/acl/" submit.cpp || return
        mv combined.cpp submit.cpp
    fi

    printf '\n// library: https://github.com/Attsu-dev/cp\n' >> submit.cpp

    iconv -t sjis submit.cpp | clip.exe || return
    printf '📋 Copied submit.cpp to clipboard!\n'
}

# 提出コードをクリップボードにコピー & サンプルテストを実行
# 例1: t
# 例2: t -acl （ACLも展開する）
function t() {
    s "$@" || return
    g main.cpp || return
    oj t
}

# AtCoderのコンテストを開始する
# 例: atcoder-start abc001
function atcoder-start() {
    cd "$CP_ROOT/contests/atcoder"
    acc n "$1" || return
    cd "$1/a/" || return
    code --goto main.cpp:4:3
}

# Codeforcesのコンテストを開始する
# 例: cf-start 1234
function cf-start() {
    local contestID="$1"
    local root="$CP_ROOT/contests/cf/$contestID"

    for p in {a..h}; do
        mkdir -p "$root/$p"
        cp "$CP_ROOT/templates/cf.cpp" "$root/$p/main.cpp"
        cd "$root/$p"
        oj d "https://codeforces.com/contest/$contestID/problem/${p^^}"
    done

    cd "$root/a" || return
    code --goto main.cpp:4:3
}

# 同じコンテスト内の別の問題へ移動する
# 例: to b
function to() {
    cd "../$1/" || return
    code --goto main.cpp:4:3
}

# ストレステスト用のコードと入力生成器を作成する
# 例: stress-init
function stress-init() {
    cp "$CP_ROOT/templates/generate.py" .
    cp main.cpp naive.cpp
    code naive.cpp generate.py
}

# ストレステストを実行する
# 例: stress
function stress() {
    g -O2 main.cpp || return
    g -O2 naive.cpp -o naive || return

    local tmp=".stress"
    mkdir -p "$tmp" || return

    local i=0

    while true; do
        ((++i))

        python3 generate.py > "$tmp/input.txt" || return

        ./naive < "$tmp/input.txt" > "$tmp/expected.txt" || {
            printf '\nnaive.cpp failed\n' >&2
            return 1
        }

        ./a.out < "$tmp/input.txt" > "$tmp/output.txt"
        local status=$?

        printf '\rTested: %d cases' "$i"

        if (( status != 0 )) || ! diff -q "$tmp/output.txt" "$tmp/expected.txt" > /dev/null; then

            printf '\n'

            if (( status != 0 )); then
                printf '\nmain.cpp failed\n' >&2
            fi

            printf '\n[input]\n'
            cat "$tmp/input.txt"
            printf '\n[output]\n'
            cat "$tmp/output.txt"
            printf '\n[expected]\n'
            cat "$tmp/expected.txt"

            return 1
        fi
    done
}

# ストレステストで失敗したテストケースをtest/に保存する
# 例: stress-save
stress-save() {
    mkdir -p test || return

    local n=1
    while [[ -e "test/stress-$n.in" ]]; do
        ((++n))
    done

    cp .stress/input.txt "test/stress-$n.in" || return
    cp .stress/expected.txt "test/stress-$n.out" || return

    printf 'Saved: test/stress-%d.{in,out}\n' "$n"
}

# downloads/samples-?.zip を test/ に展開する
# 例: zip2test A
function zip2test() {
    unzip "$HOME/downloads/samples-$1.zip" -d test || return
    rm "$HOME/downloads/samples-$1.zip"*
    for f in test/*.ans;do
        mv "$f" "${f%.ans}.out"
    done
}

# シェル関数・スニペット・テンプレートの設定を反映する
# 例: apply-settings
function apply-settings() {
    source "$CP_ROOT/tools/commands.sh"
    python3 "$CP_ROOT/tools/make_snippets.py"
    cp "$CP_ROOT/templates/main.cpp" "$HOME/.config/atcoder-cli-nodejs/cpp/main.cpp"
}

# GitHubにライブラリを保存する
# 例: save-lib update
function save-lib() (
    local commit_message="${1:-update}"

    apply-settings

    cd "$CP_ROOT"
    git add .
    git commit -m "$commit_message"
    git push origin main
)

# acc のセッションが切れていないか確認する
acc session 2>/dev/null | grep -qx 'OK' || echo "⚠️ acc のセッションが切れています！ https://pypi.org/project/aclogin/"
