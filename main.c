#define _CRT_SECURE_NO_WARNINGS
#include"cnfparser.h"
#include"display.h"
#include"dpll_solver_v1.h"
#include"dpll_solver_v2.h"
#include"sudoku.h"

int main()
{
    printf("-------------------------------------------\n");
    printf("********这是一个SAT求解器和数独游戏********\n");
    printf("-------------------------------------------\n");
    while (1) {
        printf("\n");
        printf("1.求解cnf文件\n2.数独游戏\n0.退出程序\n");
        printf("请输入您的选择：");
        int choice1;
        scanf("%d", &choice1);
        printf("\n");
        if (choice1 == 0) break;
        switch (choice1) {
            case 1: {
                printf("请输入cnf文件路径（路径收尾不要加双引号！）：");
                char cnf_file_path[512];
                scanf("%s", cnf_file_path);
                getchar();
                printf("\n");
                formula* F = parse_cnf(cnf_file_path);
                if (!F) {
                    fprintf(stderr, "解析CNF文件失败\n");
                    break;
                }
                Assignment A;
                double time_ms, time_ms_optimized;
                bool SAT_optimized = solve_dpll_v2(F, &A, &time_ms_optimized);
                print_result(SAT_optimized, &A, F->var_num, time_ms_optimized);
                //将.cnf文件名改为同名的.res文件
                size_t len = strlen(cnf_file_path);
                char res_file_path[512];
                if (len > 4) {
                    memcpy(res_file_path, cnf_file_path, len - 4);
                    strcpy(res_file_path + (len - 4), ".res");
                }
                write_to_file(res_file_path, SAT_optimized, &A, F->var_num, time_ms_optimized);
                printf("\n");
                bool SAT = solve_dpll_v1(F, &A, &time_ms);
                print_result(SAT, &A, F->var_num, time_ms);
                if (time_ms == time_ms_optimized) printf("时间优化率为0\n");
                else printf("时间优化率为：[(t-t0)/t]*100%% = %.2f%%\n", (time_ms - time_ms_optimized) / time_ms * 100.00);
                free(A.values);
                free_formula(F);
                break;
            }
            case 2: {
                while (1) {
                    printf("数独种类： 1.普通数独  2.百分号数独\n输入0退出数独游戏\n");
                    printf("请输入您的选择：");
                    int choice2;
                    scanf("%d", &choice2);
                    printf("\n");
                    if (choice2 == 0) break;
                    switch (choice2) {
                        case 1: {
                            while (1) {
                                printf("操作选择： 1.解决数独  2.随机生成一个数独\n输入0重新选择数独种类\n");
                                printf("请输入您的选择：");
                                int choice3;
                                scanf("%d", &choice3);
                                printf("\n");
                                if (choice3 == 0) break;
                                switch (choice3) {
                                    case 1: {
                                        while (1) {
                                            printf("数独来源： 1.来自于文件  2.手动输入数独格局\n输入0返回上一级\n");
                                            printf("  请输入您的选择：");
                                            int choice4;
                                            scanf("%d", &choice4);
                                            printf("\n");
                                            if (choice4 == 0) break;
                                            switch (choice4) {
                                                case 1: {
                                                    printf("请输入文件路径：");
                                                    char sudoku_file_path[100];
                                                    scanf("%s", sudoku_file_path);
                                                    int count = sudoku_solve_from_file(sudoku_file_path);
                                                    if (count == -1) {
                                                        printf("文件打开失败！\n");
                                                        break;
                                                    }
                                                    else {
                                                        printf("成功求解数独个数：%d \n", count);
                                                        break;
                                                    }
                                                }
                                                case 2: {
                                                    printf("请输入待解决的数独，格式要求：81个符号按行优先排列，符号"".""表示待填空格，示例：.......9....23.6...3.7....5.....4........69........8...82..9....9.....2..1.......\n");
                                                    char sudoku_str[100];
                                                    scanf("%s", sudoku_str);
                                                    bool SAT = sudoku_solve_from_string(sudoku_str);
                                                    break;
                                                }
                                                default:
                                                    printf("请输入有效的选项！\n");
                                                    break;
                                            }
                                        }
                                        break;
                                    }
                                    case 2: {
                                        while (1) {
                                            printf("请选择难度： 1.简单  2.中等  3.困难\n 输入0返回上一级\n");
                                            printf("请输入您的选择：");
                                            int choice5;
                                            scanf("%d", &choice5);
                                            printf("\n");
                                            if (choice5 == 0) break;
                                            switch (choice5) {
                                                case 1:
                                                case 2:
                                                case 3: {
                                                    char random_sudoku[82];
                                                    generate_random_sudoku(choice5, random_sudoku);
                                                    for (int i = 0; i < 9; i++) printf("%.9s\n", random_sudoku + i * 9);
                                                    printf("查看答案请输入1，退出请输入0：");
                                                    int choice6;
                                                    scanf("%d", &choice6);
                                                    printf("\n");
                                                    if (choice6 == 1) {
                                                        sudoku_solve_from_string(random_sudoku);
                                                        break;
                                                    }
                                                    else break;
                                                }
                                                default: {
                                                    printf("请输入有效的选项！\n");
                                                    break;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    default:
                                        printf("请输入有效的选项！\n");
                                        break;
                                }
                            }
                            break;
                        }
                        case 2: {
                            while (1) {
                                printf("操作选择： 1.解决百分号数独  2.随机生成一个百分号数独\n输入0重新选择数独种类\n");
                                printf("请输入您的选择：");
                                int choice7;
                                scanf("%d", &choice7);
                                printf("\n");
                                if (choice7 == 0) break;
                                switch (choice7) {
                                    case 1: {
                                        while (1) {
                                            printf("数独来源： 1.来自于文件  2.手动输入百分号数独格局\n输入0返回上一级\n");
                                            printf("请输入您的选择：");
                                            int choice8;
                                            scanf("%d", &choice8);
                                            printf("\n");
                                            if (choice8 == 0) break;
                                            switch (choice8) {
                                            case 1: {
                                                printf("请输入文件路径：");
                                                char xsudoku_file_path[100];
                                                scanf("%s", xsudoku_file_path);
                                                int count = xsudoku_solve_from_file(xsudoku_file_path);
                                                if (count == -1) {
                                                    printf("文件打开失败！\n");
                                                    break;
                                                }
                                                else {
                                                    printf("成功求解百分号数独个数：%d \n", count);
                                                    break;
                                                }
                                            }
                                            case 2: {
                                                printf("请输入待解决的百分号数独，格式要求：81个符号按行优先排列，符号"".""表示待填空格，示例：.......9....23.6...3.7....5.....4........69........8...82..9....9.....2..1.......\n");
                                                char xsudoku_str[100];
                                                scanf("%s", xsudoku_str);
                                                bool SAT = xsudoku_solve_from_string(xsudoku_str);
                                                break;
                                            }
                                            default:
                                                printf("请输入有效的选项！\n");
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    case 2: {
                                        while (1) {
                                            printf("请选择难度： 1.简单  2.中等  3.困难\n 输入0返回上一级\n");
                                            printf("请输入您的选择：");
                                            int choice9;
                                            scanf("%d", &choice9);
                                            printf("\n");
                                            if (choice9 == 0) break;
                                            switch (choice9) {
                                                case 1:
                                                case 2:
                                                case 3: {
                                                    char random_xsudoku[82];
                                                    generate_random_xsudoku(choice9, random_xsudoku);
                                                    for (int i = 0; i < 9; i++) printf("%.9s\n", random_xsudoku + i * 9);
                                                    printf("查看答案请输入1，退出请输入0：");
                                                    int choice10;
                                                    scanf("%d", &choice10);
                                                    printf("\n");
                                                    if (choice10 == 1) {
                                                        xsudoku_solve_from_string(random_xsudoku);
                                                        break;
                                                    }
                                                    else break;
                                                }
                                                default: {
                                                    printf("请输入有效的选项！\n");
                                                    break;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    default:
                                        printf("请输入有效的选项！\n");
                                        break;
                                }
                            }
                            break;
                        }
                        default:
                            printf("请输入有效的选项！\n");
                            break;
                    }
                }
                break;
            }
            default:
                printf("请输入有效的选项！\n");
                break;
        }
    }
    return 0;
}