import numpy as np
import torch
import torch.nn as nn

def im2col(x, field_height, field_width, padding=1, stride=1):
    N, C, H, W = x.shape
    
    out_height = (H + 2 * padding - field_height) // stride + 1
    out_width = (W + 2 * padding - field_width) // stride + 1

    i0 = np.repeat(np.arange(field_height), field_width)
    i0 = np.tile(i0, C)
    i1 = stride * np.repeat(np.arange(out_height), out_width)
    
    j0 = np.tile(np.arange(field_width), field_height * C)
    j1 = stride * np.tile(np.arange(out_width), out_height)
    
    i = i0.reshape(-1, 1) + i1.reshape(1, -1)
    j = j0.reshape(-1, 1) + j1.reshape(1, -1)
    k = np.repeat(np.arange(C), field_height * field_width).reshape(-1, 1)

    p = padding
    x_padded = np.pad(x, ((0, 0), (0, 0), (p, p), (p, p)), mode='constant')
    cols = x_padded[:, k, i, j]
    
    C = x.shape[1]
    cols = cols.transpose(1, 2, 0).reshape(field_height * field_width * C, -1)
    
    return cols

def my_conv(x, w, b, stride=1, padding=1):
    N, C, H, W = x.shape
    FN, C, KH, KW = w.shape
    
    out_h = (H + 2 * padding - KH) // stride + 1
    out_w = (W + 2 * padding - KW) // stride + 1

    col = im2col(x, KH, KW, padding, stride)    
    col_w = w.reshape(FN, -1)

    out = np.dot(col_w, col) + b.reshape(-1, 1)
    out = out.reshape(FN, out_h, out_w, N).transpose(3, 0, 1, 2)

    return out

#-------------------------------------------------------------------

batch_size = 2
in_channels = 3
h, w = 10, 10
n_filters = 4
kernel_size = 3
stride = 1
padding = 1


x_np = np.random.randn(batch_size, in_channels, h, w).astype(np.float32)
x_torch = torch.from_numpy(x_np)

conv = nn.Conv2d(in_channels, n_filters, kernel_size, stride=stride, padding=padding)

weights_np = conv.weight.data.numpy()
bias_np = conv.bias.data.numpy()

my_output = my_conv(x_np, weights_np, bias_np, stride, padding)
torch_output = conv(x_torch).data.numpy()

diff = np.abs(my_output - torch_output).max()
print(f"Максимальная разница между результатами: {diff}")