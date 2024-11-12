def GCD(a,b):
    if b==0:
        return a
    else:
        return GCD(b,a%b)
    

def ExtendedEuclidean(a,b):
    if a==0:
        return b,0,1
    gcd,x1,y1 = ExtendedEuclidean(b%a,a)
    x = y1 - (b//a) * x1
    y = x1
    return gcd,x,y

if __name__ == "__main__":
    print(GCD(10,15))
    print(ExtendedEuclidean(10,15)[0])