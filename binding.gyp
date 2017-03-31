{
  "targets": [
    {
      "target_name": "termios",
      "sources": [ "src/termios.cc" ],
      "include_dirs" : ['<!(node -e "require(\'nan\')")']
    }
  ]
}

