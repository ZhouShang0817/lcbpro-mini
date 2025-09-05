import sys

read = sys.stdin.readline

TC = int(read())

def query_sum(a: list[list], x1: int, y1: int, x2: int, y2: int) -> int:
    return a[x2][y2] + a[x1 - 1][y1 - 1] - a[x1 - 1][y2] - a[x2][y1 - 1]

for _ in range(TC):
    m, q = (int(x) for x in read().split())

    matrix = []; res = []

    for _ in range(m):
        matrix.append([int(x) for x in read().split()])
    
    matrix_1 = [[0] * (m + 1) for _ in range(m + 1)]
    matrix_2 = [[0] * (m + 1) for _ in range(m + 1)]
    matrix_3 = [[0] * (m + 1) for _ in range(m + 1)]

    for i in range(1, m + 1):
        for j in range(1, m + 1):
            matrix_3[i][j] = matrix[i - 1][j - 1]
            matrix_1[i][j] = matrix[i - 1][j - 1] * j
            matrix_2[i][j] = matrix[i - 1][j - 1] * i
            
    
    for i in range(1, m + 1):
        for j in range(1, m + 1):
            matrix_2[j][i] += matrix_2[j][i - 1]
            matrix_1[j][i] += matrix_1[j][i - 1]
            matrix_3[j][i] += matrix_3[j][i - 1]

    for i in range(1, m + 1):
        for j in range(1, m + 1):
            matrix_2[i][j] += matrix_2[i - 1][j]
            matrix_1[i][j] += matrix_1[i - 1][j]
            matrix_3[i][j] += matrix_3[i - 1][j]
    
    
    for _ in range(q):
        (a, b, x, y) = (int(x) for x in input().split())
        res.append(query_sum(matrix_1, a, b, x, y) - (b - 1) * query_sum(matrix_3, a, b, x, y)
                   + (y - b + 1) * (query_sum(matrix_2, a, b, x, y) - a * (query_sum(matrix_3, a, b, x, y))))

    print(' '.join(str(x) for x in res))
        
        

