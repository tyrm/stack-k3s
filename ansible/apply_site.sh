#!/usr/bin/env bash

# Create venv if it doesn't exist
if [ -d "venv" ]
then
  # Source It
  . venv/bin/activate
else
  echo "creating venv"
  PYTHON_3_PATH=$(which python3)
  virtualenv -p $PYTHON_3_PATH venv
  . venv/bin/activate
  pip install ansible
fi

ansible-playbook -i hosts --ask-become-pass --vault-id stack@~/.ansible/password_file site.yml
