## spark

spark 是一个计算框架，可以读入hdfs文件  json文件  数据库文件 等等不同类型的存储文件，然后提供例如机器学习库的计算api框架
spark sql和hive sql不同之处在于 spark以前直接用hive sql的解释器，后面spark自动重构了解释器

spark API文档：

https://spark.apache.org/docs/2.4.0/api/python/pyspark.sql.html?highlight=format#pyspark.sql.DataFrameWriter.format

顺带说一下： hbase是和redis对标的存储方案 不过hbase读取慢 容量大  而  redis 读取快但容量小。 codis是redis的分布式版本

spark 默认不区分大小写



```
hi everyone, I write a simple example to check the difference between spark and hive sql and if you are interested, here is the code https://git.garena.com/rongdi.yin/spark_hive_diff
```



使用spark-shell/ spark-submiit 输出pretty log的方式：

https://confluence.shopee.io/display/SDE/Spark+logging+configuration

```
Change Logging Level from "INFO" to "WARN" for easier debugging
The default logging level set is at the "INFO" level. This can be display too much log information, making it hard to identify an error if it does appear.

Create custom log4j.properties
To change the default logging-level to "WARN":

cd into your working directory
Use touch log4j.properties to create an empty file
Paste the following code block into your newly created log4j.properties file:
# Set everything to be logged to the console
log4j.rootCategory=WARN, console
log4j.appender.console=org.apache.log4j.ConsoleAppender
log4j.appender.console.target=System.err
log4j.appender.console.layout=org.apache.log4j.PatternLayout
log4j.appender.console.layout.ConversionPattern=%d{yy/MM/dd HH:mm:ss} %p %c{1}: %m%n
  
# Set the default spark-shell log level to WARN. When running the spark-shell, the
# log level for this class is used to overwrite the root logger's log level, so that
# the user can have different defaults for the shell and regular Spark apps.
log4j.logger.org.apache.spark.repl.Main=WARN
 
# Settings to quiet third party logs that are too verbose
# log4j.logger.org.spark_project.jetty=INFO
# log4j.logger.org.spark_project.jetty.util.component.AbstractLifeCycle=INFO
# log4j.logger.org.apache.spark.repl.SparkIMain$exprTyper=INFO
# log4j.logger.org.apache.spark.repl.SparkILoop$SparkILoopInterpreter=INFO
# log4j.logger.org.apache.parquet=INFO
# log4j.logger.org.apache=INFO
# log4j.logger.parquet=INFO
  
# SPARK-9183: Settings to avoid annoying messages when looking up nonexistent UDFs in SparkSQL with Hive support
log4j.logger.org.apache.hadoop.hive.metastore.RetryingHMSHandler=INFO
log4j.logger.org.apache.hadoop.hive.ql.exec.FunctionRegistry=INFO
Note:

If you want to set your logs from your application at different level, you can add the following line to log4j.properties file.
Assume that all your code is in package com.shopee and you want to set log level to INFO
# Set log from com.shopee to INFO 
log4j.logger.com.shopee=INFO


Start Spark with new log4j.properties file
Run following command to start spark-shell which the new log4j.properties. This option also works for other console such as pyspark or spark-sql.

spark-shell --queue de-regular --driver-java-options"-Dlog4j.configuration=file:[/path/to/]log4j.properties"
For spark-submit, you will need to tweak the option based on the mode the application is run.

# Client mode:
spark-submit --deploy-mode client --files [/path/to/]log4j.properties \
--conf "spark.driver.extraJavaOptions=-Dlog4j.configuration=file:[/path/to/]log4j.properties" \
--conf "spark.executor.extraJavaOptions=-Dlog4j.configuration=file:log4j.properties"
 
# Cluster mode:
spark-submit --deploy-mode cluster --files [/path/to/]log4j.properties \
--conf "spark.driver.extraJavaOptions=-Dlog4j.configuration=file:log4j.properties" \
--conf "spark.executor.extraJavaOptions=-Dlog4j.configuration=file:log4j.properties"
Note for the conf on remote nodes, such as executor or driver in cluster mode in the above command, log4j.properties will be copied to distributed cache, then copied again from distributed cache to remote nodes, and the log4j.properties path is just local.

You could find the copying log from client machine to distributed cache in the log file, for example
21/06/16 03:12:05 INFO Client: Uploading resource file:/home/jenkins/data_daasprofile/om-user-behavior/master/resources/log4j.properties -> hdfs://R2/user/data_daasprofile/.sparkStaging/application_1623767049889_42896/log4j.properties

```



