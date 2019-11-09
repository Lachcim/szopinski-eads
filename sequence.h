#ifndef SEQUENCE_H
#define SEQUENCE_H

template <class Key, class Info>
class Sequence {
    private:
        struct SequenceNode {
            Key key;
            Info info;

            SequenceNode* next;
        };

        SequenceNode* head;
        SequenceNode* tail;
        int size;

        void copyList(const Sequence<Key, Info>&);
        void deleteList();
        SequenceNode* createNode(const Key&, const Info&);
        void deleteNode(SequenceNode*);
    public:
        Sequence<Key, Info>();
        Sequence<Key, Info>(const Sequence<Key, Info>&);
        ~Sequence<Key, Info>();

        Sequence<Key, Info>& operator=(const Sequence<Key, Info>&);
        Sequence<Key, Info> operator+(const Sequence<Key, Info>&);
        Sequence<Key, Info>& operator+=(const Sequence<Key, Info>&);

        void add(const Key&, const Info&);
        bool add(const Key&, const Info&, int);
        bool add(const Sequence<Key, Info>&);
        bool copy(int, Sequence<Key, Info>&) const;
        bool copy(int, Sequence<Key, Info>&, int) const;
        bool get(int, Key&, Info&) const;
        bool remove();
        bool remove(int);
        int getSize() const;
};

#include "sequence.tpp"

#endif
