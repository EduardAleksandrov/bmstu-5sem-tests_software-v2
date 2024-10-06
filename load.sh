#!/bin/bash

# $chmod u+x load
# ls -l load

function build_folder() {
    cd ./build/
    echo "to build folder"
}

function cmakes() {
    cd build
    cmake ..
    echo "to cmake"
}

function build() {
    cd ./build/
    cmake --build .
    echo "to build"
}

function install() {
    cd ./python
    python3.8 -m venv venv/
    source venv/bin/activate
    pip install matplotlib pandas
    deactivate
}

function all() {
    cd ./python
    source  venv/bin/activate
    python3.8 graph_one.py
    python3.8 graph_two.py
    deactivate
}

case "$1" in
    folder)
        build_folder
        ;;
    cmake)
        cmakes
        ;;
    build)
        build
        ;;
    install)
        install
        ;;
    all)
        all
        ;;
esac