def binaryTreeSort(l):
    assert(type(l)==type(['']))
    length = len(l)
    if length==0 or length==1:
        return l
    class Node:
        def __init__(self,value=None,left=None,right=None):
            self.__value = value
            self.__left = left
            self.__right = right
        @property
        def value(self):
            return self.__value
        @property
        def left(self):
            return self.__left
        @property
        def right(self):
            return self.__right

    class BinaryTree:
        def __init__(self,root=None):
            self.__root = root
            self.__ret=[]
        
        @property
        def result(self):
            return self.__ret
        def add(self,parent,node):
            if parent.value>node.value:
                if not parent.left:
                    parent.left = node
                else:
                    self.add(parent.left,node)
                pass
            else:
                if not parent.right:
                    parent.right = node
                else:
                    self.add(parent.right,node)
        
        def Add(self,node):
            if not self.__root:
                self.__root = node
            else:
                self.add(self.__root, node)
        
        def show(self,node):
            if not node:
                return
            if node.right:
                self.show(node.right)
            self.__ret.append(node.value)
            if node.left:
                self.show(node.left)
                
        def Show(self):
            self.show(self.__root)
                
    b = BinaryTree()
    for i in l:
        b.Add(Node(i))
    b.Show()
    return b.result



list = [8,3,5,2,1,6,7,0]

def main():
    print binaryTreeSort(list)

if __name__ == '__main__':
    main()