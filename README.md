easy-git
======================
This project is imitation of git.  
I'm trying to make it easy to use version control.  
This works on macOS.


Usage
------
Download zip or evaluate next...  
After that, build project and put product in where the path is through.  
Then, move to your project directory.

### Initialize ###
    eat init


### Add ###
    eat add file1 dir1 file2 ...    // means "git add file1 fir1 ..."
    eat add ./    // means "git add ."


### Commit ###
    eat commit    // means "git commit"
    // After you evaluate this, you could type commit message.


### Log ###
    eat log   // means "git log"
    eat log 1 // shows latest commit log only
    eat log n // shows latest n commits log

### Branch ###
    eat branch     // shows branch list
    eat branch b1  // create the branch named b1

### Checkout ###
    eat checkout branch_name  // means "git checkout branch_name"

### Reset ###
    eat reset   // reset project to latest commited version
    eat reset n // reset project to n commited ago

### Merge ###
    eat merge branch_name  // means "git merge branch_name"

### Issue ###
Now, add functon dows not work collectly.
commit_tree generated 2 times, so please use reflect function only.

License
----------
Copyright &copy; 2017 arabian9ts
Distributed under the [MIT License][mit].

[MIT]: http://www.opensource.org/licenses/mit-license.php
