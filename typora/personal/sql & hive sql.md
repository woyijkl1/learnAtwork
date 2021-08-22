```
cross join   两个表做笛卡尔集

select * from table1 cross join table2

if table2 is one row table, then table1 will add a column with table2
```



```
两行合并用
select * from xxx
union
select * from XXX

union all 会将两个表中的重复行去掉
```



```
to bucket a feature or do some statistics, can use case when 

select
  case
    when xxx<2 then 0
    when xxx<3 then 1
    ...
    else 4
  end as bucket_feature



```



````
hive sql 需要在每个子查询后面加上别名
selct * 
from(
	select xxx
) 这里必须有别名


其他的时候，一般在有多个重复的字段的时候也需要加别名
在from后有两个表的时候一般都会加别名
一个表的时候一般不用别名，但表的名字长的时候也可以加别名简化一下

````





```
order by
所有的数据都会经过一个reducer排序

sort by
保证每个reducer里面的数据有序

distribute by
将指定字段作为分配reducer的依据，保证同样的数据去往同样的reducer

cluster by
等于distributed by 和 sort by的结合

select mid, money, name from store distribute by mid sort by mid
等价于
select mid, money, name from store cluster by mid sort by money


```





```
with talbe_a as (
	select * ...
),  //要有逗号
table_b as(
	select * ...
),
....
table_x as(
	select * ...
) //最后一个不要逗号
select * ...
```



```
聚合函数
return_type.    	name
bool 							array_contains(list,item)
array<V>        	map_values(map<K,V>)
array<K> 					map_keys(map<K,V>)
array<T>					sort_array(Array<T>)
string						concat(string A, string B...)
string 						concat_ws(separator, string A, string B)   A,B,C = concat_wa(",","A","B","C")

```



```
group by 之后，判断某个字段是否含有特定的值
  思路：用一个sum（是否含有特定值）as column 
  如果大于0则表示含有特定值

例子：判断value里面有没有 “出行”
select type,sum(value = '出行') from config 
group by type
```



```
各种join：

INNER JOIN：
仅仅返回两个表中，匹配列相同的列值，所在行的数据。

LEFT OUTER JOIN：
左外连接：返回左表的所有数据，并且在右表中不能匹配的列值，其坐在行则使用空值。

FULL OUTER JOIN：
完全连接可看作是左外连接和右外连接结果之和，返回两个表的所有数据，如果匹配列的值在两个表中匹配，那么返回数据行，否则返回空值。

外连接： left和right指示要保留那个表，然后用保留的表的行去另一个表里面找能够连接上的行，如果能连接上，那么把连接上的字段加到指定的表上，！！指定保留的表的一行在另一张表有多条匹配时，则在最后的结果中保留多条匹配的结果


例子：
table A   |   table B
a 1						b x
b 2						c y
c 3						c z

select * from A left join B on A.colunm1 = B.column1

result:
b 2 x
c 3 y
c 3 z



left join = left outer join
right join = right outer join
full join = full outer join

 内连接：
 join = inner join
 
 完全连接：
 cross join
```





```
explode 和 lateral view

explode 把表里面某个字段的list等结构变成行

表 mytable 
 mycol列
 [1,2,3]
 [1,2]
 
 select explode(mycol) as newcol from mytable
 
 结果：
 newcol
	1
	2
	3
	1
	2
	
lateral view 用来将 类似explode这种可以产生多个行的函数与当前行进行结合，生成多行（原来的属性+explode产生的新属性
	
	表 pageads
	id   			ads
	front			[1,2,3]
	contact 	[2,3,4]
	
	select id, adsid
	from pageads lateral view explode(ads) adstable as adsid
	
	结果：
	id   			adsid
	front			1
	front			2
	front			3
	contact		2
	contact		3
	contact		4
	
explode(ads) adstable 形成叫 adstable的表， lateral view会把这个表对应到每一行，产生多个对应的行，可理解对每一行用explor生成多个行

后续可以结合group by 统计adsid出现的次数

select id, count(*)
from pageads lateral view explode(ads) adstable as adsid group by adsid
	

```

```
同一份数据的多种处理
from history
insert overwrite sales select * where action='purchased'
insert overwrite credits select *  where action='returned';
```



```
分位数
percentile_approx(uv, array(0.2,0.4,0.6,0.8), 9999) as uv

```



```
数据类型转换
cast(number as string),
```





```
系统配置：
hive.limit.optimize.enable 
hive.exec.mode.local.auto

```





### udf

如果输入是空 则在udf中相应的位置 系统会给‘\N’  判断也就用  value=='\N' 就行
