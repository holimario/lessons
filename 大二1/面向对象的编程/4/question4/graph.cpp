#include "graph.h"
#include "other.h"
#include "node.h"

using namespace std;

Graph::Graph(int num_node) {
    // 预分配节点空间
    nodes_.initialize(num_node);
}

void Graph::InsertPlaceholder(const string &node_name) {
    PlaceholderNode* p=new PlaceholderNode(node_name);
    nodes_.insert(node_name,p);
    // wait to fill, 使用nodes_.insert()新建一个占位符
}

void Graph::InsertConstant(const string &node_name, float value) {
    ConstantNode* p=new ConstantNode(node_name,value);
    nodes_.insert(node_name,p);
    // wait to fill, 使用nodes_.insert()新建一个常量
}

void Graph::InsertOperation(const string &node_name, const string &operation_type, 
                                const string &input1, const string &input2) {
    if(operation_type=="+")
    {
        Other* p=new Other(node_name,nodes_[input1],nodes_[input2],1);
        nodes_.insert(node_name,p);
    }
    else
    {
        Other* p=new Other(node_name,nodes_[input1],nodes_[input2],0);
        nodes_.insert(node_name,p);
    }
    // wait to fill, 根据operation_type的名字调用相应的运算符节点构造函数
}

void Graph::Eval(const string &node_name, const int &argument_num, 
                    const string* argument_name_list_, const float* argument_value_list_) {

    for(int i=0;i<=argument_num-1;i++)
    {
        PlaceholderNode* p=dynamic_cast<PlaceholderNode*>(nodes_[argument_name_list_[i]]);
        p->set_val(argument_value_list_[i]);
    }
    // wait to fill, 调用相应的placeholder的set_val函数


    nodes_[node_name]->calc();
    float temp_value = nodes_[node_name]->value();
    cout << std::fixed << setprecision(2) << temp_value << endl;   
}

Graph::~Graph() {
    
}


