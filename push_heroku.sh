#!/bin/sh


# This script pushes a git subtree (The "./"Software" directory) to the 
# Heroku cloud computing platform (heroku.com)
# 
# This is because we do not want our entire git repo to be pushed to Heroku,
# only the "Software" folder should go onto the cloud.

# As heroku expects you to push a git repo to its servers, we will use git subtree
# to accomplish this.

git_url='https://git.heroku.com/ee209t02.git'

# Print the command we are running 
set -x 

git subtree push --prefix Software $git_url master 


