#ifndef SEQUENCE_H
#define SEQUENCE_H

template <class Key, class Info>
class Sequence {
    public:
        struct KeyInfoPair {
            Key key;
            Info info;
        };

    private:
        struct SequenceNode {
            KeyInfoPair data;
            SequenceNode* next;
        };

        SequenceNode* head;
        SequenceNode* tail;
        int size;

        void copyList(const Sequence<Key, Info>&);
        void deleteList();
        static SequenceNode* createNode(const Key&, const Info&);

    public:
        class const_iterator {
            friend class Sequence;

            private:
                const_iterator();
                const_iterator(SequenceNode*);
            protected:
                SequenceNode* node;
            public:
                const KeyInfoPair& operator*();
                const KeyInfoPair* operator->();
                const_iterator operator++();
                const_iterator operator++(int);
                bool operator==(const const_iterator&);
                bool operator!=(const const_iterator&);
        };
        class iterator : public const_iterator {
            public:
                KeyInfoPair& operator*();
                KeyInfoPair* operator->();
                KeyInfoPair& operator=(const KeyInfoPair&);
                iterator operator++();
                iterator operator++(int);
        };

        const_iterator cbegin() const;
        const_iterator cend() const;
        iterator begin();
        iterator end();

        Sequence<Key, Info>();
        Sequence<Key, Info>(const Sequence<Key, Info>&);
        ~Sequence<Key, Info>();

        Sequence<Key, Info>& operator=(const Sequence<Key, Info>&);
        Sequence<Key, Info> operator+(const Sequence<Key, Info>&);
        Sequence<Key, Info>& operator+=(const Sequence<Key, Info>&);

        void add(const Key&, const Info&);
        void add(const KeyInfoPair&);
        bool add(const Key&, const Info&, int);
        bool add(const KeyInfoPair&, int);
        bool add(const Sequence<Key, Info>&);
        bool copy(int, Sequence<Key, Info>&) const;
        bool copy(int, Sequence<Key, Info>&, int) const;
        bool get(int, Key&, Info&) const;
        bool get(int, KeyInfoPair&) const;
        bool remove();
        bool remove(int);
        int getSize() const;
};

#include "sequence.hpp"
#include "sequenceiterator.hpp"

#endif
