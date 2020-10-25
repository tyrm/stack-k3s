#/bin/bash



ansible-vault encrypt_string --vault-id stack@~/.ansible/password_file "$2" --name "$1"
