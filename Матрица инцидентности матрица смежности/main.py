import numpy as np

def print_matrix(matrix):
    for i in matrix:
        row = '('
        for j in i:
            if j != -1: row += ' '
            row += str(j)
        print(row+' )')
    print()

def is_symmetrical(matrix:np.ndarray):
    for i in range(matrix.shape[0]):
        for j in range(i+1):
            if abs(matrix[i,j]) != abs(matrix[j,i]):
                return False
    return True

def generate_incidence_matrix(adjacency_matrix):
    if not is_symmetrical(adjacency_matrix): return None

    lines = 0
    for i in range(adjacency_matrix.shape[0]):
        for j in range(i + 1):
            if adjacency_matrix[i,j] != 0:
                lines += 1

    incidence_matrix = np.zeros([lines, adjacency_matrix.shape[1]], dtype=int)
    counter = 0

    for i in range(adjacency_matrix.shape[0]):
        for j in range(i + 1):
            if adjacency_matrix[i,j] != 0:
                incidence_matrix[counter, i] = adjacency_matrix[i, j]
                incidence_matrix[counter, j] = -adjacency_matrix[i, j]
                counter += 1

    return incidence_matrix

def generate_adjacency_matrix(incidence_matrix:np.ndarray):
    adjacency_matrix = np.zeros([incidence_matrix.shape[1], incidence_matrix.shape[1]], dtype=int)

    for i in incidence_matrix:
        flag = True
        row = -1
        column = -1
        for j, j_c in zip(i, range(incidence_matrix.shape[1])):
            if flag and j != 0:
                row = j_c
                flag = False
            elif not flag and j != 0:
                column = j_c

        if row != -1 and column != -1:
            adjacency_matrix[row, column] = 1
            adjacency_matrix[column, row] = -1
        elif row != -1: adjacency_matrix[row, row] = 1

    return adjacency_matrix

adjacency_matrix = np.array(
    [(1 ,1 ,0 ,0 ,1 ),
     (-1,0 ,-1,0 ,1 ),
     (0 ,1 ,0 ,-1,0 ),
     (0 ,0 ,1 ,0 ,1 ),
     (-1,-1,0 ,1 ,0 )]
)
print('Матрица смежности:')
print_matrix(adjacency_matrix)

print('Матрица инцидентности, полученная из матрицы смежности:')
incidence_matrix = generate_incidence_matrix(adjacency_matrix)
print_matrix(incidence_matrix)

print('Матрица смежности, полученная из матрицы инцидентности:')
adjacency_matrix_new = generate_adjacency_matrix(incidence_matrix)
print_matrix(adjacency_matrix_new)