# for go

### module import

```
go 早期的import方式是将代码都放到  $GOPATH/src 然后import语句的查找方式也是从$GOPATH/src目录下查找
后期社区开发了一些如vendor 之类的包管理工具，官方在1.11后推出go mod，成为主流

go mod用法：
  基本用法：
  	建立好一个module后，运行  go mod init module_name (可以是一个路径)
  	       								 go mod tidy （添加所需依赖）
  go mod的查找过程：
  	编译时编译器会从工作目录（当前所在目录）开始并逐级向上查找是否具有 go.mod 文件。
  	  如果有，go.mod 文件中声明的 module 名称就视作 go.mod 所在的路径，然后以指定的 main 包为依赖入口，所有以 go.mod 中声明的 module 名称开头的导入路径都以 go.mod 所在的路径为相对路径进行包的查找导入。所有需要导入的路径中如果在 go.mod 中指定了版本，则从 $GOPATH/pkg/mod/ 下取得相应版本进行导入，如果没有被指定则从 $GOPATH/src/ 或 $GOROOT/src/ 中进行查找导入。
  	  如果没有，所有依赖均从 $GOPATH/src/ 或 $GOROOT/src/ 中进行查找导入。
  	  如果是以./ 或者 ../ 开头的import 直接去对应的相对路径寻找。
  
  引入不在 gopath/src下的包p2：
    在程序中，import "p2_module_name"
    在mod文件中  replace "p2_module_name" => "../p2_path"（p2需要有mod文件）
    参考： https://zhuanlan.zhihu.com/p/109828249

  	  
```









## basic

```
rune  在go中，就是int32

needl:="hello"
rune_type = []rune(needle)
```



```
# make
make(map[type]type)
make([]type,len,cap)
make(x chan<-)
```





### string

```
string类型底层是一个[]byte 
byte类型是uint8类型，

单引号'h'是rune类型，"h"是string类型

循环string的时候，临时变量是rune类型

func main() {
	s := "hello word"
	for _,c := range s{
		fmt.Println(c)
		if c == 'h'{
			fmt.Println("yes")
		}
	}
}

output：
104
yes
101
108
108
111
32
119
111
114
100


格式化：
s := fmt.Sprintf("%s is %d years old.\n", name, age)
```



### json

```
导入： encoding/json
if err := json.Unmarshal([]byte(line), &jsnItem); err != nil {
			log.Fatalf("json load runs: %s", err)
		}
注意，是把struct的地址传入函数，不是对象传进去
```







## array

```
# declear  x := []type{}
a := []int{1,2,3}

#delete
a = append(a[:loc],a[loc:])
```







