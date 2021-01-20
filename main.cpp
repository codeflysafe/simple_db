#include <iostream>
#include "bmgr.h"
#include "instruction.h"
#include <ctime>
#include <log.h>
using namespace std;

/**
 * 初始化数据库文件
 * 随机写入50000个page
 */
void init_db()
{
    auto bm = make_shared<BMgr>();
    for (unsigned int j = 1; j <= 50000; j++)
    {
        auto frame = generate_frame();
        bm->fix_new_page(frame);
    }
}

/**
 * 执行test
 * @param bm BMgr的shared_ptr
 */
void run_test(const BMgr::sptr &bm)
{
    auto ins_vector = Instruction::read_instructions("../data-5w-50w-zipf.txt");
    int index = 0;
    for (auto &i : *ins_vector)
    {
        index++;
        i.execute(bm);
    }
}

int main()
{
    // init_db();
    auto bm = make_shared<BMgr>();
    clock_t start, end;
    start = clock();
    run_test(bm);
    end = clock();
    char log[500];
    sprintf(log, "buffer_size:%d,total_io:%d,total_hit:%d,interval:%0.2fs",
            BUFFER_SIZE, bm->get_io_count(), bm->get_hit_count(), (float)(end - start) / CLOCKS_PER_SEC);
    logger(log);
    return 0;
}