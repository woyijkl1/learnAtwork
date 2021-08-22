



show databases;
show tables;

desc XXXtable;

show partitions XXXtable;

explain select * from XXX table limit 1;   //查看行数

用ld-rongdi_yin 作为用户 否则会报权限错误



### hive debug 方法

当在hive上跑udf的时候，输出的日志并不能满足debug的需求，这个时候需要先用本地模式先在本地debug，不然招不到bug信息只能一行一行试哪里有问题 十分麻烦

例如在一个sql里面写：

select 
pdpitemid,pdpshopid,pdpSubcat,pdpThirdcat,ubSubcat,ubThirdcat,ubid
from temp_rongdi_relevant
limit 10000;

然后 执行

hive -f this.sql | python udf.py

先跑1w条数据看看有没有问题，没有问题再大规模跑

如果python 程序出错，在python里面用try except 把输入打印出来再分析

#### 常见 udf 错误记录

- json 解析出错

- 数组下标超过范围（因为之前生成数据中有null导致数组的长度不可控，所以要处理好异常/缺失情况

- python 直接语法错误（在本地debug一遍可以解决这个问题

  







# create (from other table) and load data

```
create table test5(
	shopid	bigint,
	itemid	bigint,
	list                	array<struct<itemid:bigint,shopid:int,score:int,data_type:string>>,
	dt	string
)

Create table like XX_table
```



```
insert overwrite table table_name partition(  XX ) select * from XX_table limit 100  // 从大的表里面拿数据需要用map reduce 过程，很慢，不能用limit 语句，这里会只分配1个reducer，如果表很大，这个reducer就会成为瓶颈，会很慢
```



```
create table rongdi_temp2 as select * from rcmd_temp_rongdi_statistics_sg;         
新的表是没有分区的,用as的都没有分区
```



```
create talbe rongdi_temp3 like rcmd_temp_rongdi_statistics_sg;
insert overwrite table rongdi_temp3 partition(dt,country)  select * from rcmd_temp_rongdi_statistics_sg;
新的表有分区
```



```
create table like rcmd_temp_rongdi_statistics_sg;
insert overwrite table rongdi_temp5 partition(dt,country)  select * from rcmd_temp_rongdi_statistics_sg tablesample(1 rows) ; 
有分区
```



### 修改表名

```
alter table table_name rename to new_table_name;
```





### 采样

Table sample 语句后面不能带有where语句

```
create table rongdi_temp4 as select * from rcmd_temp_rongdi_statistics_sg tablesample (1 rows);  没有分区
```



```
表有多个分区

create table Rongdi_temp6 like rcmd_temp_rongdi_statistics;
insert overwrite table rongdi_temp6 partition(dt,country)  select * from rcmd_temp_rongdi_statistics tablesample(100 rows) ;  
结果中有多个分区 
```



```
create table Rongdi_temp7 like rcmd_temp_rongdi_statistics;
with temp as (
        select * from rcmd_temp_rongdi_statistics where country='SG'
)
insert overwrite table rongdi_temp7 partition(dt,country)  select * from temp tablesample(100 rows) ;
结果只有一个分区 且数量固定
```





```
实际操作，从rcmd_item(有80亿的条数) 里面的指定分区采样1w条
with temp as (
        select * from rcmd_item where dt='2021-05-25'
)
insert overwrite table rongdi_temp8 partition(dt)  select * from temp tablesample(10000 rows) ;
```



```
select * from tabel_name tablesample (bucket 1 out of 5 on colunm_name)
```



```
对小数据采样也可以用rand函数
select * from table_name
distribute by rand()
sort by rand()
limit 10000;
```
















drop table test5



insert into test6 (a , b) values (1, 2)



insert into table test8 partition(dt = '2')
  select 1,2,3,array(named_struct('itemid',bigint(1),'shopid',1,'score',2,'data_type','item'));

insert into table tmp_rd_rcmd_item partition(dt) select * from rcmd_item limit 10000;



alter table test8 drop partition(dt='2')



select itemid, collect_list(concat_ws('*',string(simi.shopid),string(simi.itemid))) from test8 lateral view explode(list) at as simi group by itemid;





```
set hive.cli.print.header=true;
```



```
hive -e 'set hive.cli.print.header=true; select * from rcmd_item limit 1' | sed 's/[\t]/,/g'  > ./rcmd_item.csv  
// 把\t 换成逗号，这么做不妥，因为字符串里面有逗号
```



```
use python to transform data in map reduce

SELECT
    transform(itemid, list) 
    using 'python3 convert_similaritemlist.py'
    as (itemid bigint, similaritemslist array<string>)
from (
    select distinct itemid, list
    from vav5list
) limit 1;
```



```
把dict的结构变成字符串
select itemid,
collect_list( concat('{' ,
concat_ws(':','"itemid"',string(simi.itemid)) ,
',',
concat_ws(':','"shopid"',string(simi.shopid)) ,
',',
concat_ws(':','"score"',string(simi.score))   ,
',',
concat_ws(':','"data_type"',simi.data_type) , '}' ))  

from (
    select *
    from vav5list_v2
    where dt = '2021-03-11' and list is not null 
    limit 1000
) t2 lateral view outer explode(list) at as simi 
where dt = '2021-03-11'
group by itemid
limit 1000;
```





保存hive之前zhaoqi给的设置：

use recommend;
set hive.support.quoted.identifiers=none;
set hive.exec.parallel=true;
set hive.exec.parallel.thread.number=16;
set hive.exec.dynamic.partition=true;
set hive.exec.dynamic.partition.mode=nonstrict;
set hive.map.aggr=true;
set hive.groupby.skewindata=true;
set hive.optimize.skewjoin=true;
set hive.skewjoin.key=100000;

set hive.execution.engine=spark;
set spark.executor.memory=8g;
set spark.yarn.executor.memoryOverhead=6g;



```
查看表的详细信息：
describe  extended table;
在表的最后结尾，会有这个表有多大，有多少行
```



### hive的存储格式

```
每个表的表述文件中有：
ROW FORMAT SERDE
  'org.apache.hadoop.hive.serde2.JsonSerDe'
STORED AS INPUTFORMAT
  'org.apache.hadoop.mapred.TextInputFormat'
OUTPUTFORMAT
  'org.apache.hadoop.hive.ql.io.HiveIgnoreKeyTextOutputFormat'
  
ROW FORMAT SERDE 表示 hive序列化的过程
hive序列化的过程是：
HDFS files --> InputFileFormat --> <key, value> --> Deserializer --> Row object
Row object --> Serializer --> <key, value> --> OutputFileFormat --> HDFS files
ROW FORMAT SERDE 定义的是 HDFS files --> InputFileFormat（OutputFileFormat --> HDFS） 的过程，
其实也就定义了hive表的存储格式

用ROW FORMAT SERDE
  'org.apache.hadoop.hive.serde2.JsonSerDe';
  则是定义底层用json的格式存储
  
STORED AS INPUTFORMAT 和 OUTPUTFORMAT共同指定了 底层的存储格式（textfile 二进制等等）
像spark的默认存储就是parquet
用textfile 可以配合cat 等工具直接处理 用parquet等就要转换
```







