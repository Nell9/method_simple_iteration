import numpy as np

m_size = 101

def diag(A):
    for i in range(m_size):
        A[i, i] = np.sum(np.abs(A[i, :])) + np.random.randint(1, 10)

def gaus(A):
    buff = np.zeros(m_size,dtype=float)
    buff2 = np.zeros(m_size,dtype=float)
    for col in range(m_size):
        flag = 1
        buff3 = A[col][col]
        for i in range(col,m_size):
            for j in range(m_size):
                if flag == 1:
                    A[col][j] = A[col][j]/ buff3
                    buff[j] = A[i][j]
                else:
                    for k in range(m_size):
                        buff2[k] = buff[j] * A[i][col]
                    A[i][j] = buff2[j] - A[i][j]
            flag=0
                    
 
def main():
    matrix_path = "D:\\The Science\\PGU\\abramov\\method_simple_iteration_kurs\\matrix.txt"
    vector_path = "D:\\The Science\\PGU\\abramov\\method_simple_iteration_kurs\\vector.txt"

    A = np.random.randint(1, 10,size = (m_size,m_size))
    A = A.astype("float")
    b = np.random.randint(250, 500, size=m_size)    
    print (A)
    gaus(A)
    
    #diag(A)
    print (A)
    with open(matrix_path, "w") as f:
        for i in range(m_size):
            #row = np.append(A[i], b[i])
            row = A[i]
            np.savetxt(f, [row], fmt="%.2f")
    f.close()

    with open(vector_path, "w") as f:
        np.savetxt(f, [b], fmt="%.2f")
    f.close()

main()
print("files .txt is create!")