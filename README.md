easy-git
======================
This project is imitation of git.  
I'm trying to make it easy to use version control.  
This works on macOS and needs C++ boost lib.


Usage
------
Download zip or evaluate next...  
After that, build project and put product in where the path is through.  
Then, move to your project directory.

### Initialize ###
you can places your project under the management of eat system.<br>
formula is as following...

    eat init


### Add ###
you can add files to eat repos.<br>
formula is as following...

    eat add <file1> <dir1> <file2> ...    // means "git add file1 fir1 ..."
    eat add ./    // means "git add ."


### Commit ###
after adding files, you should exec commit cmd.<br>
formula is as following...

    eat commit    // means "git commit"
    // After you evaluate this, you could type commit message.


### Log ###
you can check repos's logs.
after some commits, then eval log cmd.<br>
formula is as following...

    eat log   // means "git log"
    eat log 1 // shows latest commit log only
    eat log <Integer n> // shows latest n commits log

### Branch ###
if you work not only master(default) branch, you can make new repos or check existing branches.<br>
formula is as following...

    eat branch     // shows branch list
    eat branch <new_branch_name>  // create the branch has specific name

### Checkout ###
if want to switch working branch, eval this cmd.<br>
formula is as following...

    eat checkout <branch_name>  // means "git checkout <branch_name>"

### Reset ###
if want to go back to past, eval this cmd.
first, check the log you want to go, then eval reset cmd.<br>
formula is as following...

    eat reset   // reset project to latest commited version
    eat reset <Integer n> // reset project to n commited ago

### Merge ###
when want to merge one branch to another, you can merge working status by this.<br>
formula is as following...

    eat merge <branch_name>  // means "git merge branch_name"

### Help ###
if you don't know which cmd you should eval, check help.<br>
formula is as following...

    eat help <subcommand>

License
----------
Copyright &copy; 2017 arabian9ts
Distributed under the [MIT License][mit].

[MIT]: http://www.opensource.org/licenses/mit-license.php
