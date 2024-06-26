// TreeWidget.hpp

#pragma once

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QFontMetrics>
#include "tree.hpp"
#include "node.hpp"

template <typename T>
class TreeWidget : public QWidget {
    Q_OBJECT

private:
    Tree<T>* tree;

public:
    TreeWidget(Tree<T>* tree, QWidget* parent = nullptr) : QWidget(parent), tree(tree) {}

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        if (tree->get_root() != nullptr) {
            drawNode(painter, tree->get_root(), width() / 2, 30, width() / 4);
        }
    }

    void drawNode(QPainter& painter, Node<T>* node, int x, int y, int hSpacing) {
        if (node == nullptr) {
            return;
        }

        painter.setBrush(Qt::white);
        painter.setPen(Qt::black);

        QString nodeValue = QString::number(node->get_value());
        QRect nodeRect = painter.fontMetrics().boundingRect(nodeValue);
        nodeRect.moveCenter(QPoint(x, y));

        painter.drawEllipse(nodeRect);
        painter.drawText(nodeRect, Qt::AlignCenter, nodeValue);

        int childX = x - hSpacing;
        int childY = y + 50;

        for (auto child : node->get_children()) {
            if (child != nullptr) {
                painter.drawLine(x, y + nodeRect.height() / 2, childX, childY - nodeRect.height() / 2);
                drawNode(painter, child, childX, childY, hSpacing / 2);
                childX += hSpacing;
            }
        }
    }
};
