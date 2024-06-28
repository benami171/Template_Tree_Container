#pragma once
#include <QApplication>
#include <QColor>
#include <QFont>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QMainWindow>
#include <QPen>
#include <QString>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <vector>

#include "node.hpp"

#define BINARY 2
#define LEFT_CHILD 0
#define RIGHT_CHILD 1

template <typename T, int K = BINARY>
class Tree {
   private:
    Node<T>* root;
    int max_children = K;

    // Helper method to find a node . given a tree and a value to look for.
    // Returns the node if found, nullptr otherwise.
    Node<T>* find_node(Node<T>* node, const T& value) {
        if (node == nullptr) return nullptr;
        if (node->value == value) return node;
        for (auto child : node->children) {
            Node<T>* found = find_node(child, value);
            if (found != nullptr) return found;
        }
        return nullptr;
    }

   public:
    explicit Tree() : root(nullptr) {}

    int get_max_children() const {
        return max_children;
    }

    void add_root(Node<T>* root) {
        this->root = root;
    }

    void add_sub_node(Node<T>* parent, Node<T>* child) {
        if (parent->get_children().size() >= (size_t)max_children) {
            throw std::runtime_error("Parent has reached its maximum number of children");
        }
        parent->add_child(child);
    }

    Node<T>* get_root() { return root; }

    class dfs_iterator {
       private:
        std::stack<Node<T>*> stk;

       public:
        dfs_iterator(Node<T>* root) {
            if (root) {
                stk.push(root);
            }
        }

        T& operator*() const {
            return stk.top()->get_value();
        }

        Node<T>* operator->() const {
            return stk.top();
        }

        dfs_iterator& operator++() {
            Node<T>* current = stk.top();
            stk.pop();
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                stk.push(*it);
            }
            return *this;
        }

