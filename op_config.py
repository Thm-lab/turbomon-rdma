import argparse
import sys
from jinja2 import Environment, FileSystemLoader

# 允许的宏名称
ALLOWED_OPS = {
    "ALL", "MAX", "MIN", "EXIST", "DISTINCT", "MERGE", "FILTER", "all", "max",
    "min", "exist", "distinct", "merge", "filter"
}


def generate_config(ops):
    """生成 op_enable.h 配置文件"""
    enabled_ops = set()

    enable_all = False
    for op in ops:
        for part in op.split(","):
            if part.strip().lower() == "all":
                enable_all = True

    if enable_all:
        enabled_ops = ALLOWED_OPS.copy()

    if ops:
        for op in ops:
            if op not in ALLOWED_OPS:
                print(f"invalid op: '{op}', optional: {ALLOWED_OPS}")
                sys.exit(1)
            enabled_ops.add(op)

    # 默认关闭
    config = {
        "op_max": 0,
        "op_min": 0,
        "op_exist": 0,
        "op_distinct": 0,
        "op_merge": 0,
        "op_filter": 0
    }

    # 根据参数设置为 1
    for op in enabled_ops:
        key = f"op_{op.lower()}"
        config[key] = 1

    # 渲染模板并写入文件
    env = Environment(loader=FileSystemLoader("./include/config/"))
    template = env.get_template("op_enable.template")
    with open("./include/config/op_enable.h", "w") as f:
        f.write(template.render(**config))
    print("generate op_enable.h successfully!")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--op",
        action="append",
        default=[],
    )
    args = parser.parse_args()
    generate_config(args.op)
