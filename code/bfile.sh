#!/bin/bash

# 定義 grid 的起始值和增量
grids=(30 50 100 150 200 250 300 350 400 450 500 550 600 650 700 750 800 850 900 950 1000)

# 遍歷 grid 值並執行流程
for grid in "${grids[@]}"; do
  (
    echo "執行 make grid=$grid"
    make grid=$grid
    sleep 5  # 等待 5 秒，確保 make 完成

    echo "執行 ./exe/start 3"
    ./exe/start 3
    sleep 30  # 等待 30 秒，確保程序執行完成

    echo "執行 make clean"
    make clean
    sleep 5  # 等待 5 秒，確保清理完成
  ) &
done

# 等待所有子進程結束
wait

echo "所有程序已執行完畢。"

