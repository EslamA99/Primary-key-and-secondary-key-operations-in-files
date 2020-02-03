#include <iostream>
#include <bits/stdc++.h>

using namespace std;


string int_to_string(short x)
{
    string y="";
    stringstream converter;
    converter<<x;
    y+=converter.str();
    return y;
}
int string_to_int(string x)
{
    short y=atoi(x.c_str());
    return y;
}


class SimpleIndex
{
    int next;
    int headerSize;
    struct course
    {
        char ID[6];
        string Name;
        string instructor_name;
        short weeks;
    };
    struct IndexRecord
    {
        char PK[6];
        int offset;
    };
    struct secondindex
    {
        char PK[6];
        string ins_name;
    };
    const static int indexSize = 100;
    IndexRecord index[indexSize];
    secondindex second[indexSize];
public:
    SimpleIndex();
    void sortprimIndex();
    int primIndexBinarySearch(char key[]);
    int secIndexBinarySearch_id(char key[]);
    void sortsecondIndex();
    int secondIndexBinarySearch(string key);
    void ChangeIndexState_prim(bool state);
    void ChangeIndexState_sec(bool state);
    void insertcourse();
    void saveprimIndex();
    void loadprimIndex();
    void ReconstructIndex_prim();
    bool getIndexState_prim();
    bool getIndexState_sec();
    void printcourse_prim();
    void deletecourse_prim();
    void updatecourse_prim();
    void saveSecondindex();
    void deletecourse_sec();
    void printcourse_sec();
    void ReconstructIndex_sec();
    void loadSecondindex();
    bool check_for_repetition_sec(string namee);
    void updatecourse_sec();
    void sortsecIndex_id();
};

SimpleIndex::SimpleIndex()
{
    next=0;
    headerSize=1;
}

bool SimpleIndex::check_for_repetition_sec(string namee)
{
    int count1=0;
    for(int i=0; i<next; i++)
        if (second[i].ins_name==namee)count1++;
    if(count1==1)return false;
    else return true;
}

int SimpleIndex::secIndexBinarySearch_id(char key[])
{
    int size = next;
    int low = 0, high = size - 1;
    while (low <= high)
    {
        int middle = (low + high) / 2;
        if (strcmp(second[middle].PK, key) == 0)
            return middle;
        else if (atoi(second[middle].PK)<atoi(key))
            low = middle + 1;
        else
            high = middle - 1;
    }
    return -1;
}


