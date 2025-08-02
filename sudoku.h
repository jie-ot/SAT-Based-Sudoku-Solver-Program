#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"dpll_solver_v2.h"

#define SUDOKU_LENGTH 81
#define VAR_NUM 729
#define N 9

//��һ��81�ַ��İٷֺ�����ת����cnf��д��cnf_path���ɹ�����1�����򷵻�0
bool xsudoku_to_cnf(const char* xsudoku_str, const char* cnf_path);
//��һ��81�ַ�����ͨ����ת����cnf��д��cnf_path���ɹ�����1�����򷵻�0
bool sudoku_to_cnf(const char* xsudoku_str, const char* cnf_path);

//����dpll���cnf_path�µ�������var_countΪ�ܱ�Ԫ����model�����洢cnf��ʽ�Ľ�
bool xsudoku_solver(const char* cnf_path, int var_count, int* model);

//��model��1��var_count������ȡ�������Ľ⣬д��grid_res��
void xsudoku_model_to_grid(const int* model, int var_count, char* grid_res);

//���ַ���grid_res�д�ӡ����
void xsudoku_print(const char* grid_res);

//��һ���ַ���sudoku_str�����ͨ����
bool sudoku_solve_from_string(const char* sudoku_str);
//��һ���ַ���xsudoku_str���ٷֺ�����
bool xsudoku_solve_from_string(const char* xsudoku_str);

//���ı��ļ������ж�ȡ�����ͨ������������Ⲣ��ӡ�����سɹ����ĸ���
int sudoku_solve_from_file(const char* sudoku_file);
//���ı��ļ������ж�ȡ����ٷֺ�������������Ⲣ��ӡ�����سɹ����ĸ���
int xsudoku_solve_from_file(const char* xsudoku_file);

void generate_random_sudoku(int difficulty, char* sudoku_str);
void generate_random_xsudoku(int difficulty, char* xsudoku_str);

//�����������������grid[9][9]
bool generate_full_xsudoku(int grid[9][9]);

//��grid[9][9]������ڶ���ֻ����clues�����֣�����ʣ��������������0�����ʧ��
int xsudoku_dig_holes(int grid[9][9], int clues);

//����һ������Ϊ81���ַ���sudoku_str��cluesΪ����������������1��ʾ�ɹ������򷵻�0
bool xsudoku_generater(char* xsudoku_str, int clues);