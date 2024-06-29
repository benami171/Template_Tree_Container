#ifndef TREE_HPP
#define TREE_HPP
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

#include "iterators.hpp"
#include "node.hpp"

#define BINARY 2
#define LEFT_CHILD 0
#define RIGHT_CHILD 1

template <typename T, int K = BINARY>
class Tree {
   private:
    Node<T>* root;
    int max_children = K;
    vector<Node<T>*> all_nodes;  // To manage all nodes’ lifetimes

   public:
    Tree() : root(nullptr) {}

    ~Tree() {
        for (auto it = all_nodes.rbegin(); it != all_nodes.rend(); ++it) {
            (*it)->delete_children();
        }
    }

    void add_root(Node<T>* root) {
        if (this->root != nullptr) {
            for (auto it = all_nodes.rbegin(); it != all_nodes.rend(); ++it) {
                (*it)->delete_children();
            }
        }
        this->root = root;
        all_nodes.push_back(root);
    }

    void add_sub_node(Node<T>* parent, Node<T>* child) {
        if (parent->get_children().size() >= (size_t)max_children) {
            throw std::runtime_error("Parent has reached its maximum number of children");
        }
        parent->add_child(child);
        all_nodes.push_back(child);
    }

    Node<T>* get_root() {
        return root;
    }

    using iterator_pre_order = typename std::conditional<K == BINARY, pre_order_iterator<T>, dfs_iterator<T>>::type;
    using iterator_post_order = typename std::conditional<K == BINARY, post_order_iterator<T>, dfs_iterator<T>>::type;
    using iterator_in_order = typename std::conditional<K == BINARY, in_order_iterator<T>, dfs_iterator<T>>::type;
    using iterator_min_heap = typename std::conditional<K == BINARY, min_heap_iterator<T>, dfs_iterator<T>>::type;

    iterator_pre_order begin_pre_order() {
        return iterator_pre_order(this->root);
    }

    iterator_pre_order end_pre_order() {
        return iterator_pre_order(nullptr);
    }

    iterator_post_order begin_post_order() {
        return iterator_post_order(this->root);
    }

    iterator_post_order end_post_order() {
        return iterator_post_order(nullptr);
    }

    iterator_in_order begin_in_order() {
        return iterator_in_order(this->root);
    }

    iterator_in_order end_in_order() {
        return iterator_in_order(nullptr);
    }

    dfs_iterator<T> begin_dfs_scan() {
        return dfs_iterator<T>(this->root);
    }

    dfs_iterator<T> end_dfs_scan() {
        return dfs_iterator<T>(nullptr);
    }

    bfs_iterator<T> begin_bfs_scan() {
        return bfs_iterator<T>(this->root);
    }

    bfs_iterator<T> end_bfs_scan() {
        return bfs_iterator<T>(nullptr);
    }

    bfs_iterator<T> begin() {  // Default iterator
        return begin_bfs_scan();
    }

    bfs_iterator<T> end() {  // Default iterator
        return end_bfs_scan();
    }

    iterator_min_heap begin_min_heap() {
        return iterator_min_heap(this->root);
    }

    iterator_min_heap end_min_heap() {
        return iterator_min_heap(nullptr);
    }

    std::pair<iterator_min_heap, iterator_min_heap> myHeap() {
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

#endif