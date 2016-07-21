#!/usr/bin/env python

# Copyright (c) 2009 Giampaolo Rodola'. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""psutil is a cross-platform library for retrieving information on
running processes and system utilization (CPU, memory, disks, network)
in Python.
"""

import os
import sys
try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension


def get_version():
    return "1.1"


def get_description():
    return "aaa"

extensions = [Extension(
    '_fn',
    sources=[
        'fjs/_fn.cpp',
        'fjs/app.cpp',
        'fjs/conninode.cpp',
        'fjs/process.cpp'
    ],
    extra_link_args=[
        '-lpcap', '-lpthread'
    ],
)]


def main():
    setup_args = dict(
        name='fjs',
        version=get_version(),
        description=__doc__,
        long_description=get_description(),
        keywords=[
            'ps', 'top', 'kill', 'free', 'lsof', 'netstat', 'nice',
            'tty', 'ionice', 'uptime', 'taskmgr', 'process', 'df',
            'iotop', 'iostat', 'ifconfig', 'taskset', 'who', 'pidof',
            'pmap', 'smem', 'monitoring', 'ulimit', 'prlimit',
        ],
        author='Giampaolo Rodola',
        author_email='g.rodola <at> gmail <dot> com',
        url='http://code.google.com/p/psutil/',
        platforms='Platform Independent',
        license='BSD',
        packages=['fjs'],
        # see: python setup.py register --list-classifiers
        classifiers=[
            'Development Status :: 5 - Production/Stable',
            'Environment :: Console',
            'Environment :: Win32 (MS Windows)',
            'Intended Audience :: Developers',
            'Intended Audience :: Information Technology',
            'Intended Audience :: System Administrators',
            'License :: OSI Approved :: BSD License',
            'Operating System :: MacOS :: MacOS X',
            'Operating System :: Microsoft :: Windows :: Windows NT/2000',
            'Operating System :: Microsoft',
            'Operating System :: OS Independent',
            'Operating System :: POSIX :: BSD :: FreeBSD',
            'Operating System :: POSIX :: Linux',
            'Operating System :: POSIX :: SunOS/Solaris',
            'Operating System :: POSIX',
            'Programming Language :: C',
            'Programming Language :: Python :: 2',
            'Programming Language :: Python :: 2.4',
            'Programming Language :: Python :: 2.5',
            'Programming Language :: Python :: 2.6',
            'Programming Language :: Python :: 2.7',
            'Programming Language :: Python :: 3',
            'Programming Language :: Python :: 3.0',
            'Programming Language :: Python :: 3.1',
            'Programming Language :: Python :: 3.2',
            'Programming Language :: Python :: 3.3',
            'Programming Language :: Python :: 3.4',
            'Programming Language :: Python :: Implementation :: CPython',
            'Programming Language :: Python :: Implementation :: PyPy',
            'Programming Language :: Python',
            'Topic :: Software Development :: Libraries :: Python Modules',
            'Topic :: Software Development :: Libraries',
            'Topic :: System :: Benchmark',
            'Topic :: System :: Hardware',
            'Topic :: System :: Monitoring',
            'Topic :: System :: Networking :: Monitoring',
            'Topic :: System :: Networking',
            'Topic :: System :: Systems Administration',
            'Topic :: Utilities',
        ],
    )
    if extensions is not None:
        setup_args["ext_modules"] = extensions
    setup(**setup_args)

if __name__ == '__main__':
    main()