### shell输出级别

```
spark.SparkContext.setLogLevel("ERROR")
```



### 启动命令

```
注意 有些queue不行  换着用 


pyspark --num-executors 100 --executor-memory 4G --executor-cores 4 --driver-memory 1G --conf spark.default.parallelism=1000 --conf spark.storage.memoryFraction=0.5 --conf spark.shuffle.memoryFraction=0.3 --queue root.rcmd-dev



pyspark --num-executors 100 --executor-memory 10G --executor-cores 4 --driver-memory 6G --conf spark.default.parallelism=1000 --conf spark.storage.memoryFraction=0.5 --conf spark.shuffle.memoryFraction=0.3 --conf spark.driver.memoryOverhead=4G --conf spark.yarn.driver.memoryOverhead=4G --queue root.search-prod

spark-submit \
  --master yarn \
  --num-executors 150 \
  --executor-memory 3G \
  --executor-cores 4 \
  --driver-memory 1G \
  --conf spark.default.parallelism=1000 \
  --conf spark.storage.memoryFraction=0.5 \
  --conf spark.shuffle.memoryFraction=0.3 \
  --queue root.rcmd-prod \
  spark_process.py \
  --dt 2021-06-27
```

### 参数配置

```
1. 从启动命令直接指定

2. 在 sparksession创建的时候直接指定
spark = SparkSession.builder \
...     .master("local") \
...     .appName("Word Count") \
...     .config("spark.some.config.option", "some-value") \
...     .getOrCreate()

3.
设置执行参数
spark.conf.set("spark.driver.cores","8")
spark.conf.set("spark.driver.memory","4g")
spark.conf.set("spark.executor.memory","6g")
spark.conf.set("spark.yarn.executor.memoryOverhead","4g")
spark.conf.set("spark.executor.cores","4")
spark.conf.set("spark.default.parallelism","1000")
spark.conf.set("spark.executor.instances","100")

4. 这种写法 应该和命令行的写法差不多
from pyspark import SparkConf
conf = SparkConf().setMaster("local[2]").setAppName("DefinitiveGuide")\
.set("some.conf", "to.some.value")
```



```
设置成可以覆盖表里面的内容
spark.conf.set("spark.sql.legacy.allowCreatingManagedTableUsingNonemptyLocation", "true")
```



```
spark内部调用过程
结合下面的图片理解spark 参数
```

![截屏2021-07-12 上午11.31.41](/Users/rongdi.yin/Desktop/截屏2021-07-12 上午11.31.41.png)

```

```





### session

SparkSession 代替HiveContext 和 SQLcontext 成为统一的程序入口

```
```



```
import function

from pyspark.sql.functions import size

```







### 读取文件

```
读取text file
log_txt=spark.sparkContext.textFile("/path/to/data/sample_data.txt") //获得rdd
temp_var = log_txt.map(lambda k: k.split("\\t"))
log_df=temp_var.toDF(['column_name1','column_name2',...]) // 类型都是string
log_df = log_df.withColumn("field1Int", log_df["field1"].cast(IntegerType())) //类型转换
或者用udf转换类型

```



```
判断表是否存在 
spark._jsparkSession.catalog().tableExists('recommend.temp_rongdi_v2_userfeat3')

```



