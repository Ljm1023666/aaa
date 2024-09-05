#!/usr/bin/env python3

import argparse
import asyncio
import json
import sys
from asyncio.subprocess import DEVNULL, PIPE, STDOUT
from dataclasses import dataclass

import psutil

if sys.version_info[0] != 3 or sys.version_info[1] < 6:
    print(
        "This script requires Python version 3.7 and later. Please upgrade your Python version to grade this lab."
    )
    sys.exit(0)


@dataclass
class LineCapture:
    """Line capture definition. Used for parsing scores.json in lab folders."""

    content: str
    msg: str
    proposed: int
    actual: int = 0


def killall(pid):
    """Kill all children processes of a process."""
    try:
        parent = psutil.Process(pid)
        for child in parent.children(recursive=True):
            child.kill()
        parent.kill()
    except psutil.NoSuchProcess:
        pass


captures = []
process = None


async def main(args: argparse.Namespace):
    """Main grading function."""

    try:
        with open(args.file, "rb") as f:
            line_captures = json.load(f)
    except FileNotFoundError:
        print(f"File {args.file} not found.")
        raise
    except json.JSONDecodeError:
        print(f"File {args.file} is not a valid JSON file.")
        raise

    for line_capture in line_captures:
        try:
            captures.append(
                LineCapture(
                    content=line_capture["capture"],
                    msg=line_capture["msg"],
                    proposed=line_capture["proposed"],
                )
            )
        except KeyError:
            print("Invalid line capture definition.")
            raise
    process = await asyncio.create_subprocess_exec(
        *args.command, stdin=DEVNULL, stdout=PIPE, stderr=STDOUT
    )
    for line_capture in captures:
        try:
            while True:
                line = await asyncio.wait_for(process.stdout.readline(), args.timeout)
                if len(line) == 0:
                    break
                if line_capture.content in line.decode():
                    line_capture.actual = line_capture.proposed
                    break
        except asyncio.TimeoutError:
            break

    killall(process.pid)
    await process.wait()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="A simple grader on listening the stdout"
    )
    parser.add_argument(
        "-f",
        "--file",
        type=str,
        dest="file",
        required=True,
        help="Score definition on certain lines of stdout.",
    )
    parser.add_argument(
        "-t",
        "--timeout",
        type=int,
        dest="timeout",
        required=True,
        help="Timeout for the grading process.",
    )
    parser.add_argument("command", nargs=argparse.REMAINDER, help="Command to grade.")
    args = parser.parse_args()
    try:
        result = asyncio.run(main(args))
    except KeyboardInterrupt:
        if process:
            killall(process.pid)

    scores = 0
    for line_capture in captures:
        print(f"{line_capture.msg}: {line_capture.actual}")
        scores += line_capture.actual

    sys.exit(scores)
