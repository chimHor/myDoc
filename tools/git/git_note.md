##### checkout branch
git checkout [branchName]  切换分支
git checkout -b [branchName] 创建并切换分支

##### push
git remote add 11 ssh://hejiaquan@172.16.1.11/git_repo/device/widevine.git
repo remote add [repo name] ssh://hejiaquan@172.16.1.11/git_repo

git push [repo name] [local branch name]:[remote repo branch name]


##### merge conflict, checkout
repo forall -c git merge remotes/exdroid/jb42-exdroid

git checkout --theirs .

##### example of compress commit
```
laura@rune:~/example (master)$ git branch tmpsquash ba3c498878054e25afc5e22e207d62eb40ff1f38
laura@rune:~/example (master)$ git checkout tmpsquash
Switched to branch 'tmpsquash'
laura@rune:~/example (tmpsquash)$ git merge --squash master
Updating ba3c498..40386b8
Fast-forward
Squash commit -- not updating HEAD

[snip, changed files]

11 files changed, 212 insertions(+), 59 deletions(-)
laura@rune:~/example  (tmpsquash)$ git commit -a -m "My squashed commits"
[test2 6127e5c] My squashed commits
11 files changed, 212 insertions(+), 59 deletions(-)
laura@rune:~/example  (tmpsquash)$ git format-patch master
0001-My-squashed-commits.patch
laura@rune:~/example  (tmpsquash)$ git checkout master
Switched to branch 'master'
laura@rune:~/example  (master)$
```
##### branch
删除分支，若未被合并无法删除
git branch -d branchName 
强制删除分支
git branch -D branchName 


##### conflict deal way
记录冲突解决方法
git config --global rerere.enabled true   
不记录冲突解决方法
git config --global rerere.enabled false


##### tag
删除本地tag
git tag -d [tag_name]
删除服务器tag
git push xxx :refs/tags/[tag_name]
推送tag
git push xxx [tag_name]


##### else
repo forall -c "commit=$(git log --before=2014-06-10-1 | grep commit | sed 's/commit//g');git checkout $commit"