```
结果保存
insertInto()   saveAsTable()
saveTable 
使用 overwrite模式 会把表原来的分区都覆盖掉 
使用 append模式时， 如果存在同样的分区，不会将原来的分区删除，而是直接在文件夹里面增加（在spark3.0以后修改了这个bug

所以暂时还不能实现hive里面的 insert overwrite table

df.write.mode("overwrite").format("json").insertInto("recommend.temp_rongdi_v2_userfeat4",overwrite=True)
df.write.saveAsTable("recommend.temp_rongdi_v2_userfeat4",format="json",mode="append",partitionBy=['dt','country','scenario'])


结果分区：
指定partitionBy 或者调用paritionby
df.write.saveAsTable("recommend.temp_rongdi_v2_userfeat4",format="json",mode="append",partitionBy=['dt','country','scenario'])

保存成json格式：
df.repartition(1).write.json("/user/ld-rongdi_yin/wordcount/noresult/",mode='overwrite')
```





### 列

```
构造和引用列 使用 col() or column()  // under spark.sql.functions

df.select(
 df.col("DEST_COUNTRY_NAME"),
 col("DEST_COUNTRY_NAME"),
 column("DEST_COUNTRY_NAME"),
 'DEST_COUNTRY_NAME,
 $"DEST_COUNTRY_NAME",
 expr("DEST_COUNTRY_NAME"))
 
 改名    
 df.select(expr("DEST_COUNTRY_NAME AS destination"))
 df.select(expr("DEST_COUNTRY_NAME as destination").alias("DEST_COUNTRY_NAME"))
 
 df.withColumnRenamed("DEST_COUNTRY_NAME", "dest")
 
 创建新的列
 df.selectExpr(
 "*", // 包含所有的原始列
 "(DEST_COUNTRY_NAME = ORIGIN_COUNTRY_NAME) as withinCountry")
 
 df.withColumn("numberOne", lit(1))
 
 df.withColumn("withinCountry", expr("ORIGIN_COUNTRY_NAME ==
DEST_COUNTRY_NAME"))
 
 
 df.withColumn("new_gender", when(col("gender") === "M","Male")
                            .when(col("gender") === "F","Female")
                            .otherwise("Unknown").alias("new_gender"))
 df.withColumn("new_gender", 
      expr("case when gender = 'M' then 'Male' " +
                "when gender = 'F' then 'Female' " +
                "else 'Unknown' end").alias("new_gender"))
 
 直接使用列表达式
 df.selectExpr("DEST_COUNTRY_NAME as newColumnName", "DEST_COUNTRY_NAME")
 
 删除列
 df.drop("ORIGIN_COUNTRY_NAME", "DEST_COUNTRY_NAME")
 
 更改列的类型：
 df.withColumn("count2", col("count").cast("long"))
 
 
 过滤： filter 和 where 语句作用相同
 df.filter(col("count") < 2).show(2)
 df.where("count < 2").show(2)
 df.where(col("count") < 2).where(col("ORIGIN_COUNTRY_NAME") =!="Croatia")
 可以用来选择partition
 df.where('dt=2021-06-06 and country=MY')
 
 获取唯一\去重：
 df.select("ORIGIN_COUNTRY_NAME","DEST_COUNTRY_NAME").distinct()
 dataFrame.dropDuplicates("id","label")
 
 连接两个dataframe
 df.union(newDF)
 
 排序
 df.sort("count")
 df.orderBy("count", "DEST_COUNTRY_NAME")
 
 
 减小规模
 df.limit(5) 取前五个
 df.sample(withReplacement, fraction, seed)
 df2  = df.sample(withReplacement=False,fraction=0.1,seed=1000)
 
 
 # explode
 df.withColumn("splitted", split(col("Description"), " "))\
.withColumn("exploded", explode(col("splitted")))\
.select("Description", "InvoiceNo", "exploded")
 
 
 # 聚合
 df.select(sum("Quantity"))
 df.select(min("Quantity"), max("Quantity"))
 df.agg(collect_set("Country"), collect_list("Country"))  没用select 感觉很奇怪
 df.agg(countDistinct("column_name")) 和想的不一样 参见：
 https://stackoverflow.com/questions/37949494/how-to-count-occurrences-of-each-distinct-value-for-every-column-in-a-dataframe
 
 # group by
 df.groupBy("InvoiceNo").agg(
	count("Quantity").alias("quan"), expr("count(Quantity)"))
 df.groupBy("InvoiceNo").agg(expr("avg(Quantity)"),expr("stddev_pop(Quantity)"))
 
 # 重命名
 df.withColumnRenamed("_1", "x1")
 
 
 # explode
 >>> df = spark.createDataFrame([(1, "A", [1,2,3]), (2, "B", [3,5])],["col1", "col2", "col3"])
>>> from pyspark.sql.functions import explode
>>> df.withColumn("col3", explode(df.col3))

 # 持久化
 df = df.persist()
 DF1.cache() // 这个好一点
 
 # check 是否有null
 df.select("*").where(col("c").isNull()).limit(1)
 
```



