#include <bits/stdc++.h>

using namespace std;
typedef int type;
static const int maxLen = 3000;

int len;
type seg[4 * maxLen];
type arr[maxLen];

int leftChild(int parent){
    return (2 * parent) + 1;
}
int rightChild(int parent){
    return (2 * parent) + 2;
}
int parent(int child){
    return (child - 1) / 2;
}


/**
 * Identity element is 0 for summation, INT_MIN for maximization, INT_MAX for minimization etc 
 * 
 * 
 */
type identityElement = 0;
type calculateParent(type child1, type child2){
    return (child1 + child2);
}

void getInput(){

    cin >> len;

    if(len > maxLen){
        throw std::invalid_argument( "Maximum length exceeded!!" );
    }

    for(int i = 0; i < len; i++)
        cin >> arr[i];

}

void build(int node, int l, int r){

    if(l == r){
        seg[node] = arr[l];
        return;
    }

    build(leftChild(node), l, (l + r) / 2);
    build(rightChild(node), 1 + ((l + r) / 2), r);

    seg[node] = calculateParent(seg[leftChild(node)], seg[rightChild(node)]);
}

void init(){
    build(0, 0, len-1);
}


type find(int node, int findLeft, int findRight, int mostLeft, int mostRight){

    if(findRight < mostLeft || findLeft > mostRight)
        return identityElement;

    
    if(findRight >= mostRight && findLeft <= mostLeft)
        return seg[node];

    return calculateParent(find(leftChild(node), findLeft, findRight, mostLeft, (mostLeft + mostRight) / 2 ),
                        find(rightChild(node), findLeft, findRight, 1 + ( (mostLeft + mostRight) / 2 ), mostRight ) );


}

type query(int findLeft, int findRight ){

    if(findLeft > findRight)
        return identityElement;

    return find(0, findLeft, findRight, 0, len-1);
}



void update(int node, int index, type newValue, int mostLeft, int mostRight){
    if(index < mostLeft || index > mostRight)
        return;

    if(mostLeft == mostRight){
        arr[index] = newValue;
        seg[node] = newValue;
        return;
    }

    update(leftChild(node), index, newValue, mostLeft,  (mostLeft + mostRight) / 2);
    update(rightChild(node), index, newValue, 1 + ((mostLeft + mostRight) / 2), mostRight);

    seg[node] = calculateParent(seg[leftChild(node)], seg[rightChild(node)]);
}

/**
 * @brief 0 <= index < len
 * 
 * @param index 
 * @param newValue 
 */
void update(int index, type newValue){
    update(0, index, newValue, 0, len - 1);
}


int main() {
    getInput();
    init();


	return 0;
}

