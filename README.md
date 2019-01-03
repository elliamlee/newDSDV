# Adaptive Destination Sequenced Distance Vector (A-DSDV)
---

## Induction
Ad-hoc network is a decentralized type of wireless network. The network is ad-hoc because it does not rely on a pre-existing infrastructure such as routers and access points in wired network. Therefore, the stations in network participate in routing by forwarding data for other nodes and in hosting. One of the important features of Ad-hoc network is that wireless mobile ad hoc networks are self-configuring and dynamic which means the nodes in the network are free to move. Because of this, routing protocols used in wired network could not be applied to ad hoc network and researches for ad hoc routing protocols have been proceeded.

Ad-hoc routing protocols usually consists of two parts: a table-driven protocol which updates and maintains the routing table and an on-demand protocol which updates the routing table as the needs of the case demand. Destination Sequenced Distance Vector (DSDV) routing protocol is a representative of table-driven protocol. DSDV is a hop-by-hop distance vector routing protocol requiring each node to periodically broadcast routing updates based on the idea of classical Bellman-Ford routing algorithm. Each node maintains a routing table listing the next hop for each reachable destination, number of hops to reach destination and the sequence number assigned by destination node. The stations periodically transmit their routing tables to their immediate neighbors. A station also transmits its routing table if a significant change has occurred in its table from the last update sent. So, the update is both time-driven and event driven. The routing table updates can be sent in two ways: a full dump or an incremental update.

In the existing DSDV routing protocol, the time at which the routing table is periodically updated at each node is fixed to a constant value. This setting is always constant regardless of the presence or absence of data packets that must be transmitted from one node to another. Therefore, this protocol has a problem that it cannot appropriately deal with the situation of the network because it uses a fixed value.

In this project, the number of packets to be transferred from each node to another node will be recorded to solve the problem. Based on this records, a new method to dynamically implement the time to periodic update of routing table is proposed and the performance of this method will be shown through simulations.

## A New Approach to Improve Performance of DSDV Algorithm
As mentioned earlier, the existing DSDV routing protocol has the fixed time value of updating routing table. For example, we could easily found that the default time value of periodic updates is 15 seconds in NS3 environment.

It does not matter when there is a lot of traffic in network. However, unnecessary updates are made and control overheads are increased when there is no traffic.

![ns1](https://user-images.githubusercontent.com/34092568/50624934-db7d9780-0f67-11e9-8370-ea81cce8b36a.png)
