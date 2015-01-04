def quickSortPython(l):
    assert(type(l)==type(['']))
    length = len(l)
    if length==0 or length==1:
        return l
    if len(l)<=1:
        return l
    left = [i for i in l[1:] if i>l[0]]
    right = [i for i in l[1:] if i<=l[0]]
    return quickSortPython(left) +[l[0],]+ quickSortPython(right)

def myPythonQS(l):
    assert(type(l) == type(['']))
    length = len(l)
    if length <= 1:
        return l
    left = [i for i in l if i > l[0]]
    right = [i for i in l if i < l[0]]
    return myPythonQS(left) + [l[0],] + myPythonQS(right)

def quickSort(l,s,e):
    assert(type(l)==type(['']))
    length = len(l)
    if length==0 or length==1:
        return l
    def partition(l,start,end):
        pivot = l[start]
        while start<end-1:
            while end>start and l[end]<pivot:
                end-=1
            l[start] = l[end]
            while end>start and l[start]>pivot:
                start+=1
            l[end] = l[start]
        l[start] = pivot
        return start
        pass
    #random pivot
    def random_partition(l,start,end):
        i = random.randint(start,end)
        temp = l[i]
        l[i] = l[start]
        l[start] = temp
        return partition(l,start,end)
    
    if s<e:
        m = partition (l,s,e)
        quickSort(l,s,m-1)
        quickSort(l,m+1,e)
    return l


list = [8,3,5,2,1,6,7,0]

def main():
    print quickSort(list, 0, len(list))

if __name__ == '__main__':
    main()