void SimpleIndex::sortprimIndex() //selection sort
{
    int len = next -1;
    IndexRecord temp;
    for (int i = 0; i<len; i++)
        for (int j = 0; j<len - i; j++)
        {
            if (atoi(index[j].PK)>atoi(index[j + 1].PK))
            {
                temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    cout<<"\nprimary index after sort:\n";

    for (int i = 0; i<next; i++)cout<<index[i].PK<<"    "<<index[i].offset<<endl;

}

int SimpleIndex::primIndexBinarySearch(char key[])
{
    int size = next;
    int low = 0, high = size - 1;
    while (low <= high)
    {
        int middle = (low + high) / 2;
        if (strcmp(index[middle].PK, key) == 0)
            return middle;
        else if (atoi(index[middle].PK)<atoi(key))
            low = middle + 1;
        else
            high = middle - 1;
    }
    return -1;
}

void SimpleIndex::sortsecIndex_id() //selection sort
{
    int len = next -1;
    secondindex temp;
    for (int i = 0; i<len; i++)
        for (int j = 0; j<len - i; j++)
        {
            if (atoi(second[j].PK)>atoi(second[j + 1].PK))
            {
                temp = second[j];
                second[j] = second[j + 1];
                second[j + 1] = temp;
            }
        }
    cout<<"\nsecond index after sort:\n";

    for (int i = 0; i<next; i++)cout<<second[i].PK<<"    "<<second[i].ins_name<<endl;

}


void SimpleIndex::sortsecondIndex() //selection sort
{
    int len = next -1;
    secondindex temp;
    for (int i = 0; i<len; i++)
        for (int j = 0; j<len - i; j++)
        {
            if (second[j].ins_name>second[j + 1].ins_name)
            {
                temp = second[j];
                second[j] = second[j + 1];
                second[j + 1] = temp;
            }
        }
    cout<<"\nSecond index after sort:\n";
    for (int i = 0; i<next; i++)cout<<second[i].ins_name<<"   "<<second[i].PK<<endl;

}

int SimpleIndex::secondIndexBinarySearch(string key)
{
    int size = next;
    int low = 0, high = size - 1;
    while (low <= high)
    {
        int middle = (low + high) / 2;
        if (second[middle].ins_name== key)
            return middle;
        else if (second[middle].ins_name<key)
            low = middle + 1;
        else
            high = middle - 1;
    }
    return -1;
}

void SimpleIndex:: ReconstructIndex_prim()
{
    fstream f("t.txt",ios::out|ios::in);
    f.seekg(0,ios::beg);
    next=0;
    while(true)
    {
        if (f.peek() == EOF)
        {
            f.clear();
            break;
        }
        int cont=0;
        index[next].offset=f.tellg();
        string length="";
        char x;
        f>>x;
        length+=x;
        f>>x;
        if(x!='|')
            length+=x;
        else
        {
            f.seekg(0,ios::beg);
            f>>x;
        }
//        char len[2];
//        cout<<"ffffff"<<len<<endl;
//        f.read(len,2);
        if(length[0]=='*')
        {
            while(cont!=5)
            {
                char x;
                f>>x;
                if(x=='|')cont++;
            }
            continue;
        }
        int len_=string_to_int(length);
        char buff[len_];
        f.read(buff,len_);
        string str="";
        for(int i=1; i<7; i++)
        {
            if(buff[i]=='|')break;
            str+=buff[i];
        }
        strcpy(index[next].PK,str.c_str());
        next++;
    }
    sortprimIndex();
}

void SimpleIndex::ChangeIndexState_prim(bool state)
{
    fstream p("p.txt",ios::out|ios::in);
    p.seekp(0,ios::beg);
    short st=state;
    p<<st;
    p.close();
}
void SimpleIndex::ChangeIndexState_sec(bool state)
{
    fstream s("sec.txt",ios::out|ios::in);
    s.seekp(0,ios::beg);
    short st=state;
    s<<st;
    s.close();
}

void SimpleIndex::saveprimIndex()
{
    fstream p("p.txt",ios::out| ios::in|ios::trunc);
    short state=0;
    p<<state;
    for (int i = 0; i<next; i++)
    {
        p.write((char*)&index[i], sizeof(index[i]));
    }
    p.close();
}

bool SimpleIndex::getIndexState_prim()
{
    fstream p("p.txt",ios::out|ios::in);
    p.seekg(0,ios::beg);
    short state=0;
    p>>state;
    p.close();
    if(state==1)return true;
    if(state==0)return false;

}

bool SimpleIndex::getIndexState_sec()
{
    fstream s("sec.txt",ios::out|ios::in);
    s.seekg(0,ios::beg);
    short state=0;
    s>>state;
    s.close();
    if(state==1)return true;
    if(state==0)return false;

}

void SimpleIndex::loadprimIndex()
{
    if(!getIndexState_prim())
    {
        fstream p("p.txt",ios::in|ios::out);
        short state=0;
        p>>state;
        next=0;
        while(true)
        {
            if(p.peek()==EOF)
            {
                p.clear();
                break;
            }
            p.read((char*)&index[next],sizeof(index[next]));
            next++;
        }
    }
    else ReconstructIndex_prim();
}

void SimpleIndex:: insertcourse()
{
    fstream f("t.txt",ios::out|ios::in|ios::app);
    ChangeIndexState_prim(true);
    ChangeIndexState_sec(true);

    course record;
    cout<<"Enter ID: ";
    cin>>record.ID;
    cout<<"Enter Name: ";
    cin>>record.Name;
    cout<<"Enter instructor name: ";
    cin>>record.instructor_name;
    cout<<"Enter num of weeks: ";
    cin>>record.weeks;

    f.seekp(0,ios::end);
    int offset= f.tellp();

    string buffer="";
    buffer+="|";
    buffer+=record.ID;
    buffer+="|";
    buffer+=record.Name;
    buffer+="|";
    buffer+=record.instructor_name;
    buffer+="|";
    buffer+=int_to_string(record.weeks);
    buffer+="|";

    f<<buffer.length();
    f.write(&buffer[0],buffer.length());

    strcpy(index[next].PK,record.ID);
    index[next].offset=offset;

    second[next].ins_name=record.instructor_name;
    strcpy(second[next].PK,record.ID);

    next++;
    sortsecondIndex();
    sortprimIndex();
    f.close();
}

void SimpleIndex::printcourse_sec()
{
    fstream f("t.txt",ios::in|ios::out);
    cout<<"Enter instructor name: ";
    string insname;
    cin>>insname;
    sortsecondIndex();
    int add=secondIndexBinarySearch(insname);
    if(add==-1)cout<<"name not found"<<endl;
    else
    {
        for(int j=0; j<next; j++)
        {
            if(second[j].ins_name==insname)
            {
                int q=primIndexBinarySearch(second[j].PK);
                f.seekg(index[q].offset,ios::beg);
                short len=0;

                string length="";
                char x;
                f>>x;
                length+=x;
                f>>x;
                if(x!='|')
                    length+=x;
                else
                {
                    f.seekg(index[q].offset,ios::beg);
                    f>>x;
                }

                len=string_to_int(length);
                char buffer[len];
                f.read(buffer,len);
                string temp="";
                int countt=1;
                for(int i=1; i<len; i++)
                {
                    if(buffer[i]=='|'&&countt==1)
                    {
                        cout<<"\nID: "<<temp;
                        countt++;
                        temp="";
                        continue;
                    }
                    if(buffer[i]=='|'&&countt==2)
                    {
                        cout<<"\nName: "<<temp;
                        countt++;
                        temp="";
                        continue;
                    }
                    if(buffer[i]=='|'&&countt==3)
                    {
                        cout<<"\ninstructor name: "<<temp;
                        countt++;
                        temp="";
                        continue;
                    }
                    if(buffer[i]=='|'&&countt==4)
                    {
                        cout<<"\nnum of weeks: "<<temp<<endl;
                        countt++;
                        temp="";
                        countt=1;
                        continue;
                    }
                    temp+=buffer[i];

                }
            }
        }
    }

}

void SimpleIndex::printcourse_prim()
{
    fstream f("t.txt",ios::in|ios::binary);
    char pk[6];
    cout<<"Enter the ID: ";
    cin>>pk;
    int address=primIndexBinarySearch(pk);
    if(address==-1)cout<<"ID not found"<<endl;
    else
    {
        f.seekg(index[address].offset,ios::beg);
        short len=0;
        string length="";
        char x;
        f>>x;
        length+=x;
        f>>x;
        if(x!='|')
            length+=x;
        else
        {
            f.seekg(index[address].offset,ios::beg);
            f>>x;
        }

        len=string_to_int(length);
        char buffer[len];
        f.read(buffer,len);

        string temp="";
        int countt=1;
        for(int i=1; i<len; i++)
        {
            if(buffer[i]=='|'&&countt==1)
            {
                cout<<"\nID: "<<temp;
                countt++;
                temp="";
                continue;
            }
            if(buffer[i]=='|'&&countt==2)
            {
                cout<<"\nName: "<<temp;
                countt++;
                temp="";
                continue;
            }
            if(buffer[i]=='|'&&countt==3)
            {
                cout<<"\ninstructor name: "<<temp;
                countt++;
                temp="";
                continue;
            }
            if(buffer[i]=='|'&&countt==4)
            {
                cout<<"\nnum of weeks: "<<temp<<endl;
                countt++;
                temp="";
                continue;
            }
            temp+=buffer[i];

        }
    }
}

void SimpleIndex::deletecourse_sec()
{
    ChangeIndexState_sec(1);
    ChangeIndexState_prim(1);

    fstream f("t.txt",ios::in|ios::out);
    cout<<"Enter ur deleted course instructor name: ";
    string nam,h,str,m;
    cin>>nam;
    bool checkforprim=false;
    for(int i=0; i<next; i++)
    {
        if(second[i].ins_name==nam)//put * in datafile
        {
            int position=primIndexBinarySearch(second[i].PK);
            f.seekp(index[position].offset);
            char x='*';
            f.write((char*)&x,1);
            checkforprim=true;
        }
        if(checkforprim)
        {
            int p=primIndexBinarySearch(second[i].PK);
            for(int k=p; k<next; k++)
                index[k]=index[k+1];

            for(int j=i; j<next; j++)
                second[j]=second[j+1];
            next--;
            i--;
            checkforprim=false;
        }
    }
    /*fstream s("sec.txt",ios::in|ios::out);
    short state=0;
    s>>state;
    while(true)
    {
        if(s.peek()==EOF)
        {
            s.clear();
            break;
        }
        getline(s,str,'|');
        if(str==nam)
        {
            m="-1";
            s.write(&m[0],2);
        }
        else
            getline(s,h,'|');
    }*/
}

void SimpleIndex::deletecourse_prim()
{
    ChangeIndexState_sec(1);
    ChangeIndexState_prim(1);
    fstream f("t.txt",ios::in|ios::out);
    char id[6];
    cout<<"Enter Id U Want to delete: ";
    cin>>id;
    int pos=primIndexBinarySearch(id);
    if(pos==-1)
        cout<<"Not found!"<<endl;
    else
    {
        f.seekp(index[pos].offset);
        char x='*';
        f.write((char*)&x,1);
        sortsecIndex_id();
        int pos2=secIndexBinarySearch_id(id);
        //sortsecondIndex();
        for (int i = pos; i<next - 1; i++)
            index[i] = index[i + 1];

        for (int i = pos2; i<next - 1; i++)
            second[i] = second[i + 1];

        next--;
        sortprimIndex();
        sortsecondIndex();
    }
}

void SimpleIndex::updatecourse_sec()
{
    ChangeIndexState_sec(1);
    ChangeIndexState_prim(1);
    fstream f("t.txt",ios::in|ios::out);
    string naame;
    cout<<"Enter instructor name U Want to Update: ";
    cin>>naame;
    int n=secondIndexBinarySearch(naame);
    if(n==-1)cout<<"Name not found\n";
    else
    {
        if(check_for_repetition_sec(naame))
        {
            char idd[6];
            cout<<"there are more than one record with the same name please enter id of ur record to update: ";
            cin>>idd;
            int m=primIndexBinarySearch(idd);
            if(n==-1)cout<<"ID not found\n";
            else
            {
                course record;
                cout<<"Enter ID: ";
                cin>>record.ID;
                cout<<"Enter Name: ";
                cin>>record.Name;
                cout<<"Enter instructor name: ";
                cin>>record.instructor_name;
                cout<<"Enter num of weeks: ";
                cin>>record.weeks;
                string buffer="";
                buffer+="|";
                buffer+=record.ID;
                buffer+="|";
                buffer+=record.Name;
                buffer+="|";
                buffer+=record.instructor_name;
                buffer+="|";
                buffer+=int_to_string(record.weeks);
                buffer+="|";
                sortsecIndex_id();
                int position=secIndexBinarySearch_id(idd);
                //position++;
                int pos=primIndexBinarySearch(idd);
                //sortsecondIndex();
                f.seekg(index[pos].offset);

                string length="";
                char x;
                f>>x;
                length+=x;
                f>>x;
                if(x!='|')
                    length+=x;
                else
                {
                    f.seekg(index[pos].offset);
                    f>>x;
                }
                short lenn=0;
                lenn=string_to_int(length);
                if(lenn==buffer.length())
                {
                    f.seekp(index[pos].offset);
                    f<<buffer.length();
                    f.write(&buffer[0],buffer.length());
                    strcpy(index[pos].PK,record.ID);
                    strcpy(second[position].PK,record.ID);

                    second[position].ins_name=record.instructor_name;
                    sortprimIndex();
                    sortsecondIndex();
                }
                else
                {
                    f.seekp(index[pos].offset);
                    char x='*';
                    f.write((char*)&x,1);
                    f.seekp(0,ios::end);
                    int ofs=f.tellp();

                    f<<buffer.length();
                    f.write(&buffer[0],buffer.length());

                    strcpy(index[pos].PK,record.ID);
                    index[pos].offset=ofs;

                    strcpy(second[position].PK,record.ID);
                    second[position].ins_name=record.instructor_name;

                    sortprimIndex();
                    sortsecondIndex();
                }
            }

        }
        else
        {
            course record;
            cout<<"Enter ID: ";
            cin>>record.ID;
            cout<<"Enter Name: ";
            cin>>record.Name;
            cout<<"Enter instructor name: ";
            cin>>record.instructor_name;
            cout<<"Enter num of weeks: ";
            cin>>record.weeks;
            string buffer="";
            buffer+="|";
            buffer+=record.ID;
            buffer+="|";
            buffer+=record.Name;
            buffer+="|";
            buffer+=record.instructor_name;
            buffer+="|";
            buffer+=int_to_string(record.weeks);
            buffer+="|";
            int position=secondIndexBinarySearch(naame);
            int pos=primIndexBinarySearch(second[position].PK);
            f.seekg(index[pos].offset);
            string length="";
            char x;
            f>>x;
            length+=x;
            f>>x;
            if(x!='|')
                length+=x;
            else
            {
                f.seekg(index[pos].offset);
                f>>x;
            }
            short lenn=0;
            lenn=string_to_int(length);
            if(lenn==buffer.length())
            {
                f.seekp(index[pos].offset);
                f<<buffer.length();
                f.write(&buffer[0],buffer.length());
                strcpy(index[pos].PK,record.ID);

                strcpy(second[position].PK,record.ID);
                second[position].ins_name=record.instructor_name;
                sortprimIndex();
                sortsecondIndex();
            }
            else
            {
                f.seekp(index[pos].offset);
                char x='*';
                f.write((char*)&x,1);
                f.seekp(0,ios::end);
                int ofs=f.tellp();

                f<<buffer.length();
                f.write(&buffer[0],buffer.length());

                strcpy(index[pos].PK,record.ID);
                index[pos].offset=ofs;

                strcpy(second[position].PK,record.ID);
                second[position].ins_name=record.instructor_name;

                sortprimIndex();
                sortsecondIndex();
            }
        }
    }
}

void SimpleIndex::updatecourse_prim()
{
    ChangeIndexState_sec(1);
    ChangeIndexState_prim(1);
    fstream f("t.txt",ios::in|ios::out|ios::binary);
    char id[6];
    cout<<"Enter Id U Want to Update: ";
    cin>>id;
    int pos=primIndexBinarySearch(id);
    if(pos==-1)
        cout<<"Not found!"<<endl;
    else
    {
        course record;
        cout<<"Enter ID: ";
        cin>>record.ID;
        cout<<"Enter Name: ";
        cin>>record.Name;
        cout<<"Enter instructor name: ";
        cin>>record.instructor_name;
        cout<<"Enter num of weeks: ";
        cin>>record.weeks;
        string buffer="";
        buffer+="|";
        buffer+=record.ID;
        buffer+="|";
        buffer+=record.Name;
        buffer+="|";
        buffer+=record.instructor_name;
        buffer+="|";
        buffer+=int_to_string(record.weeks);
        buffer+="|";
        f.seekg(index[pos].offset);
        string length="";
        char x;
        f>>x;
        length+=x;
        f>>x;
        if(x!='|')
            length+=x;
        else
        {
            f.seekg(index[pos].offset);
            f>>x;
        }
        short lenn=0;
        lenn=string_to_int(length);
        if(lenn==buffer.length())
        {
            f.seekp(index[pos].offset);
            f<<buffer.length();
            f.write(&buffer[0],buffer.length());
            strcpy(index[pos].PK,record.ID);
            sortsecIndex_id();
            int position=secIndexBinarySearch_id(id);
            strcpy(second[position].PK,record.ID);
            second[position].ins_name=record.instructor_name;
            sortprimIndex();
            sortsecondIndex();
        }
        else
        {
            f.seekp(index[pos].offset);
            char x='*';
            f.write((char*)&x,1);
            f.seekp(0,ios::end);
            int ofs=f.tellp();

            f<<buffer.length();
            f.write(&buffer[0],buffer.length());

            strcpy(index[pos].PK,record.ID);
            index[pos].offset=ofs;
            sortsecIndex_id();
            int position=secIndexBinarySearch_id(id);
            strcpy(second[position].PK,record.ID);
            second[position].ins_name=record.instructor_name;

            sortprimIndex();
            sortsecondIndex();
        }

    }

}

void SimpleIndex::saveSecondindex()
{
    fstream s("sec.txt",ios::in|ios::out|ios::trunc);
    fstream t("linked.txt",ios::in|ios::out|ios::trunc);
    char x='|';
    short state=0;
    s<<state;
    int i=0,j=0,o=-1,cont=0;
    string str="",m="",h="";
    bool repeated=false;

    for( i=0; i<next; i++)
    {
        for( j=(i-1); j>=0; j--)
        {
            if(second[i].ins_name==second[j].ins_name)
            {
                repeated=true;
                break;
            }
        }
        if(repeated)
        {
            string pkk="";
            pkk+=second[i].PK;
            //cout<<"pkk= "<<pkk<<endl;
            t.write(&pkk[0],pkk.length());
            t.write((char*)&x,1);
            t<<o;
            t.write((char*)&x,1);
            t.seekg(0,ios::beg);
            while(true)
            {
                if(t.peek()==EOF)
                {
                    t.clear();
                    break;
                }
                getline(t,str,'|');
                if(cont==j)

                {
                    m=int_to_string(i);
                    t.write(&m[0],2);
                }
                else
                    getline(t,h,'|');
                cont++;
            }
            cont=0;
            repeated=false;
        }
        else
        {
            string pkk="";
            pkk+=second[i].PK;
            //cout<<"pkk= "<<pkk<<endl;
            t.write(&pkk[0],pkk.length());
            t.write((char*)&x,1);
            t<<o;
            t.write((char*)&x,1);
            s.seekp(0,ios::end);
            s.write(&second[i].ins_name[0],second[i].ins_name.length());
            s.write((char*)&x,1);
            s<<i;
            s.write((char*)&x,1);

        }
    }

    // read
    /*t.seekg(0,ios::beg);
    string styyyyyy="",st="";
    while(true)
    {
        if(t.peek()==EOF)
        {
            t.clear();
            break;
        }
        getline(t,styyyyyy,'|');
        cout<<styyyyyy<<"  ";
        getline(t,st,'|');
        cout<<st<<endl;
    }*/
}

void SimpleIndex::ReconstructIndex_sec()
{
    fstream f("t.txt",ios::in|ios::out);
    next=0;
    while(true)
    {
        if(f.peek()==EOF)
        {
            f.clear();
            break;
        }

        int len=0,conter=0;
        string length="";
        char x;
        f>>x;
        length+=x;
        f>>x;
        if(x!='|')
            length+=x;
        else
        {
            f.seekg(0,ios::beg);
            f>>x;
        }
        if(length[0]=='*')
        {
            while(conter!=5)
            {
                char x;
                f>>x;
                if(x=='|')conter++;
            }
            continue;
        }
        len=string_to_int(length);
        string buffer="";
        f.read(&buffer[0],len);
        string pk="",instruc_name="";
        int cont=0;
        for(int i=1; i<len; i++)
        {
            if(buffer[i]=='|')
            {
                cont++;
                continue;
            }
            if(cont==0)pk+=buffer[i];
            if(cont==2)instruc_name+=buffer[i];
        }
        second[next].ins_name=instruc_name;
        strcpy(second[next].PK,pk.c_str());
        next++;
    }
    sortsecondIndex();
}

void SimpleIndex:: loadSecondindex()
{
    if(!getIndexState_sec())
    {
        fstream s("sec.txt",ios::in|ios::out);
        fstream t("linked.txt",ios::in|ios::out);
        short state=0;
        s>>state;
        next=0;
        while(true)
        {
            if(s.peek()==EOF)
            {
                s.clear();
                break;
            }
            string str="",num="";
            getline(s,str,'|');
            getline(s,num,'|');
            //cout<<"first= "<<str<<"  "<<num<<endl;
            int coont=0,number1=string_to_int(num);
            t.seekg(0,ios::beg);
            while(true)
            {
                if(t.peek()==EOF)
                {
                    t.clear();
                    break;
                }
                string str2="",num2="";
                while(coont==number1)
                {
                    getline(t,str2,'|');
                    second[next].ins_name=str;
                    strcpy(second[next].PK,str2.c_str());
                    next++;
                    getline(t,num2,'|');
                    number1=string_to_int(num2);
                    if(number1==-1)break;
                    coont++;
                }
                getline(t,str2,'|');
                getline(t,num2,'|');
                coont++;
            }
        }
        sortsecondIndex();
        //for(int i=0;i<next;i++)cout<<second[i].ins_name<<"   "<<second[i].PK<<endl;
    }
    else ReconstructIndex_sec();

}

int main()
{
    SimpleIndex r;
    while (true)
    {
        cout<<"1-Add course\n2-print course by id\n3-print course by name\n4-delete course by id\n5-delete course by name\n6-update course by id\n7-update course by name\n8-load data from file to indexes\n9-Save and exit\n";
        int choice=0;
        cin>>choice;
        if(choice==1)r.insertcourse();
        if(choice==2)r.printcourse_prim();
        if(choice==3)r.printcourse_sec();
        if(choice==4)r.deletecourse_prim();
        if(choice==5)r.deletecourse_sec();
        if(choice==6)r.updatecourse_prim();
        if(choice==7)r.updatecourse_sec();
        if(choice==8)
        {
            r.loadSecondindex();
            r.loadprimIndex();
        }
        if(choice==9)
        {
            r.saveprimIndex();
            cout<<"prim saved\n";
            r.saveSecondindex();
            cout<<"second saved\n";
            break;
        }
        cout<<endl;
    }
    return 0;
}
