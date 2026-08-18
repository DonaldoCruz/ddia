[[Indexes]]
* **Heap file**( #disk_memory ) : location where the data is actually stored and is referenced by the key index.

Example of Non-clustered (Pointer to Heap file)
```
Query: "give me the record where id = 42"
        ↓
  Key-Value Index
  key=42 → value=byte_offset(1234)
        ↓
  Follow pointer to byte 1234 in heap file
        ↓
  Actual data: {id:42, name:"Managua", population:1.4m}
```

* **Clustered Index**: The value of the key-value pair index is the actual data. ([[Indexes#^clustered-index]])
* **Covering Index / Index with included columns**: Compromise between clustered and nonclustered index. It stores some o the tables columns within the index. [[Indexes#^covering-index]]

![Image showing secondary index and how they point to heap file](secondary_index_heap_file.png)

![Image showing secondary index that is a clustered index](secondary_clustered_index.png)

**Multi-column index**:

**Multi-dimensional index**:

**Automaton**:

**In-memory Database**s:
* Storage is in RAM
* e.g., Redis

**Anti-caching Approach**:

**Non-volatile Memory (NVM)**: 

**Online Transaction Processing (OLTP)**: read and writes small number of records. Data represents latest state of data (current point in time). 
* The term comes from the early days where databases were used to process commercial transactions such as sales, products, blog posts.

**Online Analytic Processing (OLAP)**: Read and writes large amounts of data, usually with the purpose of providing business intelligence and help support/make business decisions
* OLAP usually deals with aggregations and analytics on OLTP data. They help answer questions like "what was our total revenue last year from selling XYZ?".



