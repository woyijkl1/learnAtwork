```
git 的 branch 、commit 、 HEAD 的含义：

commit 是代码提交保存的checkpoint，可以理解是在某一时刻的快照，就像图里面的节点一样

branch 代表分支，可以支持从某个commit开始并行或者多任务编程，一般由一连串的commit组成，本质上branch是指示了一个commit的地址

HEAD 是当前我们屏幕（或者ide）看到的某个commit的内容的指针，指示我们现在看到的代码是哪个commit的快照

可以把所有的commit（所有人 所有branch）想象成一个有向无环图，branch和HEAD都是一个指针，指向某个节点，只不过branch指针是指向某个端节点（可以继续提交新的commit来扩展整个图），而HEAD是指向我们当前IDE显示的commit的指针。
```



```
git branch branch_name startpoint
新建分支，如果不指定starpoint则默认从HEAD处开始
```



```
git checkout [-b] branch/commit 
b代表新建一个
最后一个参数是commit的时候，HEAD指向这个commit，我们的ide就看到的是这个commit时候的代码，但是这个时候的分支是不变的，我们可以用git checkout branch 来使得HEAD回到branch指向的commit
```





```
git 分成工作区（当前的修改）  暂存区（add 之后文件进入暂存区）

如果一个文件已经add 但是后面又不想提交它，那么用
git restore --staged filename 将这个文件撤离暂存区

在工作区，如果一个文件被无意中修改（比如不小心按了空格），想恢复到没有修改之前的状态，则用
git restore filename (. for all file)
```



```
get branch branch name
```





### 切换版本

git check <version>

放弃本地修改 换成线上的版本：
git reset --hard
git pull

创建新分支  git checkout -b branchname



```
当用了新的gitignore但是远端没有生效的时候
忽略某些文件
# 注意有个点“.”
git rm -r --cached .
git add -A
git commit -m "update .gitignore"
```

```
暴力切换到某一次的提交（reset 分支）
git log 查看commit的 id
git reflog 查看所有分支的所有记录，包括分支转换、提交等
git reset --hard <commit id>
对于<commit id> 可以用HEAD表示当前版本，用HEAD^表示上一个版本，HEAD^^ 表示上两个版本，HEAD~10 表示上10个版本
--hard 直接放弃commit id后面所有的提交记录
--soft 将commit id后面的提交放到暂存区

如果想暂时看某个checkpoint的结果，然后再回到最新的代码：
git checkout commit_id
看完了
git checkout branch_name



```



### 暂时存储现场

```
当一个工作干了一般的时候，需要切到另一个分支处理一点事情，这个时候并不需要commit，应该用的是git stash
整体流程：

1.在某个dev上开发了一半，这个时候git status 提示
$ git status
On branch dev
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

	new file:   hello.py

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

	modified:   readme.txt

2.使用命令 git stash
$ git stash
Saved working directory and index state WIP on dev: f52c633 add merge
之后就可以任意切换分支 例如 切换到master 干了一点活，然后再切回到dev上准备继续开发

3.使用git stash pop / git stash apply ( apply 不会删除存的东西，需要手动删除，pop自动删除)
```



### 选择合并分支的一些内容

```
在master上修改一个bug后，分支也要同样修复这个bug 这个时候并不需要重复劳动，直接选择把改bug的commit合并到分支即可

假如需要选择合并 4c805e2 commit
运行：
git cherry-pick 4c805e2
```





### 打印

```
git log --graph --pretty=oneline --abbrev-commit
```



### rebase  用法

```
作用 把多个commit 合并
命令  git rebase -i HEAD~3 （start hash:end hash）

命令回车后，进入vim页面 挑选commit以及定义操作：界面如下：

vim：
pick 6afc00a second commit   -> p 6afc00a second commit
pick 11df037 fourth commit   -> s 11df037 fourth commit
pick 9ab897d five commit     -> p 9ab897d five commit

# Rebase b79010a..9ab897d onto b79010a (3 commands)
#
# Commands:
# p, pick <commit> = use commit
# r, reword <commit> = use commit, but edit the commit message
# e, edit <commit> = use commit, but stop for amending
# s, squash <commit>

注意 这个时候的log顺序和git log命令中的顺序是不一样的 所以在这里最后一个commit 不能用s，因为s会往下继续找commit，而它是最新的commit下面没有了，就会报错


接下来会进入第二个vim页面
# this is the merge commit...
input here your commit message (这里是新加的信息)

# this is the first commit message(这里可以修改以前的commit信息)
first commit message
...

保存完了第二个页面之后即rebase完成


```



### 删除远程分支

```
git remote add origin git@github.com:michaelliao/learngit.git
```



