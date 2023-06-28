# 交换分区性能测试

这个代码主要用于测试使用交换分区后代码的性能下降程度。

## 测试流程

1. 创建一个控制组：
   ```shell {.line-numbers}
   $ sudo mkdir /sys/fs/cgroup/memory/mygroup
   ```
2. 设置控制组的内存限制：
   ```shell {.line-numbers}
   $ sudo sh -c "echo 500M > /sys/fs/cgroup/memory/mygroup/memory.limit_in_bytes"
   ```
   上述命令将内存限制设置为500兆字节（M）。
3. 在控制组中启动程序：
   ```shell {.line-numbers}
   $ sudo cgexec -g memory:mygroup /path/to/your/program
   ```
   这会在指定的控制组 mygroup 中启动位于 /path/to/your/program 的程序。
4. 无限制运行程序

**注：程序的内存占用不能过于超过内存限制，否则难以运行结束。**

## 测试结果

运行环境：
```shell {.line-numbers}
System:    Host: wzw-NUC7i5BNH Kernel: 5.15.0-73-generic x86_64 bits: 64 Console: tty 0
           Distro: Ubuntu 20.04.5 LTS (Focal Fossa)
Machine:   Type: Desktop System: Intel product: NUC7i5BNH v: J57645-310 serial: G6BN8230083K
           Mobo: Intel model: NUC7i5BNB v: J31144-310 serial: GEBN82000346 UEFI: Intel v: BNKBL357.86A.0062.2018.0222.1644
           date: 02/22/2018
CPU:       Topology: Dual Core model: Intel Core i5-7260U bits: 64 type: MT MCP L2 cache: 4096 KiB
           Speed: 3401 MHz min/max: 400/3400 MHz Core speeds (MHz): 1: 3401 2: 3400 3: 3400 4: 3400
Graphics:  Device-1: Intel Iris Plus Graphics 640 driver: i915 v: kernel
           Display: server: X.org 1.20.13 driver: i915 tty: 267x79
           Message: Advanced graphics data unavailable for root.
Audio:     Device-1: Intel Sunrise Point-LP HD Audio driver: snd_hda_intel
           Sound Server: ALSA v: k5.15.0-73-generic
Network:   Device-1: Intel Ethernet I219-V driver: e1000e
           IF: eno1 state: up speed: 1000 Mbps duplex: full mac: 94:c6:91:1f:a2:f4
           Device-2: Intel Wireless 8265 / 8275 driver: iwlwifi
           IF: wlp58s0 state: down mac: d4:6d:6d:99:c6:6d
           IF-ID-1: docker0 state: down mac: 02:42:15:05:f1:22
Drives:    Local Storage: total: 238.47 GiB used: 152.35 GiB (63.9%)
           ID-1: /dev/sda vendor: Intel model: SSDSC2KW256G8 size: 238.47 GiB
Partition: ID-1: / size: 233.18 GiB used: 152.35 GiB (65.3%) fs: ext4 dev: /dev/sda2
Sensors:   System Temperatures: cpu: 48.0 C mobo: N/A
           Fan Speeds (RPM): N/A
Info:      Processes: 227 Uptime: 19d 17h 17m Memory: 3.72 GiB used: 717.2 MiB (18.8%) Shell: bash inxi: 3.0.38
```

测试结果：
```shell {.line-numbers}
$ ./bin/swap
Sum: 1837700959
Time: 14 ms
$ cgexec -g memory:mygroup ./bin/swap
Sum: -1414375120
Time: 641 ms
```