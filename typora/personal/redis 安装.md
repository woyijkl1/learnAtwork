## 使用Homebrew安装Redis

##### (1) 安装命令

```
brew install redis
```

##### (2) 查看软件安装及配置文件位置

Homebrew安装的软件会默认在`/usr/local/Cellar/`路径下；

redis的配置文件`redis.conf`存放在`/usr/local/etc`路径下。

##### (3) 启动redis服务

###### 方法一：

brew除了可以帮助我们安装软件以外，还可以帮助我们启动软件

```
brew services start redis
```

###### 方法二：

```
redis-server /usr/local/etc/redis.conf
```

##### (4) 查看redis服务进程

我们可以通过下面命令查看redis是否正在运行

```
ps axu | grep redis
```

##### (5) redis-cli连接redis服务

redis默认端口号**6379**，默认**auth**为空，输入以下命令即可连接

```
redis-cli -h 127.0.0.1 -p 6379
```

##### (6) 关闭redis服务

优雅的关闭`redis-cli shutdown`或者杀死`sudo pkill redis-server`

##### (7) redis.conf配置文件说明

redis默认是前台启动，如果我们想以守护进程的方式运行（后台运行），可以在**redis.conf**中将`daemonize no`,修改成`yes`即可。





常用命令

select 0