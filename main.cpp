#include <iostream>
#include "bmgr.h"
#include "instruction.h"
#include <ctime>

using namespace std;

/**
 * 初始化数据库文件
 * 随机写入50000个page
 */
void init_db(const BMgr::sptr &bm)
{
    for (unsigned int j = 1; j <= 50000; j++)
    {
        auto frame = generate_random_frame();
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
    auto bm = make_shared<BMgr>();
    init_db(bm);
    time_t start = time(NULL);
    run_test(bm);
    time_t end = time(NULL);
    printf("buffer_size:%d,total_io:%d,total_hit:%d,interval:%ld s",
           DEF_BUF_SIZE, bm->get_io_count(), bm->get_hit_count(), (end - start));
    return 0;
}