```
spark使用 列表达式 expression 操作Row对象，以产生有效的结果值
```



### 行

```
row 对象没有schema 所以创建的时候要注意顺序

spark.sql.Row
```



df_temp_1 = spark.table('recommend.rcmd_userfeat_realtime_global_v3_rongdi_MY') \

​       .where("dt='2021-06-24' and country='MY' ") \

​       .select('userid','behavior')



df_user = df_mfs_vec.join(df_temp_1,'userid', 'left_outer')

### 添加文件

```
spark.sparkContext.addFile(path)
```



###  常用参数

```
${SPARK_HOME}/bin/spark-submit \
--master yarn \
--deploy-mode cluster \
--driver-memory 8g \
--num-executors 4 \
--executor-memory 8g \
--executor-cores 4 \
--files ${SPARK_HOME}/conf/hive-site.xml \
--py-files /path/file.egg /path/file.py


./bin/spark-submit \
  --master yarn-cluster \
  --num-executors 100 \
  --executor-memory 6G \
  --executor-cores 4 \
  --driver-memory 1G \
  --conf spark.default.parallelism=1000 \
  --conf spark.storage.memoryFraction=0.5 \
  --conf spark.shuffle.memoryFraction=0.3 \
```



### 数据类型

```
StructType, StructField, IntegerType, FloatType, StringType
```

```
struct usage

schema = ArrayType(StructType([
    StructField("startTime", StringType(), False),
    StructField("endTime", StringType(), False)
]))
MergeAdjacentUsages = udf(lambda xs: xs, schema)
```

```
类型转换
col("foo").cast(IntegerType())
```



### udf

```
关于在sql里面使用udf的一些总结
udf一定要测试
  1.在udf使用的地方，构造一模一样的输入数据测试udf
  2.构造输入数据： 去掉udf函数后，将代码直接在spark中运行，获得dataframe 然后直接limit（2W左右） 或者  sample 百分之1左右 存储一个临时表
  3.使用hive -f 执行sql， 这个sql 直接select * from temp_table
  4.使用 linux 管道将3的输出给到python udf.py 看有没有错误
  5总体命令： hive -f select.sql | python3 udf.py

在udf的使用中 一定要注意是否可能出现空值 在dict取值 如 a['name'] 一定要注意 里面是否有‘name’，如果没有程序出错 且不会报错， 并且如果name字段是空的话，a['name'] 是存在的，但是a['name'] 是null 或者None 这个时候使用len(a['name'])就会报错，所以要先判断type(a['name']) == list 或者其他类型

还有一个就是  sql的输入是 string类型 需要用json.loads() 解析 不然会出错


```



