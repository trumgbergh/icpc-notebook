/**
 * queue qx, qy;
 * qx.push(s);
 * while one of the two queues is not empty:
 *     u = pop minimal distant node among the two heads
 *     for all edges e of form (u, v):
 *         if dist(v) > dist(u) + cost(e):
 *             dist(v) = dist(u) + cost(e);
 * if cost (e)
 *     == x : qx.push(dist(v), v);
 * else
 *     qy.push(dist(v), v);
 **/
