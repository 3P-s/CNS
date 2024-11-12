def chineseRemTheorem(a, m):
    mm = 1
    for mi in m:
        mm *= mi
    M_i = [mm // mi for mi in m]
    y_i = [modInverse(M_i[i], m[i]) for i in range(len(m))]
    x = 0
    for i in range(len(a)):
        x += a[i] * M_i[i] * y_i[i]
    return x % mm, mm

def modInverse(a, m):
    m0 = m
    y = 0
    x = 1
    if m == 1:
        return 0
    while a > 1:
        q = a // m
        t = m
        m = a % m
        a = t
        t = y
        y = x - q * y
        x = t
    if x < 0:
        x += m0
    return x


print(chineseRemTheorem([2, 3, 2], [3, 5, 7])) 