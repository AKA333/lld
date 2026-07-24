#include <bits/stdc++.h>

using namespace std;

class fileSystem {
    public:
    virtual ~fileSystem() = default;
    virtual string getName() = 0;
    virtual int getSize() = 0;
    virtual void ls() = 0;
    virtual bool isFolder() = 0;
    virtual void openAll() = 0;
}; 

class file : public fileSystem {
    string name;
    int size;
public:
    file(string _name, int _size) : name(_name), size(_size) {}

    string getName(){
        return name;
    }

    int getSize(){
        return size;
    }

    void ls(){
        cout<<name<<"\n";
    }
    void openAll(){
        cout<<name<<"\n";
    }

    bool isFolder(){
        return false;
    }
};

class folder : public fileSystem {
    string name;
    vector<fileSystem*> children;
public:
    folder(string _name){
        name = _name;
    }
    ~folder(){
        for(auto child: children){
            delete child;
        }
    }
    void add(fileSystem* file){
        children.push_back(file);
    }
    string getName(){
        return name;
    }
    int getSize(){
        int size=0;
        for(auto child: children){
            size += child->getSize();
        }
        return size;
    }
    bool isFolder() { return true; }

    void ls(){
        for(auto child : children){
            cout<<child->getName()<<"\n";
        }
    }

    void openAll(){
        cout<<"+ "<<name<<"\n";
        for(auto child : children){
            child->openAll();
        }
    }
};

int main(){
    folder* root = new folder("root");

    folder* docs = new folder("docs");
    file* resume = new file("resume", 2);
    file* cover_letter = new file("cover letter", 4);

    docs->add(resume);
    docs->add(cover_letter);

    root->add(docs);

    cout<<"root ls\n";
    root->ls();

    cout<<"root size\n";
    cout<<root->getSize()<<"\n";

    cout<<"docs size\n";
    cout<<docs->getSize()<<"\n";

    cout<<"docs ls\n";
    docs->ls();


    cout<<"root openall\n";
    root->openAll();
    cout<<"docs openall\n";
    docs->openAll();
}

// Output:
// root ls
// + root
// + docs
// resume
// cover letter
// root size
// 6
// docs size
// 6
// docs ls
// + docs
// resume
// cover letter
// root openall
// + root
// + docs
// resume
// cover letter
// docs openall
// + docs
// resume
// cover letter
