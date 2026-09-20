

* **Vertical scaling**: Increase the resources on one machine.
* **Horizontal scaling**: deploying an application across multiple machines.

* **Replication**: Copying data on one machine into other machines that are connected via a network.
* **Partitioning**: Splitting bid data into smaller subsets called partitions. Also known as **sharding**.

### Algorithms for replicating changes to data
* **single-leader replication**
* **multi-leader replication**
* **leaderless replication**

* **Leader-based replication**: Essentially, you have one machine that accepts writes from the client, it then propagates these changes via a **replication log** or **change stream**
to the replica nodes. Those replica nodes only accept read-only queries.
    * **Synchronous replication**: The leader node/machine must wait for a response from one of the followers, assuring that a write has been processed and replicated.
    * **Asynchronous replication**: The leader node does not wait for a response from the followers. It can keep accepting writes. The only issue is that if the leader fails,
    it could mean that writes are lost.
    * **Semi-synchronous replication**: Configuration where one of the followers is synchronous, while another follower is asychronous.

* **Catch-up recovery**: Follower nodes usually store a leader's change log in local disk. Meaning that if the follower for some reason fails (e.g., power outage, network failure, etc)
it can request from the leader, all changes that happened from that failure point onwards. Once it is caught up, it can continue receiving writes as usual.

* **Failover**: Refers to when a leader fails, a follower node becomes the new leader.
    * Many systems have automatic failover, others require a manual process to switch.
    * Different systems have ways of detectin  **split brain** (two leaders at the same time) scenarios which could lead to corrupted data.
    * In the case of asynchronous writes, the new leader may not have all the data and when the old leader comes back on, it can make writes that conflict
    with new writes. You can delete those old writes, but that could violate clients' durability expectations.
        * Github once has this problem, an old leader came back on a performed writes. The new leader has IDs that were lagging behind. This caused some users to 
        have access to other users' data.

* **Statement-based replication**: The whole INSERT, UPDATE, DELETE SQL statement is sent to follower and executed on those machines.
    * The issues that arise with this is that nondeterministic statements like ROW(), RAND(), NOW(), will have different values from node-to-node.
* **Write-ahead log (WAL) shipping**: A log is passed to followers, It is very closely coupled to the storage engine because the log stores the changes byte for byte.
    * An issue that arises with this is the difficulty you can have when trying to upgrade your nodes to a new version of the storage engine because the data will be different.
* **Logical (row-based) log replication**: Decouples the replication log from the storage engine. Allows for an easier time with backward compatibility (compared to WAL shipping)
it also allows for an easier time with **change data capture (CDC)**.
* **Trigger-based replication**: Some automated trigger on the database like stored procedures or triggers, sends data changes to a table. Then an external process
can read from that table and apply applicationlogic and replicate the data change to another system.
* **Replication lag**: This refers to the delay that happens when the leader sends the write to the follower. A useful setup is for the leader to accept write requests, and any
read requests go to the followers. This is called read-scaling, and if a system requires more reads/ many read requests, you can use many followers for read only requests.
    * The problem with this is that sometimes followers can fall behind, specially if it is a synchronous system. In a synchronous system, a failure can cause the whole system
    to go down for some time.
    * In an asynchronous setup, followers can fall behind, so data can be inconsistent if the delay is great. This is called **eventual consistency**.
