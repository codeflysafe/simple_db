"""
Parse the info from log.

"""

import matplotlib.pyplot as plt
from tqdm import tqdm
import argparse
import pandas as pd


def draw(buffer_sizes: list, total_ios: list, total_hits: list, intervals: list, path: str) -> None:
    """ Draw infos
    """
    plt.subplot(311)
    plt.plot(buffer_sizes, total_ios, c='r', label='total io')
    plt.plot(buffer_sizes, total_hits, c='b', label='total hits')
    plt.xlabel('buffer_size')
    plt.ylabel('count')
    plt.legend()
    # plt.savefig(f'{path}/info.png')
    # plt.show()
    plt.subplot(312)
    hit_rates = [hit * 1.0 /
                 500000 for hit in total_hits]
    plt.plot(buffer_sizes, hit_rates, label='hit rate')
    plt.ylabel('hit rate')
    plt.legend()
    plt.subplot(313)
    plt.plot(buffer_sizes, intervals, c='y', label='intervals')
    plt.ylabel('s')
    plt.legend()
    plt.savefig(f'{path}/analysis.png')

    analysis = pd.DataFrame({
        'buffer_sizes': buffer_sizes,
        'total_ios': total_ios,
        'total_hits': total_hits,
        'hit_rates': hit_rates,
        'intervals/s': intervals,

    })
    analysis.to_csv('analysis.csv', index=False)
    # plt.show()


def extrac_infos(log_path: str):
    """ Extract info from log .
    """
    buffer_sizes, total_ios, total_hits, intervals = [], [], [], []
    with open(log_path) as f:
        lines = f.readlines()
        for line in tqdm(lines):
            words = line.replace('\t', ',').replace('\n', '').split(',')
            # print(words)
            buffer_size = int(words[1].split(':')[1])
            total_io = int(words[2].split(':')[1])
            total_hit = int(words[3].split(':')[1])
            interval = float(words[4].split(':')[1][:-1])
            buffer_sizes.append(buffer_size)
            total_ios.append(total_io)
            total_hits.append(total_hit)
            intervals.append(interval)
    return buffer_sizes, total_ios, total_hits, intervals


def main(opt):
    buffer_sizes, total_ios, total_hits, intervals = extrac_infos(opt.log_path)
    draw(buffer_sizes, total_ios, total_hits, intervals, opt.save_path)


if __name__ == '__main__':
    parser = argparse.ArgumentParser('analysis')
    parser.add_argument('-log_path', type=str, default='log.txt')
    parser.add_argument('-save_path', type=str, default='.')
    opt = parser.parse_args()
    main(opt)
