#!/usr/bin/env python
# encoding: utf-8

import sys
import argparse

if __name__ == "__main__":

    parser = argparse.ArgumentParser()

    parser.add_argument(dest = "m", help = "pleaer enter the m...")
    parser.add_argument(dest = "n", help = "pleaer enter the n...")
    args = parser.parse_args()

    print "%d ^ %d = %d" % (args.m,  args.n, args.m ** args.n)