```
使用python编写udf， spark上的所有数据将先序列化为python可以理解的形式，然后启动python进程对其处理，之后将python的结果返回给sprk和jvm

而用scala写的话直接在jvm上运行，速度应该快一些

指定的类型与该函数返回的实际类型不符，Spark将不会抛出错误，而只会返回null来表示失败

1.在dataframe中使用
# 定义自定义函数

import numpy as np
def log_py(num):
    return float(np.log(num))

# 注册自定义函数
log_udf = functions.udf(log_py, FloatType())

# 使用自定义函数
dataframe = dataframe.withColumn(col, log_udf(col))


2、在sparkSQL中使用
# 定义自定义函数
def is_nulludf(fieldValue, defaultValue):
    if fieldValue == None:
        return defaultValue
    return fieldValue

# 注册自定义函数
spark.udf.register("is_nulludf", is_nulludf)

# 使用自定义函数
spark.sql("select col_name, is_nulludf(col_name) as col_name2 from tble ")

# 访问输入是struct
def udf_f (arr):
  // arr is a list of struct
  arr[0]['column_name']

# 空值处理
df.na.drop("any")  //删除含有空值的行
df.na.drop("all") //删除全部是空值的行
DataFrame.dropna() //上面函数的别名
df4.na.fill(50)
 df4.na.fill({'age': 50, 'name': 'unknown'})

```



### api 

```
创建临时表
dataframe.createOrReplaceTempView("name")
```



```
解释执行计划
dataframe.explain
```



```
选择非空
df.select(coalesce(col("Description"), col("CustomerId")))

```





```
withColumn(colName : String, col : Column) : DataFrame

example:
df.withColumn("Country", lit("USA"))
```



```
访问df的列：
df.withColumn("Country", lit(df.USA))
```



```
查看字段类型：
color_df.dtypes
查看列名：
color_df.columns

```





```
select 用法 
data = data.select(col("Name").alias("name"), col("askdaosdka").alias("age"))

聚合：
df.selectExpr("avg(count)", "count(distinct(DEST_COUNTRY_NAME))"

 改名    
 df.select(expr("DEST_COUNTRY_NAME AS destination"))
 df.select(expr("DEST_COUNTRY_NAME as destination").alias("DEST_COUNTRY_NAME"))
 
 创建新的列
 df.selectExpr(
 "*", // 包含所有的原始列
 "(DEST_COUNTRY_NAME = ORIGIN_COUNTRY_NAME) as withinCountry") .show(2)
 
 直接使用列表达式
 df.selectExpr("DEST_COUNTRY_NAME as newColumnName", "DEST_COUNTRY_NAME").
```



```
常量
from pyspark.sql.functions import lit
df.select(expr("*"), lit(1).alias("One"))
```



```python
组合字符串
df2=df.select(concat(df.firstname,df.middlename,df.lastname)
              .alias("FullName"),"dob","gender","salary")
```



```
udf返回list
spark.udf.register('getthirdcat',getthirdcat,ArrayType(IntegerType()))
```

```
take(n)  return a list of row
```



### join

```
用法：
join(other,on,how)
how – str, default inner. Must be one of: inner, cross, outer, full, full_outer, left, left_outer, right, right_outer, left_semi, and left_anti.

df.join(df2,'name','outer')
df.join(df2,df.name==df2.name,'inner')
df.join(df2,[df.name==df2.name,df.age==df2.age],'inner').select(df.name,df2.height)
```







### 例

