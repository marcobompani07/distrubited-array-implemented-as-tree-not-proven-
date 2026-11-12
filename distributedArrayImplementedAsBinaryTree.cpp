#include <iostream>
using namespace std;
struct treeElement{
    int index;
    int value;
    int tcount=0;
    treeElement *r1=nullptr;
    treeElement *r2=nullptr;
};
void fromSingleChainToDouble(treeElement& root);
void balanceCount(treeElement& root);
treeElement* add(treeElement* root, int v);
int get(treeElement *root, int index);
void set(treeElement *root, int index,int v);
void reduceSize(treeElement *root);
treeElement *getTree(treeElement *root,int index);
int main(){
    int n1=10000000,n2=5000000;
    bool correct;
    //do{
        treeElement* root=nullptr;
        treeElement* root2=nullptr;
        for(int i=0;i<n1;i++){
            root=add(root,i);
            root2=add(root2,i);
        }
        for(int i=0;i<n2;i++){
            reduceSize(root);
        }
        for(int i=n1-n2;i<n1;i++){
            root=add(root,i);
        }
        /*for(int i=0;i<40;i++){
            root=add(root,i);
            root2=add(root2,i);
        }
        reduceSize(root);
        root=add(root,5000);*/
        //cout<<"allocated";
        correct=true;
        /*for(int i=0;i<n100;i++){
            if(get(root,i)!=i){
                correct=false;
            }
        }*/
        for(int i=0;i<n1;i++){
            treeElement* t1=getTree(root,i);
            treeElement* t2=getTree(root2,i);
            if(t1->r1!=nullptr&&t1->r2!=nullptr&&t2->r1!=nullptr&&t2->r2!=nullptr&&(t1->r1->index!=t2->r1->index||t1->r2->index!=t2->r2->index)){
                correct=false;
            }
        }
        n2++;
        if(n1==n2){
            n2=1;
            n1++;
            cout<<n1<<endl;
        }
    //set(root,30,-40);
    //}while (correct);
    //cout<<"n1:"<<n1<<" n2:"<<n2;
    cout<<correct;
    //cout<<correct;//<<" "<<get(root,30);
    return 0;
}
treeElement* add(treeElement *root, int v){
    if(root==nullptr){
        root=new treeElement;
        root->index=0;
        root->tcount=0;
        root->value=v;
    }else{
        treeElement *croot=new treeElement;
        croot->r1=root;
        croot->r2=nullptr;
        croot->index=root->index+1;
        croot->tcount=root->tcount+1;
        croot->value=v;
        root=croot;
        balanceCount(*root);
        fromSingleChainToDouble(*root);
    }
    return root;
}
int get(treeElement *root, int index){
    if(index<=root->index){
        treeElement *croot=root;
        while(index!=croot->index){
            if(index>croot->r1->index){
                croot=croot->r2;
            }else{
                croot=croot->r1;
            }
        }
        return croot->value;
    }
    return-1;
}
void set(treeElement *root, int index,int v){
    if(index<=root->index){
        treeElement *croot=root;
        while(index!=croot->index){
            if(index>croot->r1->index){
                croot=croot->r2;
            }else{
                croot=croot->r1;
            }
        }
        croot->value=v;
    }
}
void reduceSize(treeElement *root){
    treeElement *croot=root;
    treeElement *previusCroot=nullptr;
    treeElement *previusX2Croot=nullptr;
    bool found=true;
    do{

        croot->index--;
        if(croot->r2!=nullptr&&croot->r2->index==croot->index){
            previusX2Croot=previusCroot;
            previusCroot=croot;
            croot->value=croot->r2->value;
            croot->tcount--;
            croot=croot->r2;
        }else if(croot->r1!=nullptr&&croot->r1->index==croot->index){
            previusX2Croot=previusCroot;
            previusCroot=croot;
            croot->value=croot->r1->value;
            croot->tcount--;
            croot=croot->r1;
        }else{
            if(previusCroot!=nullptr){
                if(previusCroot->r2==croot){
                    previusCroot->r2=nullptr;
                }else{
                    previusCroot->r1=nullptr;
                }
                delete croot;
            }else{
                croot->index++;
            }
            //non elimina mai l'untimo elemento
            found=false;
            balanceCount(*root);
            fromSingleChainToDouble(*root);
            if(root->r2!=nullptr){
                treeElement *c=root->r2;
                while(c->r1!=nullptr&&c->r2!=nullptr){
                    fromSingleChainToDouble(*c);
                    balanceCount(*c);
                    c=c->r2;
                };
                balanceCount(*c);
                fromSingleChainToDouble(*c);
            }
            
        }
    }while(found);
}
treeElement *getTree(treeElement *root,int index){
    if(index<=root->index){
        treeElement *croot=root;
        while(index!=croot->index){
            if(index>croot->r1->index){
                croot=croot->r2;
            }else{
                croot=croot->r1;
            }
        }
        return croot;
    }
    return nullptr;
}
void fromSingleChainToDouble(treeElement& root){
    if(root.r1!=nullptr&&root.r2==nullptr&&root.r1->r1!=nullptr&&root.r1->r2==nullptr){
        root.r2=root.r1;
        root.r1=root.r2->r1;
        root.r2->r1=nullptr;
        root.r2->tcount-=root.r1->tcount+1;
    }
}
void balanceCount(treeElement& root){
    if(root.r1!=nullptr&&root.r1->r1!=nullptr&&root.r1->r2!=nullptr&&root.r1->r2->tcount<root.r1->r1->tcount){
        root.r2=root.r1;
        root.r1= root.r2->r1;
        root.r2->r1=root.r2->r2;
        root.r2->r2=nullptr;
        root.r2->tcount-=root.r1->tcount+1;
        balanceCount(*root.r2);
        fromSingleChainToDouble(*root.r2);
    }
}