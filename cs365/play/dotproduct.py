m1 = [[3,6,8,10],[4,1,2,8]]
m2 = [[4,8,10],[3,5,7],[2,6,8],[4,1,5]]

# should equal 103

def dotproduct(m1, m2, i, j):
    column = map(lambda row: row[j], m2)
    products = map(lambda v1, v2: v1*v2, m1[i], column)
    return reduce(lambda v1, v2: v1+v2, products)

print dotproduct(m1, m2, 1, 2)