```
from pyspark import SparkConf, SparkContext
from pyspark.sql.types import StructType, StructField, IntegerType, FloatType, StringType
from pyspark.sql.functions import udf
from pyspark.sql import SparkSession
from pyspark.sql import Row
import pandas as pd
import json
import sys
from pyspark.sql.types import ArrayType, IntegerType
from pyspark.sql.functions import col


spark = SparkSession\
       .builder\
       .appName("Pyspark on Hive Test")\
       .enableHiveSupport()\
       .getOrCreate()


spark.conf.set("spark.sql.legacy.allowCreatingManagedTableUsingNonemptyLocation", "true")


# todo: use udf to return multi value in order reduce
#       number of udf
def getsubcat(behaviors):
    vec = []
    for i in behaviors:
        vec.append(i.globalsubcat)
    return vec

def getthirdcat(behaviors):
    vec = []
    for i in behaviors:
        vec.append(i.globalthirdcat)
    return vec

def getubid(behaviors):
    vec = []
    for i in behaviors:
        result = str(i.shopid)+":"+str(i.itemid)
        vec.append(result)
    return vec

spark.udf.register('getsubcat',getsubcat,ArrayType(IntegerType()))
spark.udf.register('getthirdcat',getthirdcat,ArrayType(IntegerType()))
spark.udf.register('getubid',getubid,ArrayType(StringType()))

df = spark.sql('select pdpitemfeat.itemid as pdpitemid,pdpitemfeat.shopid as pdpshopid,pdpitemfeat.globalsubcat as pdpsubcat, pdpitemfeat.globalthirdcat as pdpthirdcat, getsubcat(behavior) as ubsubcat, getthirdcat(behavior) as ubthirdcat, getubid(behavior) as ubid from recommend.rcmd_multi_task_sampling_global_v2_userfeat where dt="2021-06-12" and country="SG"')

df.write.mode("overwrite").saveAsTable("recommend.temp_rongdi_relevant_global_spark")


df.write.format('json').mode("overwrite").saveAsTable("recommend.temp_rongdi_relevant_global_spark_json")
```



### 例2

