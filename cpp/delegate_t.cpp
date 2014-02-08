class RealPrinter { // the "delegate"
public:
     void print() {
        //do something
     }
 };

class Printer {      // the "delegator"
public:
     Printer(): p(new RealPrinter()){} // create the delegate
     void print() {
       p->print(); // delegation
     }
     ~Printer(){
       if(NULL != p){
          delete p;
          p = NULL;
       }
     }
private:
     RealPrinter *p;
 };

int main()
{
    Printer *p = new Printer;
    p->print();  //client don’t know the exists of delegate class
    delete p;
}


class PrinterDelegate{
public:
    virtual ~PrinterDelegate(){} // why virtual function , see Effective c++ Item 7.
    virtual void print() = 0;
};

class RealPrinter : public PrinterDelegate { // the "delegate"
public:
    void print() {
        //do something ZHANG
    }
};

class Printer{
public:
    Printer():delegate(new RealPrinter){}
    void print(){
        if (NULL != delegate) {
            delegate->print();
        }
    }
    ~Printer(){
       if(NULL != delegate){
          delete delegate;
          delegate = NULL;
       }
     }
private:
    PrinterDelegate *delegate;
};

int main()
{
    Printer *p = new Printer;
    p->print();  //client don’t know the exists of delegate class
    delete p;
}