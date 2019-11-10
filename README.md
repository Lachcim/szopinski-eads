# szopinski-eads

My implementation of the EADS project supervised by Mr doc. dr inż. ś.p. Roman Podraza, Esq.

The goal was to write a singly-linked list of nodes capable of storing data entries of two different types (stored in fields named "key" and "info"). The project demonstrates how to properly apply the principles of generic programming and how to use the template system in the C++ programming language. The addition of iterators was not mandatory, albeit welcome.

**Note:** The code published here is for reference purposes only. Copying it verbatim constitutes academic dishonesty.

## On the implementation of templates

The C++ language standard mandates that in order for a class template to be implicitly available for use by all classes, its declaration and implementation must be kept in the same translation unit. To work around this limitation and to keep the declaration and implementation separate, the following convention was accepted: template declarations shall be stored in **.h** files, template implementations shall be stored in **.hpp** files, and the latter shall be appended to the end of the former.