        bool operator==(const dfs_iterator& other) const {
            if (stk.empty() && other.stk.empty()) return true;
            if (stk.empty() || other.stk.empty()) return false;
            return stk.top() == other.stk.top();
        }
        bool operator!=(const dfs_iterator& other) const {
            return !(*this == other);
        }
    };

    class in_order_iterator {
       private:
        Node<T>* current;
        std::stack<Node<T>*> stk;

        // void push_left(Node<T>* node) {
        //     while (node) {
        //         stk.push(node);
        //         if (!node->children.empty()) {
        //             node = node->children[LEFT_CHILD];
        //         } else {
        //             node = nullptr;
        //         }
        //     }
        // }
        void push_left(Node<T>* node) {
            while (node) {
                stk.push(node);
                if (!node->children.empty()) {
                    node = node->children[LEFT_CHILD];
                } else {
                    node = nullptr;
                }
            }
        }

       public:
        // in_order_iterator(Node<T>* root) {
        //     Node<T>* node = root;
        //     while (node) {
        //         stk.push(node);
        //         if (!node->children.empty()) {
        //             node = node->children[LEFT_CHILD];
        //         } else {
        //             node = nullptr;
        //         }
        //     }
        //     if (!stk.empty()) {
        //         current = stk.top();
        //         stk.pop();
        //     }
        // }
        in_order_iterator(Node<T>* root) {
            push_left(root);
            if (!stk.empty()) {
                current = stk.top();
                stk.pop();
            } else {
                current = nullptr;
            }
        }

        T& operator*() const {
            return current->get_value();
        }

        Node<T>* operator->() const {
            return current;
        }

        in_order_iterator& operator++() {
            if (!current->children.empty() && current->children.size() > 1) {
                Node<T>* node = current->children[RIGHT_CHILD];
                while (node) {
                    stk.push(node);
                    if (!node->children.empty()) {
                        node = node->children[LEFT_CHILD];
                    } else {
                        node = nullptr;
                    }
                }
            }
            if (!stk.empty()) {
                current = stk.top();
                stk.pop();
            } else {
                current = nullptr;
            }
            return *this;
        }
        bool operator==(const in_order_iterator& other) const {
            return current == other.current;
        }
        bool operator!=(const in_order_iterator& other) const {
            return current != other.current;
        }
    };

    //   pre order for BINARY tree
    class pre_order_iterator {
       private:
        std::stack<Node<T>*> nodes_stack;

       public:
        pre_order_iterator(Node<T>* root) {
            nodes_stack.emplace(nullptr);  // For the end, because we use top()
            if (root != nullptr) {
                nodes_stack.emplace(root);
            }
        }

        Node<T>* operator*() const {
            return nodes_stack.top()->get_value();
        }

        Node<T>* operator->() const {
            return nodes_stack.top();
        }

        pre_order_iterator& operator++() {
            Node<T>* current = nodes_stack.top();
            nodes_stack.pop();

            if (current->children.size() > 1) {
                if (current->children[1] != nullptr) {
                    nodes_stack.emplace(current->children[1]);
                }
            }
            if (current->children.size() > 0) {
                if (current->children[0] != nullptr) {
                    nodes_stack.emplace(current->children[0]);
                }
            }

            return *this;
        }

        bool operator==(const pre_order_iterator& other) const {
            if (nodes_stack.empty() && other.nodes_stack.empty()) {
                return true;
            }
            if (nodes_stack.empty() || other.nodes_stack.empty()) {
                return false;
            }
            return nodes_stack.top() == other.nodes_stack.top();
        }

        bool operator!=(const pre_order_iterator& other) const {
            return !(*this == other);
        }
    };

    // POST ORDER FOR BINARY TREE
    class post_order_iterator {
       private:
        Node<T>* current;
        std::stack<Node<T>*> stk;
        std::unordered_set<Node<T>*> visited;

        void push_children(Node<T>* node) {
            if (node) {
                stk.push(node);
                for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                    if (*it) stk.push(*it);
                }
            }
        }

       public:
        post_order_iterator(Node<T>* root) {
            push_children(root);
            advance();
        }

        void advance() {
            while (!stk.empty()) {
                Node<T>* node = stk.top();
                if (node == nullptr) {
                    stk.pop();
                    if (!stk.empty()) {
                        current = stk.top();
                        stk.pop();
                    }
                    return;
                }
                if (visited.find(node) == visited.end()) {
                    stk.push(nullptr);
                    push_children(node);
                    visited.insert(node);
                } else {
                    stk.pop();
                }
            }
            current = nullptr;
        }

        T& operator*() const {
            return current->get_value();
        }

        Node<T>* operator->() const {
            return current;
        }

        post_order_iterator& operator++() {
            advance();
            return *this;
        }

        bool operator!=(const post_order_iterator& other) const {
            return current != other.current;
        }
    };

    class bfs_iterator {
       private:
        Node<T>* current;
        std::deque<Node<T>*> queue;

       public:
        bfs_iterator(Node<T>* root) {
            if (root) {
                queue.push_back(root);
            }
            advance();
        }

        void advance() {
            if (queue.empty()) {
                current = nullptr;
                return;
            }
            current = queue.front();
            queue.pop_front();
            for (auto child : current->children) {
                queue.push_back(child);
            }
        }

        T& operator*() const {
            return current->get_value();
        }

        Node<T>* operator->() const {
            return current;
        }

        bfs_iterator& operator++() {
            advance();
            return *this;
        }

        bool operator!=(const bfs_iterator& other) const {
            return current != other.current;
        }
    };

    class min_heap_iterator {
       private:
        Node<T>* current;
        std::queue<Node<T>*> nodesQueue;

       public:
        // Constructor
        min_heap_iterator(Node<T>* root) {
            if (root != nullptr) {
                nodesQueue.push(root);
                current = root;  // Initialize current to root
            }
        }

        T& operator*() {
            return current->get_value();
        }

        Node<T>* operator->() {
            return current;
        }

        // Move to the next element
        min_heap_iterator& operator++() {
            if (!nodesQueue.empty()) {
                nodesQueue.pop();  // Pop the current node
                for (auto child : current->children) {
                    if (child != nullptr) nodesQueue.push(child);
                }
                current = !nodesQueue.empty() ? nodesQueue.front() : nullptr;  // Update current to the next node
            }
            return *this;
        }

        // Check for inequality
        bool operator!=(const min_heap_iterator& other) const {
            return current != other.current;
        }
    };

    using iterator_type = typename std::conditional<K == BINARY, pre_order_iterator, dfs_iterator>::type;
    using iterator_type2 = typename std::conditional<K == BINARY, post_order_iterator, dfs_iterator>::type;
    using iterator_type3 = typename std::conditional<K == BINARY, in_order_iterator, dfs_iterator>::type;
    using iterator_type4 = typename std::conditional<K == BINARY, min_heap_iterator, dfs_iterator>::type;

    iterator_type begin_pre_order() {
        return iterator_type(this->root);
    }

    iterator_type end_pre_order() {
        return iterator_type(nullptr);
    }

    iterator_type2 begin_post_order() {
        return iterator_type2(this->root);
    }

    iterator_type2 end_post_order() {
        return iterator_type2(nullptr);
    }

    iterator_type3 begin_in_order() {
        return iterator_type3(this->root);
    }

    iterator_type3 end_in_order() {
        return iterator_type3(nullptr);
    }

    dfs_iterator begin_dfs_scan() {
        return dfs_iterator(this->root);
    }

    dfs_iterator end_dfs_scan() {
        return dfs_iterator(nullptr);
    }

    bfs_iterator begin_bfs_scan() {
        return bfs_iterator(this->root);
    }

    bfs_iterator end_bfs_scan() {
        return bfs_iterator(nullptr);
    }

    bfs_iterator begin() {  // Default iterator
        return begin_bfs_scan();
    }

    bfs_iterator end() {  // Default iterator
        return end_bfs_scan();
    }

    iterator_type4 begin_min_heap() {
        return iterator_type4(this->root);
    }

    iterator_type4 end_min_heap() {
        return iterator_type4(nullptr);
    }

    std::pair<iterator_type4, iterator_type4> myHeap() {
        return std::make_pair(begin_min_heap(), end_min_heap());
    }
};

