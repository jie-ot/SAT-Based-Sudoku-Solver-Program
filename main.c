#define _CRT_SECURE_NO_WARNINGS
#include"cnfparser.h"
#include"display.h"
#include"dpll_solver_v1.h"
#include"dpll_solver_v2.h"
#include"sudoku.h"

int main()
{
    printf("-------------------------------------------\n");
    printf("********����һ��SAT�������������Ϸ********\n");
    printf("-------------------------------------------\n");
    while (1) {
        printf("\n");
        printf("1.���cnf�ļ�\n2.������Ϸ\n0.�˳�����\n");
        printf("����������ѡ��");
        int choice1;
        scanf("%d", &choice1);
        printf("\n");
        if (choice1 == 0) break;
        switch (choice1) {
            case 1: {
                printf("������cnf�ļ�·����·����β��Ҫ��˫���ţ�����");
                char cnf_file_path[512];
                scanf("%s", cnf_file_path);
                getchar();
                printf("\n");
                formula* F = parse_cnf(cnf_file_path);
                if (!F) {
                    fprintf(stderr, "����CNF�ļ�ʧ��\n");
                    break;
                }
                Assignment A;
                double time_ms, time_ms_optimized;
                bool SAT_optimized = solve_dpll_v2(F, &A, &time_ms_optimized);
                print_result(SAT_optimized, &A, F->var_num, time_ms_optimized);
                //��.cnf�ļ�����Ϊͬ����.res�ļ�
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
                if (time_ms == time_ms_optimized) printf("ʱ���Ż���Ϊ0\n");
                else printf("ʱ���Ż���Ϊ��[(t-t0)/t]*100%% = %.2f%%\n", (time_ms - time_ms_optimized) / time_ms * 100.00);
                free(A.values);
                free_formula(F);
                break;
            }
            case 2: {
                while (1) {
                    printf("�������ࣺ 1.��ͨ����  2.�ٷֺ�����\n����0�˳�������Ϸ\n");
                    printf("����������ѡ��");
                    int choice2;
                    scanf("%d", &choice2);
                    printf("\n");
                    if (choice2 == 0) break;
                    switch (choice2) {
                        case 1: {
                            while (1) {
                                printf("����ѡ�� 1.�������  2.�������һ������\n����0����ѡ����������\n");
                                printf("����������ѡ��");
                                int choice3;
                                scanf("%d", &choice3);
                                printf("\n");
                                if (choice3 == 0) break;
                                switch (choice3) {
                                    case 1: {
                                        while (1) {
                                            printf("������Դ�� 1.�������ļ�  2.�ֶ������������\n����0������һ��\n");
                                            printf("  ����������ѡ��");
                                            int choice4;
                                            scanf("%d", &choice4);
                                            printf("\n");
                                            if (choice4 == 0) break;
                                            switch (choice4) {
                                                case 1: {
                                                    printf("�������ļ�·����");
                                                    char sudoku_file_path[100];
                                                    scanf("%s", sudoku_file_path);
                                                    int count = sudoku_solve_from_file(sudoku_file_path);
                                                    if (count == -1) {
                                                        printf("�ļ���ʧ�ܣ�\n");
                                                        break;
                                                    }
                                                    else {
                                                        printf("�ɹ��������������%d \n", count);
                                                        break;
                                                    }
                                                }
                                                case 2: {
                                                    printf("��������������������ʽҪ��81�����Ű����������У�����"".""��ʾ����ո�ʾ����.......9....23.6...3.7....5.....4........69........8...82..9....9.....2..1.......\n");
                                                    char sudoku_str[100];
                                                    scanf("%s", sudoku_str);
                                                    bool SAT = sudoku_solve_from_string(sudoku_str);
                                                    break;
                                                }
                                                default:
                                                    printf("��������Ч��ѡ�\n");
                                                    break;
                                            }
                                        }
                                        break;
                                    }
                                    case 2: {
                                        while (1) {
                                            printf("��ѡ���Ѷȣ� 1.��  2.�е�  3.����\n ����0������һ��\n");
                                            printf("����������ѡ��");
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
                                                    printf("�鿴��������1���˳�������0��");
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
                                                    printf("��������Ч��ѡ�\n");
                                                    break;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    default:
                                        printf("��������Ч��ѡ�\n");
                                        break;
                                }
                            }
                            break;
                        }
                        case 2: {
                            while (1) {
                                printf("����ѡ�� 1.����ٷֺ�����  2.�������һ���ٷֺ�����\n����0����ѡ����������\n");
                                printf("����������ѡ��");
                                int choice7;
                                scanf("%d", &choice7);
                                printf("\n");
                                if (choice7 == 0) break;
                                switch (choice7) {
                                    case 1: {
                                        while (1) {
                                            printf("������Դ�� 1.�������ļ�  2.�ֶ�����ٷֺ��������\n����0������һ��\n");
                                            printf("����������ѡ��");
                                            int choice8;
                                            scanf("%d", &choice8);
                                            printf("\n");
                                            if (choice8 == 0) break;
                                            switch (choice8) {
                                            case 1: {
                                                printf("�������ļ�·����");
                                                char xsudoku_file_path[100];
                                                scanf("%s", xsudoku_file_path);
                                                int count = xsudoku_solve_from_file(xsudoku_file_path);
                                                if (count == -1) {
                                                    printf("�ļ���ʧ�ܣ�\n");
                                                    break;
                                                }
                                                else {
                                                    printf("�ɹ����ٷֺ�����������%d \n", count);
                                                    break;
                                                }
                                            }
                                            case 2: {
                                                printf("�����������İٷֺ���������ʽҪ��81�����Ű����������У�����"".""��ʾ����ո�ʾ����.......9....23.6...3.7....5.....4........69........8...82..9....9.....2..1.......\n");
                                                char xsudoku_str[100];
                                                scanf("%s", xsudoku_str);
                                                bool SAT = xsudoku_solve_from_string(xsudoku_str);
                                                break;
                                            }
                                            default:
                                                printf("��������Ч��ѡ�\n");
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    case 2: {
                                        while (1) {
                                            printf("��ѡ���Ѷȣ� 1.��  2.�е�  3.����\n ����0������һ��\n");
                                            printf("����������ѡ��");
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
                                                    printf("�鿴��������1���˳�������0��");
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
                                                    printf("��������Ч��ѡ�\n");
                                                    break;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    default:
                                        printf("��������Ч��ѡ�\n");
                                        break;
                                }
                            }
                            break;
                        }
                        default:
                            printf("��������Ч��ѡ�\n");
                            break;
                    }
                }
                break;
            }
            default:
                printf("��������Ч��ѡ�\n");
                break;
        }
    }
    return 0;
}