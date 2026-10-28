function g() {
    g++ -std=c++23 \
        -I "$CP_ROOT/library" \
        -I "$CP_ROOT/third_party" \
        -I "$CP_ROOT/third_party/acl" \
        -g -Wall -Wextra \
        -fsanitize=address,undefined \
        "$@"
}

function n() {
    cp "$CP_ROOT/templates/main.cpp" main.cpp || return
    rm -r test/
    oj d "$1"
    code --goto main.cpp:4:3
}

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

function t() {
    s "$@" || return
    g main.cpp || return
    oj t
}

function atcoder-start() {
    cd "$CP_ROOT/contests/atcoder"
    acc n "$1" || return
    cd "$1/a/" || return
    code --goto main.cpp:4:3
}

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

function to() {
    cd "../$1/" || return
    code --goto main.cpp:4:3
}

function randomtest-init() {
    cp "$CP_ROOT/templates/generate.py ."
    cp main.cpp naive.cpp
    code naive.cpp generate.py
}

function randomtest() (
    g -O2 main.cpp || return 1
    g -O2 naive.cpp -o naive || return 1

    local tmp
    tmp=$(mktemp -d) || return 1
    trap 'rm -rf "$tmp"' EXIT

    local i=0

    while true; do
        ((++i))

        python3 generate.py > "$tmp/input" || return 1
        ./a.out < "$tmp/input" > "$tmp/output" || return 1
        ./naive < "$tmp/input" > "$tmp/expected" || return 1

        printf '\rTested: %d cases' "$i"

        if ! diff -q "$tmp/output" "$tmp/expected" > /dev/null; then
            mkdir -p test || return 1

            local n=1
            while [[ -e "test/random-$n.in" || -e "test/random-$n.out" ]]; do
                ((++n))
            done

            cp "$tmp/input" "test/random-$n.in"
            cp "$tmp/expected" "test/random-$n.out"

            echo
            echo "[input]"
            cat "$tmp/input"
            echo
            echo "[output]"
            cat "$tmp/output"
            echo
            echo "[expected]"
            cat "$tmp/expected"
            return 1
        fi
    done
)

function zip2test() {
    unzip "$HOME/downloads/samples-$1.zip" -d test || return
    rm "$HOME/downloads/samples-$1.zip"*
    for f in test/*.ans;do
        mv "$f" "${f%.ans}.out"
    done
}

function apply-settings() {
    source "$CP_ROOT/tools/commands.sh"
    python3 "$CP_ROOT/tools/make_snippets.py"
    cp "$CP_ROOT/templates/main.cpp" "$HOME/.config/atcoder-cli-nodejs/cpp/main.cpp"
}

function save-lib() (
    local commit_message="${1:-update}"

    apply-settings

    cd "$CP_ROOT"
    git add .
    git commit -m "$commit_message"
    git push origin main
)
