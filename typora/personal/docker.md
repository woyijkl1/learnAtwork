docker cp ./part-00000 b9c3fcb50baf:/root. # cp

### build

 ```
 docker build -t  name:vertion -f fileName .
 ```



### 启动和关闭

```
start:
open /Applications/Docker.app

close
launchctl list | grep docker
找到docker的名字
然后 
launchctl stop  docker_grep_name
```





### push

```
docker push harbor.shopeemobile.com/rongdi.yin/samewithzw:v1.0
            名字：版本
            
```



### 删除镜像

```
docker rmi 序列号
```



### docker 工作路径

```
docker 的工作路径是分层进行的 不能像写shell那样 直接用cd
docker的每一个命令（貌似）都会启动一个新的进程，如果用cd的话只会影响到当前进程
所以需要使用 WORKDIR "file path"
这个命令会将以后所有的进程的路径都放到这个路径下，如果docker里面没有这个文件夹，则自动创建这个文件夹

```





