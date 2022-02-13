git
* version control 
* % git init will initialize a repo
* % git status tells you about the status of the repo 
* committing files 
    * add into staging area: % git add file1.js file2.js 
        * % git add . —> will add all files in directory to repo
    * commit: % git commit -m “add message here” 
    * % git log gives you a history of commit changes 
        * a log has a hash, which is a long string of letters and numbers 
        * can use % git checkout hash —> insert the hash value into the hash spot, this will allow you to revert code back to previous commit states 
            * will take you off the master branch and onto a temp one 
            * use % git checkout master to take you back to latest commit 
* branches 
    * list branches % git branch 
    * create a new branch % git branch name 
    * merge a branch to master using % git merge branch-name 
* .gitignore
    * cheat sheet: https://github.com/kenmueller/gitignore