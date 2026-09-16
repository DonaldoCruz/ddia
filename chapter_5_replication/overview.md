

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
