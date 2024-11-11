/*
 * Copyright (c) 2023 Institute of Parallel And Distributed Systems (IPADS), Shanghai Jiao Tong University (SJTU)
 * Licensed under the Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *     http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
 * PURPOSE.
 * See the Mulan PSL v2 for more details.
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/syscall.h>

#include "perf_tools.h"

#define TEST_NUM PERF_NUM_SMALL

perf_time_t *start_perf_time;
perf_time_t *end_perf_time;
perf_time_t *total_perf_time;

void *thread_routine()
{
        return 0;
}

int main(int argc, char *argv[])
{
        if (bind_thread_to_core(3) < 0)
                error("sched_setaffinity failed!\n");

        start_perf_time = malloc(sizeof(perf_time_t));
        end_perf_time = malloc(sizeof(perf_time_t));
        total_perf_time = malloc(sizeof(perf_time_t));
        total_perf_time->cycle_sum = 0;
        total_perf_time->time_sum = 0;
        pthread_t thread;
        int i;
        info("Start measure create pthread\n");
        for (i = 0; i < TEST_NUM; i++) {
                record_time(start_perf_time);
                pthread_create(&thread, NULL, thread_routine, NULL);
                record_time(end_perf_time);
                accumulate_perf_record(
                        start_perf_time, end_perf_time, total_perf_time);
                pthread_join(thread, NULL);
        }
        info("Create Pthread result:\n");
        print_accumulate_perf_result(total_perf_time, TEST_NUM);

        free(start_perf_time);
        free(end_perf_time);
        free(total_perf_time);

        return 0;
}
