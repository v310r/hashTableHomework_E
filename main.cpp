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
            indexSum += static_cast<int>(name[letter]);
        }
        int arrayIndex = indexSum % hash.size();
        return arrayIndex;
    } 
public:
    using list = std::list<std::pair<std::string,std::pair<std::string,std::string> > >;

    HashTable():hash(size) {

    }

    void add(const std::string& name,const std::string& phone,const std::string& address){
        hash[hashing(name)].push_back(std::make_pair(name,std::make_pair(phone,address)));
    }

    void remove(const std::string& name){
        int index = hashing(name);
        auto& currentList = hash[index];
        list::iterator iter = currentList.begin();
        while(iter!= currentList.end()){
            if(iter->first == name){
                currentList.erase(iter);
                return;
            }
            iter++;
        }
        std::cout<<"No such person exists";
    }

    std::string get_name(const std::string& phone){
        for(int index = 0; index < hash.size();++index){
            auto currentList = hash[index];
            list::iterator iter = currentList.begin();
            while(iter!= currentList.end()){
                if(iter->second.first == phone){
                    return "name: " + iter->first;
                }
            iter++;
            }
        }
        return "No such person exists";
    }

    //get_phone number + address
    std::string operator[](const std::string& name){
        auto currentList = hash[hashing(name)];
        list::iterator iter = currentList.begin();
        while(iter!= currentList.end()){
            if(iter->first == name){
                return "phone number " + iter->second.first + "  address: " + iter->second.second;
            }
            iter++;
        }
        return "No such person exists";
    }

};

int main(){
    HashTable<11> hash;
    hash.add("Mia","+380678303012","Kyiv, Yakubovskogo");
    hash.add("Sue","+380675096599","Kyiv, Yakubovskogo");
    std::cout<<hash["Mia"]<<"\n"<<hash["Sue"]<<"\n"<<hash["Unknown"]<<"\n\n";
    hash.remove("Sue");
    std::cout<<hash["Mia"]<<"\n"<<hash["Sue"]<<"\n\n";
    hash.remove("Unknown");
    std::cout<<"\n\n";
    std::cout<<hash.get_name("+380678303012")<<"\n";
    std::cout<<hash.get_name("45435642423")<<"\n\n";

}