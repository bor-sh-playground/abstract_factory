#include <ros/ros.h>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class NodeInterface
{
public:
    NodeInterface(){}
    ~NodeInterface(){}

    template<class M>
    void func(M &p) {
        cout << "Number " << endl;
        p.test();
    }
};

class NodeObj
{
public:
    void test() {
        cout << "Hello";
    }
};

class Base
{
public:
    Base() {}
    virtual ~Base() { }

    virtual void run() = 0;

    typedef Base * (*create_fp)();

    static Base * instantiate(std::string const & name)
    {
        std::map<std::string, Base::create_fp>::const_iterator it = registry().find(name);
        return it == registry().end() ? NULL : (it->second)();
    }

protected:
    static Base * create();

    static void registrate(std::string const & name, create_fp fp)
    {
        registry()[name] = fp;
    }

    template <typename D>
    class Registrar
    {
    public:
        explicit Registrar(std::string const & name)
        {
            Base::registrate(name, &D::create);
        }

        virtual ~Registrar() {}
        // make non-copyable, etc.
    };

private:
    static std::map<std::string, create_fp> & registry();
};

std::map<std::string, Base::create_fp> & Base::registry()
{
    static std::map<std::string, Base::create_fp> impl;
    return impl;
}

class Derived : Base
{
public:
    Derived() : Base() {
        Base::Registrar<Derived> registrar("start");
    }
    virtual ~Derived() {}

    static Base * create() { return new Derived; }
    // ...

    virtual void run() {
        cout << "here running " << endl;
    }
};

class CmdStop : Base
{
public:
    CmdStop() : Base() {
        Base::Registrar<CmdStop> registrar("stop");
    }
    virtual ~CmdStop() {}

    static Base * create() { return new CmdStop; }

    virtual void run() {
        cout << "here stopping " << endl;
    }
};

class Commands
{
public:
    Commands(){}
    ~Commands(){}

    void run(int argc, char* argv[]) {
        cout << "running " << argv[1] << endl;
        Base * p = Base::instantiate(argv[1]);

        if (p != NULL)
        {
            p->run();
        }
        else
        {
            cout << "Ohoh NULL pointer" << endl;
        }
    }
};

class MemoryLeak
{
public:
    MemoryLeak()
    {
        obj_ = new NodeObj;
    }

    virtual ~MemoryLeak()
    {
        delete obj_;
    }

private:
    NodeObj *obj_;
};

class base1
{

public:
    base1(){cout<<"Base Constructor Called\n";}
    virtual ~base1(){cout<<"Base Destructor called\n";}

};
class derived1:public base1
{

public:
    derived1(){cout<<"Derived constructor called\n";}
    virtual ~derived1(){cout<<"Derived destructor called\n";}

};

int main(int argc, char* argv[])
{
//    ros::init(argc, argv, "testtest");

//    NodeInterface ni;

//    NodeObj obj;

//    ni.func(obj);
/*
    int i = 10;

    ni.func(i);

    double d = 10;
    ni.func(d)*/;

//    MemoryLeak *memtest = new MemoryLeak;
//    delete memtest;


//    Commands cmd;

//    cmd.run(argc, argv);

    base1* b;
    b=new derived1;
    delete b;

    return 0;
}
