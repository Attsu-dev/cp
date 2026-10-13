alias g='g++ -std=c++23 -I ~/cp/library/ -I ~/cp/ac-library -g -Wall -Wextra -fsanitize=address,undefined'

function n() {
    cp ~/cp/templates/main.cpp main.cpp
    rm -r test/
    oj d "$1"
    code --goto main.cpp:4:3
}

function t() {
    [[ -f main.cpp ]] || return
    oj-bundle -I ~/cp/library/ main.cpp > bundled.cpp 2>/dev/null || return
    python3 ~/cp/scripts/cleaner.py < bundled.cpp > submit.cpp || return
    rm bundled.cpp

    if [[ "$1" == "-acl" ]]; then
        python3 ~/cp/ac-library/expander.py --lib ~/cp/ac-library/ submit.cpp || return
        mv combined.cpp submit.cpp
    fi

    cat submit.cpp | iconv -t sjis | clip.exe
    g main.cpp || return
    oj t
}

function atcoder-start() {
    cd ~/cp/contests/atcoder
    acc n "$1" || return
    cd "$1/a/" || return
    code --goto main.cpp:4:3
}

function cf-start() {
    local contestID="$1"
    local root="$HOME/cp/contests/cf/$contestID"

    for p in {a..h}; do
        mkdir -p "$root/$p"
        cp "$HOME/cp/templates/mtest.cpp" "$root/$p/main.cpp"
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
    cp ~/cp/templates/generate.py .
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
    source ~/cp/scripts/commands.sh
    python3 ~/cp/scripts/make_snippets.py
    cp ~/cp/templates/main.cpp ~/.config/atcoder-cli-nodejs/cpp/main.cpp
}

function save-lib() (
    local commit_message="${1:-update}"

    apply-settings

    git add .
    git commit -m "$commit_message"
    git push origin main
)
