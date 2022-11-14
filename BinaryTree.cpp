unordered_map<int,int> BinaryTree::balanceFactors() {
    unordered_map<int, int> umap;
    Node* node = root;
    Node* child = root;
    int leftBf;
    int rightBf;
    bool checkedLeft = false;
    while (node =! nullptr) {
        leftBf = 0;
        rightBf = 0;
        /*traverse left*/
        child = node->leftChild;
        while (child != nullptr){
            if (child->leftChild && !checkedLeft){
                child = child->leftChild;
                leftBf ++;
                
            }
            else if (child->rightChild) {
                child = child->rightChild;
                leftBf ++;
                checkedLeft = false;
            }
            else {
                child = child->parent;
                checkedLeft = true;
                leftBf --;
            }
        }
        /*traverse right*/
        child = node->rightChild;

        umap[node->label] = ;
    }
    
    
}

int findHeight() {
maxH = 0;
        h = 0;
        /*traverse left*/
        vector<int> checkedEdge;
        if (node->leftChild) {
            child = node->leftChild;
            h++;
        }
        while (child != node){
        
            if (child->leftChild && !contains(checkedEdge, child->leftChild->label)){
                
                checkedEdge.insert(0, child->leftChild->label);
                child = child->leftChild;
                h++;
            }
            else if (child->rightChild) {
                child = child->rightChild;
                checkedEdge.insert(0, child->parent->rightChild.label);
                h++;
            }
            else{
                if (h > maxH){
                    maxH = h;
                }
                h--;
                child = child->parent;
                 
            }
        }
        leftBf = maxH;