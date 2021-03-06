//
// Created by kalee on 06/10/2020.
//

#include <string>
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;


enum class Relationship{
    parent,
    child,
    sibling
};

struct Person{
    string name;
};

struct RelationshipBrowser
{
    virtual vector<Person> find_all_children_of(const string& name)=0;
};

struct Relationships : RelationshipBrowser{ //low level construct
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_child (const Person &parent, const Person &child){
        relations.push_back(make_tuple(parent, Relationship::parent,child));
        relations.push_back(make_tuple(child,Relationship::child,parent));
    }

    vector<Person> find_all_children_of(const string &name) override
    {
        vector<Person> result;
        for (auto&& [first,rel,second] : relations)
        {
            if(first.name == name && rel == Relationship::parent)
            {
                result.push_back(second);
            }
        }
        return result;
    }
};

struct Research //high level
{
    Research(RelationshipBrowser& browser)
    {
        for (auto& child:browser.find_all_children_of("parent"))
        {
            cout << "John's child is "<< child.name << endl;
        }
    }
//    Research(Relationships& relationships){
//        auto& relations = relationships.relations;
//        for (auto&& [first, rel, second]:relations)
//        {
//         if (first.name == "parent" && rel == Relationship::parent)
//         {
//             cout << "John's child is " << second.name << endl;
//         }
//        }
//    }
};

int main(){
    Person parent{"parent"};
    Person child1{"child1"},child2{"child2"};
    Relationships relationships;
    relationships.add_parent_child(parent,child1);
    relationships.add_parent_child(parent,child2);
    Research _(relationships);



    return 0;
}