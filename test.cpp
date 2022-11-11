#include <iostream>
#include <string>
#include <tuple>
#define get_iter(id, index) *(id.begin()+index)


using _One_Value = std::tuple<std::string, std::string, std::string,  int>;
using _Init_Trains = std::initializer_list<_One_Value>;

//g++ test.cpp; ./a.exe

char * t = (char*)"faf";
class TrainList  {
    private:
    struct TrainNode{
    TrainNode*next;
    _One_Value values;
    TrainNode(): next(NULL), values({" ", " ", " ", 0}){};
    TrainNode(TrainNode* next): next(next), values({" ", " ", " " , 0}){};
    TrainNode(TrainNode* next, _One_Value values): next(next), values(values){};

    };


    enum{
        TYPE,
        ID,
        DF,
        IS_FULL

    };

    public:
    TrainNode *head;
    
    TrainList(_Init_Trains Train_Initializer){
        head = new TrainNode(NULL, get_iter(Train_Initializer,0));
        TrainNode *ptr = head;
        for( int x = 1; x<Train_Initializer.size(); x++){
            ptr->next = new TrainNode(NULL, get_iter(Train_Initializer, x));
        }

    }; 
    void print_vals(){
        TrainNode *ptr = head;
        while(ptr != NULL){
            std::cout<<"id is "<<std::get<TYPE>(ptr->values);
            std::cout<<"name is "<<std::get<ID>(ptr->values);
            std::cout<<"duration/frequency is "<<std::get<DF>(ptr->values);
            std::cout<<"fuel is "<<std::get<IS_FULL>(ptr->values)<<std::endl;
            ptr = ptr->next;
        }
    }
    void push_back(_One_Value val){
        TrainNode *ptr = head;

        while(ptr->next !=NULL){
            ptr = ptr->next;
        }
        ptr->next = new TrainNode(NULL, val);
    }
    void honk(int index){
        TrainNode *ptr = head;
        for(int x =0; x<index;x++){
            ptr = ptr->next;
        }
        std::cout<<" honking with f"<<std::get<DF>(ptr->values)<<" -durration\n";
        return;
    }
};



int main(void){
    TrainList trains({{"hello ", "hello2", " 100/200 ", true}, {"fda", "fdsa"," 20/20 ", false}});

    char buff;
    char temp[10], temp2[10], temp3[10];


    _One_Value pushval;

    while(buff != 'q'){
        std::cout<<"q for quit\n";
        std::cout<<"h for honk\n";
        std::cout<<"i for insert\n";
        std::cout<<"p to print\n";
        buff = getc(stdin);
        if(buff == 'h'){
            std::cout<<"honk at index..\n";
            fgets(temp,10,stdin);
            trains.honk(atoi(temp));
        }
        if(buff == 'i'){
            fgets(temp,10,stdin);

            trains.push_back({(fgets(temp, 10, stdin) != NULL? temp : temp), (fgets(temp2, 10, stdin) != NULL? temp2 : temp), (fgets(temp3, 10, stdin) != NULL? temp3 : temp), bool(( getc(stdin) == '1') ? true : false)});

        }
        if (buff == 'p'){
            trains.print_vals();

        }
    }

};