// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
class Tree {
 private:
    struct Node {
        char val = ' ';
        bool fool = false;
        int cnum = 0;
        std::vector<Node*> leaf;
    };
    Node* root;
    int num = 0;

    void buildTree(Node* root, std::vector<char> inchar) {
        if (inchar.size() == 0)
            return;
        if (!root->fool) {
            for (auto i = inchar.begin(); i != inchar.end(); i++)
                if (*i == root->val) {
                    inchar.erase(i);
                    break;
                }
        }
        for (size_t i = 0; i < inchar.size(); i++)
            root->leaf.push_back(new Node());
        for (size_t i = 0; i < root->leaf.size(); i++)
            root->leaf[i]->val = inchar[i];
        for (size_t i = 0; i < root->leaf.size(); i++)
            buildTree(root->leaf[i], inchar);
        return;
    } 

    std::vector<std::string> changes;
    void per(Node* root, std::string ch = "") {
        if (root->leaf.size() == 0) {
            ch += root->value;
            changes.push_back(ch);
        }
        if (!root->fool) {
            ch += root->val;
            root->cnum += num;
            num += 1;
        }
        for (size_t i = 0; i < root->leaf.size(); i++)
            per(root->leaf[i], ch);
    }

 public:
    std::string operator[](int i) const {
        if (i >= changes.size())
            return "";
        return changes[i];
    }

    explicit Tree(std::vector<char> val) {
        root = new Node();
        root->fool = true;
        buildTree(root, val);
        per(root);
    }
};
#endif  // INCLUDE_TREE_H_
