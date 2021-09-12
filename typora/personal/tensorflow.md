# tensorflow learn

## learn rate

```
# decay
schuduler = tf.keras.optimizers.schedules.ExponentialDecay(args.lr, 5696000 * 128 / GLOBAL_BATCH_SIZE, 0.9,staircase=True)
optimizer = tf.keras.optimizers.Adam(learning_rate=schuduler)
```





```
在静态图里面打印：
tf.print()
```



```
多卡训练：
mirrored_strategy = tf.distribute.MirroredStrategy()
mirrored_strategy = tf.distribute.MirroredStrategy(devices=["/gpu:0","/gpu:1"])

dist_dataset = my_strategy.experimental_distribute_dataset(dataset)
或者：
with strategy.scope():  #创建模型、定义损失函数都需要定义在strategy.scope下
    ...
    
```







### tf tensor 操作

```
tf.slice(
    input_, begin, size, name=None
)
从 begin位置开始，获取size大小的vec

t = tf.constant([[[1, 1, 1], [2, 2, 2]],
                 [[3, 3, 3], [4, 4, 4]],
                 [[5, 5, 5], [6, 6, 6]]])
tf.slice(t, [1, 0, 0], [1, 1, 3])  # [[[3, 3, 3]]]
tf.slice(t, [1, 0, 0], [1, 2, 3])  # [[[3, 3, 3],
                                   #   [4, 4, 4]]]
tf.slice(t, [1, 0, 0], [2, 1, 3])  # [[[3, 3, 3]],
                                   #  [[5, 5, 5]]]
```



```
tf.identity()
复制一个tensor

a = tf.constant([0.78])
a_identity = tf.identity(a)
a.numpy()

a_identity.numpy()

```





### 损失函数

```
tf.nn.compute_average_loss()
计算vec的均值，返回的是标量
```



```
tf.keras.losses.BinaryCrossentropy(
    from_logits=False, label_smoothing=0, axis=-1,
    reduction=losses_utils.ReductionV2.AUTO, name='binary_crossentropy'
)

当之前输入进过softmax的话，则from_logits=False，没经过softmax用from_logits=True

# Example 1: (batch_size = 1, number of samples = 4)
y_true = [0, 1, 0, 0]
y_pred = [-18.6, 0.51, 2.94, -12.8]
bce = tf.keras.losses.BinaryCrossentropy(from_logits=True)
bce(y_true, y_pred).numpy()  # 0.865


```



### 模型保存

```
tf.saved_model.save(
    obj, export_dir, signatures=None, options=None
)


tf.saved_model.save(model, '/tmp/adder')
```





### tensorboard

//for pytorch
from torch.utils.tensorboard import SummaryWriter
writer = SummaryWriter(file_dir)
writer.add_scalar('name', loss_ctr, step)

