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
        SequenceNode* copyNode(SequenceNode&);
    public:
        Sequence<Key, Info>();
        Sequence<Key, Info>(const Sequence<Key, Info>&);

        Sequence<Key, Info>& operator=(const Sequence<Key, Info>&);
        Sequence<Key, Info> operator+(const Sequence<Key, Info>&);
        Sequence<Key, Info>& operator+=(const Sequence<Key, Info>&);

        void add(Key&, Info&);
        void add(Key&, Info&, int);
        void add(const Sequence<Key, Info>&);
        void copy(int, const Sequence<Key, Info>&);
        void copy(int, const Sequence<Key, Info>&, int);
        void remove();
        void remove(int);
        void removeKey(Key&);
        int getSize();
};

#include "sequence.tpp"

#endif
