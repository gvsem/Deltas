# Deltas
Diff&amp;Merge problem on primitive types with support of classes

:trophy: Best section's presentation Award at Congress of Young Scientists 2021, Saint Petersburg

The problems of using optimistic replication technologies for semantically complex data models are discussed. A template library in the C++ language is proposed and described for the implementation of automatic comparison and merging operations of collections of the standard STL library. The use of the library is illustrated by the example of the developed address book application with the function of synchronizing book replicas.

### Introduction

Optimistic replication technologies are widely used in distributed information systems, which are subject to increased requirements for data availability. Examples of successful application of technologies are non-relational NoSQL databases, DNS servers, version control systems, complex engineering systems, MMO games. Unlike pessimistic transaction control policies based on data locks, optimistic policies provide for the creation of replicas of data for each client (computing node or application) and granting unlimited access to them under the optimistic assumption that divergent replicas can be reduced to a single consistent representation, and possible merge conflicts can be resolved.

Rejection of ACID transactional requirements (Atomicity, Consistency, Isolation, Durability) in favor of BASE principles (Basically Available, Soft state, Eventually consistent), and in particular, the transition from constant consistency to data consistency ultimately improves data availability (Availability) . This is consistent with the well-known CAP-theorem, the statement of which is the impossibility of designing a distributed information system that would simultaneously ensure data consistency, availability, and partition tolerance (Partition Tolerance).

At the same time, a serious obstacle in applying the optimistic approach is the need to identify and resolve conflicts between divergent replicas in such a way that the resulting consistent representation combines the maximum number of changes and at the same time satisfies all the semantic constraints prescribed by the data model. The problem is greatly simplified when using data structures with commutative operations (the so-called CRDT types). However, for more practical cases of using semantically complex models, for example, models with algebraic constraints formally specified in the declarative information modeling languages ​​EXPRESS, UML/OCL, OWL, SQL, the problem becomes extremely complex and requires new systematic approaches to the solution.

The development of software applications for optimistic replication also causes great difficulties, since the implementation of the necessary functions for comparing and merging replicas (or more precisely, the functions for finding and combining diff & merge difference transformations) must also take into account various semantic model constraints and the numerous data dependencies they generate.

### Main part

The paper proposes an approach to developing optimistic replication applications in C++, assuming that the data model is represented by collections of standard types set, multiset, list, vector, map and is implemented in the target or legacy application based on the standard STL library. The approach involves the use of template implementations for comparison and merging of collections within the three-way scheme (3-way merge) in accordance with the following definitions:

Let a replica B be optimistically obtained from the original version A, replicas A and B are polymorphic to the same type T, on which the set of operations φ(T) is defined. Then a ∆-transformation from A to B on type T is the minimal sequence of operations that, when applied to A, yields B.

The merging of two replicas B and C, obtained optimistically from A, of the same type T is a real ∆-transformation over A, whose sequence of operations includes both ∆(A, B) and ∆(A, C) as subsequences, while such a sequence contains the maximum possible number of non-conflicting operations and, when applied to A, generates a new replica Ω(A, B, C) of type T.

The developed template library provides ready-to-use implementations of ∆-transformations, hereinafter referred to as deltas. Deltas are represented as compositions or sequences of operations that can be computed over a given pair of collection replicas (for example, diff(A, B) → ∆(A, B)), applied to update a collection replica (patch(A, ∆(A, B )) → B), are inverted to implement the inverse transformation (invert(∆(A, B)) → ∆(B, A)), combined (compose(∆(A, B), ∆(B, C)) → ∆ (A, C)) or merged (merge(∆(A, B), ∆(A, C)) → ∆(A, Ω(A, B, C))).

Deltas are represented as typed objects and are constructed depending on the type of collections and the type of elements they are intended to work with. The delta type predetermines the set of allowed operations and their signatures. For unordered collections, these are the operations of adding, removing, and modifying elements of the corresponding type. For ordered collections, these are the operations of inserting, deleting, and replacing elements at given positions. The delta type also defines a set of algorithms that can be used to compare and merge collections. For example, to calculate ∆-transforms for ordered collections, versions of the Wagner-Fisher, Myers, and Hunt-Szymansky algorithms implemented in the library are used.

The provided ways of parameterization of templates ensure their correct use for collections of elements of primitive and constructed types of the C++ language, nested collections, collections of objects, etc.

### Conclusion

Thus, we have proposed an approach to developing optimistic replication applications in C++ based on a template library for collection comparison and merging operations. The approach has been successfully tested in the creation of an address book software application with the function of synchronizing book replicas and seems promising for the development of other classes of applications. The directions of further research will be the development of an approach for arbitrary object-oriented data models, as well as the analysis of ways to automate the development of optimistic replication software applications.

### Slides

The following slides were automatically translated by Google Translate.

![1](slides/KMU2021Semenov2%20(1)_page-0001.jpg)
![2](slides/KMU2021Semenov2%20(1)_page-0002.jpg)
![3](slides/KMU2021Semenov2%20(1)_page-0003.jpg)
![4](slides/KMU2021Semenov2%20(1)_page-0004.jpg)
![5](slides/KMU2021Semenov2%20(1)_page-0005.jpg)
![6](slides/KMU2021Semenov2%20(1)_page-0006.jpg)
![7](slides/KMU2021Semenov2%20(1)_page-0007.jpg)
![8](slides/KMU2021Semenov2%20(1)_page-0008.jpg)
![9](slides/KMU2021Semenov2%20(1)_page-0009.jpg)
![10](slides/KMU2021Semenov2%20(1)_page-0010.jpg)
![11](slides/KMU2021Semenov2%20(1)_page-0011.jpg)
![12](slides/KMU2021Semenov2%20(1)_page-0012.jpg)
![13](slides/KMU2021Semenov2%20(1)_page-0013.jpg)
![14](slides/KMU2021Semenov2%20(1)_page-0014.jpg)
![15](slides/KMU2021Semenov2%20(1)_page-0015.jpg)