```

from pyspark import SparkConf, SparkContext
from pyspark.sql.types import StructType, StructField, IntegerType, FloatType, StringType
from pyspark.sql.functions import udf
from pyspark.sql import SparkSession
from pyspark.sql import Row
import pandas as pd
import json
import sys
from pyspark.sql.types import ArrayType, IntegerType
from pyspark.sql.functions import col


spark.conf.set("spark.sql.legacy.allowCreatingManagedTableUsingNonemptyLocation", "true")


spark.conf.set("spark.driver.cores","8")
spark.conf.set("spark.driver.memory","4g")
spark.conf.set("spark.executor.memory","6g")
spark.conf.set("spark.yarn.executor.memoryOverhead","4g")
spark.conf.set("spark.executor.cores","4")
spark.conf.set("spark.default.parallelism","1000")
spark.conf.set("spark.executor.instances","100")


df = spark.table('recommend.rcmd_feature_multi_task_sampling_v3')

df = df.select('pdpitemfeat.itemid
df = df.select(df.pdpitemfeat.itemid.alias('item1'),df.pdpitemfeat.itemid.alias('item2'))



def getsubcat(behaviors):
    vec = []
    for i in behaviors:
        vec.append(i.subcat)
    return vec

def getthirdcat(behaviors):
    vec = []
    for i in behaviors:
        vec.append(i.thirdcat)
    return vec

def getubid(behaviors):
    vec = []
    for i in behaviors:
        result = str(i.shopid)+":"+str(i.itemid)
        vec.append(result)
    return vec


spark.udf.register('getsubcat',getsubcat,ArrayType(IntegerType()))
spark.udf.register('getthirdcat',getthirdcat,ArrayType(IntegerType()))
spark.udf.register('getubid',getubid,ArrayType(StringType()))

df = spark.sql('select pdpitemfeat.itemid as pdpitemid,pdpitemfeat.shopid as pdpshopid,pdpitemfeat.subcat as pdpsubcat, pdpitemfeat.thirdcat as pdpthirdcat, getsubcat(behavior) as ubsubcat, getthirdcat(behavior) as ubthirdcat, getubid(behavior) as ubid from recommend.rcmd_feature_multi_task_sampling_v3 where dt="2021-06-12" and country="SG"')

df.write.mode("overwrite").saveAsTable("recommend.temp_rongdi_relevant_spark")




udf(getsubcat, ArrayType(IntegerType()))

df_subcat = df.withColumn("ubsubcat",getsubcat(col('behavior')))

spark.sql('select getsubcat(behavior) from recommend.rcmd_feature_multi_task_sampling_v3').first()



--美团
spark-submit --master yarn 
  --num-executors 100 \
  --executor-memory 6G \
  --executor-cores 4 \
  --driver-memory 1G \
  --executor-cores 4 \
  --conf spark.default.parallelism=1000 \
  --conf spark.storage.memoryFraction=0.5 \
  --conf spark.shuffle.memoryFraction=0.3 \
  --py-files job.py


pyspark --num-executors 50 --driver-memory 8g --executor-memory 4g --conf spark.default.parallelism=1000

------------------------step2 

spark.sparkContext.addFile('./thirdcat2root.json')

with open('thirdcat2root.json','r') as f:
    thirdcat2root = json.load(f)

def ifSimilar(key1,value1,key2,value2):
    if key1 == key2:
        return True
    if '0' in value1:
        value1.remove('0')
    if '0' in value2:
        value2.remove('0')
    for i in value1:
        if i in value2:
            return True
    return False

def parse(x, default_return=[]):
    if x == NULL:
        return default_return
    try:
        return json.loads(x)
    except Exception as e:
        return default_return


def getsimilar(pdpthirdcat,ubsubcat,ubthirdcat,ubid):
    vec = []
    for i in range(len(ubsubcat)):
        pdpthirdcat = str(pdpthirdcat)
        if pdpthirdcat in thirdcat2root and str(ubthirdcat[i]) in thirdcat2root:
            result = ifSimilar(str(pdpthirdcat),thirdcat2root[str(pdpthirdcat)],
                                    str(ubthirdcat[i]),thirdcat2root[str(ubthirdcat[i])])
        else:
            result = 1
        vec.append([ubsubcat[i],ubthirdcat[i],ubid[i],int(result)])
    return vec


schema = ArrayType(StructType([
    StructField("ubsubcat",IntegerType()),
    StructField("ubthirdcat",IntegerType()),
    StructField("ubId",StringType()),
    StructField("result",IntegerType())
    ]
    )
)

spark.udf.register('getsimilar',getsimilar,schema)

df = spark.sql('''
    select pdpitemid,pdpshopid,pdpsubcat,pdpthirdcat,getsimilar(pdpthirdcat,ubsubcat,ubthirdcat,ubid) as similarity
    from recommend.temp_rongdi_relevant_spark
''')

df.write.mode("overwrite").saveAsTable("recommend.temp_rongdi_similarity2_spark")

----------------------------step 3

def getstatistic(similarity):
    norelevant = 0
    for item in similarity:
        if item.result == 0:
            norelevant +=1
    return norelevant


def getlen(similarity):
    return len(similarity)


spark.udf.register('getstatistic',getstatistic,IntegerType())
spark.udf.register('getlen',getlen,IntegerType())

df = spark.sql('''
    select getlen(similarity) as total ,getstatistic(similarity) as norel
    from recommend.temp_rongdi_similarity2_spark
''')

df.write.mode("overwrite").saveAsTable("recommend.temp_rongdi_statistic_spark")


------------------------step 4
spark.sql('''
    select sum(total) as t, sum(norel) as n
    from recommend.temp_rongdi_statistic_spark
''').first()


----------------------还有需要做的事情
1. 参数设置尝试 看那种比较快
2. 用命令行执行文件而不是在shell中执行            直接spark-submit 完事儿
3. udf直接返回多个列从而不需要定义多个udf

```



```
例3  将string 转换成 vec

def trans(vec_string):
    vec = []
    for i in vec_string.split(' '):
        vec.append(float(i))
    return vec

schema = ArrayType(FloatType())

trans_udf = udf(trans, schema)

log_vec = log_df.withColumn('id_vec',trans_udf(log_df.vec))
log_txt = spark.sparkContext.textFile('/user/ld-junen_tan/item_embedding/MY/embedding_v3')
```





### 统计

```
统计某列的出现次数
df.groupby('column_name').count()

```



```
统计某列加和
df.agg(sum(col('name')))
```



```
列的基本统计信息  有 最值  方差等
df = spark_df.describe('a')
d.show()
```





### 参数设置

```

```



```
提交文件
spark-submit file.py

```







### 常见错误

```
spark dataframe 保存成hive表的时候 需要保证dataframe的列名合法 不能有 . 之类的名称
！
```



























 