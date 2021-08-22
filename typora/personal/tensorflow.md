# tensorflow learn

## learn rate

```
# decay
schuduler = tf.keras.optimizers.schedules.ExponentialDecay(args.lr, 5696000 * 128 / GLOBAL_BATCH_SIZE, 0.9,staircase=True)
optimizer = tf.keras.optimizers.Adam(learning_rate=schuduler)
```









### tensorboard

//for pytorch
from torch.utils.tensorboard import SummaryWriter
writer = SummaryWriter(file_dir)
writer.add_scalar('name', loss_ctr, step)

