tail file -f 循环读取最新的



```
du -h 查看文件占用大小
du -h -d 1 ./ 查看当前文件下各个文件夹的大小

```



```
set 用法
-e 若指令传回值不等于0，则立即退出shell。
-u 　当执行时使用到未定义过的变量，则显示错误信息。
-x 　执行指令后，会先显示该指令及所下的参数。
```



chmod -R



head -100  filename >a.txt  提取前多少行



```
# run backend
nohup ./start.sh >output 2>&1 & 
```







alias la='ls -al'  //定义新的命令，写到.zshrc 里面直接调用



ssh 10.65.228.200 "sudo -u ld-rongdi_yin hadoop fs -rm -r /user/ld-rongdi_yin/hcode".  //指定用户运行



alias tohip="ssh -t 10.65.228.200 'sudo su ld-rongdi_yin;bash'" //指定目录或者其他命令



Homedoc 命令：(用来在ssh中运行交互命令行)

expect <<EOF
spawn sftp 10.65.228.200
expect ">"
send "cd /home/ld-sgdev/ld-rongdi_yin/fileUp\n"
expect ">"
send "put ${file}\n"
expect ">"
send "exit\n"
expect eof
EOF



history  输入命令进行模糊搜索 之后可以多次按 control + r继续向前模糊搜索



rsync --av  --delete --exclude  source_file_dir  target _dir
//-a 表示归档模式，递归传输文件  -v verbose 详细模式输出



### 查看cuda版本

```
cd /usr/local/cuda
cat vertion.txt
```







## bash 命令

```
尖括号（<>）用法：  <，可以实现“欺骗”的效果，让其它命令认为某个命令的输出是一个文件。
diff <(ls /original/dir/) <(ls /backup/dir/)  #比较两个文件夹包含文件的差异
```



```
yarn kill 程序
yarn application -kill appName
```





# shell 编程

```
比较运算
[[ ]] 默认用双括号  
内部操作符与操作变量之间要有空格：如 [[ “a’ = “b” ]] 

-eq 等于,如:if [ "$a" -eq "$b" ]   
-ne 不等于,如:if [ "$a" -ne "$b" ]   
-gt 大于,如:if [ "$a" -gt "$b" ]   
-ge 大于等于,如:if [ "$a" -ge "$b" ]   
-lt 小于,如:if [ "$a" -lt "$b" ]   
-le 小于等于,如:if [ "$a" -le "$b" ]  
```

 

```
反引号 ` `
反引号的功能是命令替换，在反引号 ` ` 中的内容通常是命令行，程序会优先执行反引号中的内容，并使用运行结果替换掉反引号处的内容
$ echo `date`
```



```
$(( ))

$(( )) 的功能是进行算术运算，括号中的内容为数学表达式 里面可以用运算符


```



```
中括号 [ ]
双中括号 [[ ]] 双中括号提供了针对字符串比较的高级特性，

```



```
字符串分割
string="hello,shell,split,test" -> list(hello shell split test)

array=(`echo $string | tr ',' ' '` )

```



```
对于一个list 循环


for var in ${array[@]}
do
   echo $var
done 


for(( i=0;i<${#array[@]};i++)) 
do
  #${#array[@]}获取数组长度用于循环
  echo ${array[i]};
done;
```



```
数组元素的增加： arr+=( "new_element" )
减少： arr=( "${arr[@]:0:2}" "${arr[@]:3}" )

```



### 条件判断

```
if condition
then
  command
else
	command
fi

当把then放在if那一行里面的时候 需要加分号（ ; ）来提示shell代码块的分割

if condition; then command; else command; fi
```

```
break 跳出 和python一样的用法
```



```
让一个管道的输出成为某个命令的输入 用 xargs
例如： kubectl get pods | grep ${job_name} | tail -n 1 | awk '{print $1}' | xargs kubectl logs
```



```
mkdir -p 递归创建  如果目录事先存也不会报错
```



### 命令行

```
shell 获取命令行的形式：

PSET=0
while getopts y:t:p opt; do            # 加冒号就是要有参数 如果需要类似 -p 这种不用参数的 用yt:
    case "$opt" in
    y) yesterday="$OPTARG";;
    t) today="$OPTARG";;
    p) PSET=1;; 
    ?) exit 1;;
    esac
done
shift $((OPTIND-1))
```



### 变量类型

```
布尔类型：
a=true
if [ a == true ]; then
```



### 判断文件夹是否存在

```
if [ ! -d "$folder"]; then
  mkdir "$folder"
fi
```



### 运算符

```
`expr 2+2`
```



### sed 修改文件

```
知乎的讲解 非常好 https://zhuanlan.zhihu.com/p/66651350
sed 是一行一行进行操作的

基本格式： sed -参数 "范围(1,4) 操作(p)" 文件名

sed -n "2,5 p" file //打印文件2到5行

替换文件内容：
sed -i "备份名(linux only)" "/范围/  s/被替换字符串/替换字符串/ g"
例子：
sed -i "" "/image:/ s/samewithzw:.*/samewithzw:${DOCKERNAME}/g" docker/${YAML}
加-i则直接修改文件  
用双引号是弱转义，不会去掉$符号的变量功能，而用单引号则为强转义，会把$当做一般的符号
```



### 判断文件是否存在

```
if [ -d "file name" ]; then
  XXX
fi
```



### 以空格分割字符串

```
使用awk的功能
m=`echo $a | awk '{print $1}'`
```



### 日期

```
date 命令 -d<字符串> 　显示字符串所指的日期与时间。字符串前后必须加上双引号。 
     指定输入的格式     
date '+%Y-%m-%d' -d "$DATE -$i days"

获得当前时间
time=$(date "+%Y%m%d-%H%M%S")
```





