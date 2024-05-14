# from scipy.signal import savgol_filter
# import tensorflow as tf

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from IPython.display import display
from IPython import get_ipython
from pandas.plotting import autocorrelation_plot
from matplotlib import ticker
import math as mt
import random as rnd

path_to_data = 'C:/Users/fadas/run2_WM32_data.csv'
get_ipython().run_line_magic('matplotlib', 'qt')


def get_df(path: str):
    df = pd.read_csv(path, delimiter=';', encoding='utf-8')
    return df


# Чтение данных из файла
first_df = get_df(path_to_data)
first_df = first_df.T
for col in first_df.columns:
    first_df = first_df.loc[~first_df[col].isin(['--'])]
first_df = first_df.T
first_df = pd.concat([first_df.iloc[0:119, 200:400+1], first_df.iloc[0:119, 2:199+1]], axis=1)

def normal_df(df_col, t, num):
    # Разбивает содержимое ячейки на два списки "Время" и "Амплитуда" и собирает их в датафрейм
    k = 0
    obj_list = []
    Y_list = []
    X_list = []
    str1 = str(df_col.values[t])
    obj_list.append(str1)
    for el in obj_list:
        k += 1
        while (el):
            ind = el.find(',')
            string = el[0:ind]
            if (ind == -1):
                string = el
            str1 = string.partition(':')
            X_list.append(float(str1[0]))
            Y_list.append(float(str1[2]))
            if (ind != -1):
                el = el[ind + 1:]
            else:
                el = ""
    Z_list = [num for _ in range(len(X_list))]

    result_df = pd.DataFrame({'Time': X_list, 'Amplitude': Y_list, 'Number': Z_list})
    return result_df

def split_to_str(deffect_columns):

    return [defect.partition('_')[2] for defect in deffect_columns]

def draw_3d_row(fig, row, columns, deffect_columns):
    ax = fig.add_subplot(111, projection='3d')
    ax.set_xlabel('Время', fontsize=15)
    ax.set_ylabel('Номер датчика', fontsize=15)
    ax.set_zlabel('Амплитуда', fontsize=15)
    k = 0
    list_of_defect_col = split_to_str(deffect_columns)
    plt.title(str(row) + ' строка, дефекты на датчиках: \n' + str(list_of_defect_col[0])+'-'+str(list_of_defect_col[-1]), fontsize=20)

    for num in columns:
        df = normal_df(first_df[num], row, k)
        if (num in deffect_columns):
            ax.plot(df['Time'], df['Number'], df['Amplitude'], color='r')
        else:
            ax.plot(df['Time'], df['Number'], df['Amplitude'], color='b')
        k += 1
    plt.yticks(range(len(columns)), columns, size='small')
    fig.show()


def draw_ngraph(row_list, column_matrix, deffect_columnsmatrix):
    k = 0
    column_matrix_num = 0
    for row in row_list:
        fig = plt.figure(k)
        draw_3d_row(fig, row, column_matrix[column_matrix_num], deffect_columnsmatrix[column_matrix_num])
        if len(column_matrix) > 1:
            column_matrix_num += 1
        k += 1
    return k


columns = first_df.columns.tolist()
row_list = [24]
column_matrix = [columns[396:399] + columns[2:9]]
deffect_columnsmatrix = [columns[367:369]]


# draw_ngraph(row_list, column_matrix, deffect_columnsmatrix)

def draw_3d_col(fig, column, rows, deffect_rows):
    ax = fig.add_subplot(111, projection='3d')
    ax.set_xlabel('Время', fontsize=15)
    ax.set_ylabel('Номер строки', fontsize=15)
    ax.set_zlabel('Амплитуда', fontsize=15)
    k = 0
    plt.title('Датчик ' + str(column) + ' дефект на строке: ' + str(deffect_rows), fontsize=28)
    for i in range(0, len(rows)):
        df = normal_df(first_df[column], rows[i], k)
        p = rows[i]
        if (p in deffect_rows):
            ax.plot(df['Time'], df['Number'], df['Amplitude'], color='r')
        else:
            ax.plot(df['Time'], df['Number'], df['Amplitude'], color='b')
        k += 1
    plt.yticks(range(len(rows)), rows, size='small')
    fig.show()


def draw_ngraph_col(k, row_list, column_matrix, deffect_rowsmatrix):
    for col in column_matrix:
        fg = plt.figure(k)
        draw_3d_col(fg, col, row_list, deffect_rowsmatrix)
        k += 1


columns = first_df.columns.tolist()
row_list = [i for i in range(70, 81)]# (70, 81)области с дефектами
column_matrix = [columns[120:140]]#[180:200] области с дефектами [325:345] - предполагаемо
deffect_columnsmatrix = [columns[120:140]]#[180:200]области с дефектами [325:345] - предполагаемо
k = draw_ngraph(row_list, column_matrix, deffect_columnsmatrix)

# row_list = [84, 85, 86, 87, 88, 89, 90, 91]
# column_matrix = columns[2:6]
# deffect_rowsmatrix = [87]
# draw_ngraph_col(k, row_list, column_matrix, deffect_rowsmatrix)
