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

#include <chcore/launcher.h>
#include <chcore/proc.h>
#include <stdio.h>
#include <assert.h>

int main()
{
        pid_t pid;
        char *args[1];
        struct new_process_caps new_process_caps;

        args[0] = "/test_hello.bin";
        pid = create_traced_process(1, args, &new_process_caps);
        assert(pid >= 0);
        printf("create_process success.\n");
        printf("Test finish!\n");
        return 0;
}
