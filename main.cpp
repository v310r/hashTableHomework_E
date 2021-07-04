#include <iostream>
#include <list>
#include <utility>
#include <vector>

template<int size>
class HashTable{
private:
// A vector that has lists in which each name has corresponding phone number and address
    std::vector<std::list<std::pair<std::string,std::pair<std::string,std::string> > > > hash;
    
    //getting indexes using formula -->  index = sum_of_ASCII_integers_numbers mod(arraySize)
    int hashing(const std::string& name){
        int indexSum{};
        for(int letter = 0; letter < name.size();++letter){
            // converting chars to ints using ASCII table 
            indexSum = static_cast<int>(name[letter]);
        }
        int arrayIndex = indexSum % hash.size();
        return arrayIndex;
    } 
public:

    HashTable():hash(size) {

    }

    void add(const std::string& name,const std::string& phone,const std::string& address){
        hash[hashing(name)].push_back(std::make_pair(name,std::make_pair(phone,address)));
    }

    //get_phone number
    using list_iter = std::list<std::pair<std::string,std::pair<std::string,std::string> > >;
    std::string operator[](const std::string& name){
        auto currentList = hash[hashing(name)];
        list_iter::iterator iter = currentList.begin();
        while(iter!= currentList.end()){
            if(iter->first == name){
                return iter->second.first;
            }
            iter++;
        }
        return "No such person exists";
    }

};

int main(){
    HashTable<10> hash;
    hash.add("Mia","+380678303012","Kyiv, Yakubovskogo");
    hash.add("Sue","+380675096599","Kyiv, Yakubovskogo");
    std::cout<<hash["Mia"]<<"  "<<hash["Sue"]<<"\n\n";

}