template <typename T>
void drawTree(QGraphicsScene* scene, Node<T>* node, int x, int y, int offset) {
    if (!node) return;
    const int ellipseRadius = 30;     // Increased radius for better ratio
    QPen nodePen(QColor(139, 0, 0));  // Dark red color
    nodePen.setWidth(2);              // Thicker outline
    scene->addEllipse(x - ellipseRadius, y - ellipseRadius, 2 * ellipseRadius, 2 * ellipseRadius, nodePen);

    QString nodeText = QString::fromStdString(node->to_string());
    QGraphicsTextItem* text = scene->addText(nodeText);

    // Set a consistent font size and boldness
    QFont font = text->font();
    font.setBold(true);
    font.setPointSize(10);  // Set a consistent font size
    text->setFont(font);
    text->setDefaultTextColor(QColor(139, 0, 0));  // Dark red text
    text->setPos(x - text->boundingRect().width() / 2, y - text->boundingRect().height() / 2);

    int childIndex = 0;
    for (auto child : node->get_children()) {
        int childX = x + (childIndex - node->get_children().size() / 2.0) * offset;
        int childY = y + 80;  // Increase the vertical distance between nodes

        float dx = childX - x;
        float dy = childY - y;
        float length = sqrt(dx * dx + dy * dy);
        dx /= length;
        dy /= length;

        int startX = x + dx * ellipseRadius;
        int startY = y + dy * ellipseRadius;
        int endX = childX - dx * ellipseRadius;
        int endY = childY - dy * ellipseRadius;
        QPen linePen(QColor(139, 0, 0));
        linePen.setWidth(2);  // Thicker lines
        scene->addLine(startX, startY, endX, endY, linePen);

        drawTree(scene, child, childX, childY, offset / 2);
        childIndex++;
    }
}

template <typename T>
ostream& operator<<(ostream& os, Tree<T>& tree) {
    int argc = 0;
    char* argv[] = {nullptr};
    QApplication app(argc, argv);
    QMainWindow window;

    auto* scene = new QGraphicsScene(&window);
    auto* view = new QGraphicsView(scene, &window);
    window.setCentralWidget(view);
    view->setSceneRect(0, 0, 800, 600);

    drawTree(scene, tree.get_root(), 400, 30, 200);

    window.show();
    app.exec();

    return os;
}
