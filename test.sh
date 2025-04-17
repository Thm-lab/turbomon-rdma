#!/bin/bash
clear

# 显示帮助信息
show_help() {
    echo "使用方法: $0 [选项]"
    echo ""
    echo "选项:"
    echo "  --sketch VALUE    指定sketch名称"
    echo "                    可选值: cm, cs, es, hp, um, sl"
    echo "  --mode VALUE      指定运行模式"
    echo "                    可选值: send, recv"
    echo "  --op VALUE        指定操作参数，可多次使用"
    echo "                    可选值: max, min, exist, distinct, merge, filter, all"
    echo "  -h, --help        显示此帮助信息"
    echo ""
    echo "说明:"
    echo "  op参数含义为开启算子，开启后运行会用算子去处理sketch数据，支持任意个op同时开启"
    echo "  sketch参数表示运行哪个sketch，因为RDMA网卡有限，不能同时进行多个测试"
    echo "  mode表示收发模式，应先开启发送端后再启动接收端，尽量留出几秒时间等待编译"
    echo ""
    echo "示例:"
    echo "  $0 --sketch cm --mode send --op max --op min"
    echo ""
    echo "注意:"
    echo "  在不同设备上运行需要修改test.h中绑定的IP和MAC地址"
    exit 0
}

# 解析命令行参数
while [[ "$#" -gt 0 ]]; do
    case $1 in
        --sketch)
            SKETCH="$2"
            shift 2
            ;;
        --mode)
            MODE="$2"
            shift 2
            ;;
        --op)
            OP_PARAMS+=("$2")
            shift 2
            ;;
        -h|--help)
            show_help
            ;;
        *)
            echo "错误: 未知参数 $1"
            show_help
            ;;
    esac
done

# 生成配置文件
python3 op_config.py $(printf -- "--op %s " "${OP_PARAMS[@]}")

if [ ! -d "build" ]; then
    mkdir -p build
fi
current_dir=$(basename "$PWD")
if [ "$current_dir" != "build" ]; then
    cd build
fi
cmake .. &> build.log
if [ $? -ne 0 ]; then
    exit 1
fi
make -j4 --no-print-directory | tee make.log
if [ $? -ne 0 ]; then
    exit 1
fi
echo "Build Success"

case $MODE in
    send)
        echo "Runing: ./bin/${SKETCH}_send 10.0.0.5 0000:5e:00.0 -l 0-3"
        sudo ./bin/${SKETCH}_send 10.0.0.5 0000:5e:00.0 -l 0-3 | tee send.log
        ;;
    recv)
        echo "Ruing sudo ./bin/${SKETCH}_recv 10.0.0.5 auxiliary/mlx5_core.sf.2"
        sudo ./bin/${SKETCH}_recv 10.0.0.5 auxiliary/mlx5_core.sf.2 | tee recv.log
        ;;
esac