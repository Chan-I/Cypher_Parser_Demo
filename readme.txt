MATCH (a:Meta) RETURN count(distinct a.name)
MATCH (a:Meta) WHERE a.sys_time < 0 OR a.node_id > 845 RETURN count(a)
MATCH (n) WHERE id(n) = 345 RETURN n.mono_time, n.sys_time, n.name
MATCH (n {name:["/var/db/entropy/saved-entropy.7", "/var/db/entropy/saved-entropy.8"]}) RETURN n.node_id ORDER BY n.node_id ASC
MATCH (n) WHERE exists(n.value) AND exists(n.timestamp) RETURN count(n)
MATCH (a:Global)-[]->(b) RETURN b.node_id AS conn_id
MATCH (a)-[r:LOC_OBJ]-(b) RETURN b.name, r.state ORDER BY b.node_id ASC LIMIT 15
MATCH ()<-[r:LOC_OBJ {state:12}]-(idA {type:2}) RETURN count(r)
MATCH (n:Local)<--(m:Global) RETURN m.node_id AS thing, m.type AS ty ORDER BY m.sys_time LIMIT 3
MATCH (a)-->(b)-->(c)-->(d) WHERE id(d) < 123 RETURN count(a) AS cool
MATCH (a:Global)-->(b:Local)-->(c:Process)<--(d:Local)<--(b) RETURN count(b)
MATCH ()-[r]-() RETURN DISTINCT r.state ORDER BY r.state
MATCH (n)--()--()--()--(n) WHERE exists(n.status) RETURN count(n)
MATCH (s)-[e]-(d) WHERE id(s) = 349 AND NOT 'Process' in labels(s) AND NOT 'Global' in labels(d) RETURN d.node_id ORDER BY d.node_id ASC
MATCH (n:Process)<-[e:PROC_OBJ]-(c:Local) WHERE id(n) = 916 AND e.state in [5] RETURN c.name, e.state ORDER BY c.name DESC
MATCH (a)-[e]-(b) WHERE id(a) IN [100, 200, 300, 400] AND id(b) IN [101, 201, 202, 302, 404] RETURN e.state
MATCH (a)-[*1..3]->(c:Process) RETURN count(c)
MATCH (a:Local)-[*4..9]->(b) RETURN DISTINCT b.node_id, b.sys_time AS time_alias ORDER BY b.node_id DESC
MATCH p=shortestPath((f {name:"omega"})-[*1..6]->(t:Meta)) RETURN count(t)
MATCH (a) WHERE any(name in a.name WHERE name = 'uid') RETURN count(a)
MATCH (a) WHERE any(lab in labels(a) WHERE lab IN ['Global', 'Meta']) RETURN count(a)
MATCH (n) WHERE 'Process' in labels(n) WITH n MATCH (m) WHERE m.status = n.status RETURN count(n)
MATCH (n) WHERE 'Local' in labels(n) AND NOT exists(n.pid) WITH n MATCH (m:Global)-[r]->(n) WHERE id(m) > 900 RETURN n.node_id, r.state
MATCH (n:Global)-->(m:Local) WHERE n.node_id < m.node_id RETURN count(m)
MATCH (n:Meta)<--(m:Process)-->(p) WHERE n.node_id > m.node_id AND p.node_id <= m.node_id RETURN count(m)
MATCH (n) WHERE id(n) < 3 WITH n MATCH (m) WHERE id(m) < id(n) WITH m MATCH (p) WHERE p.node_id < m.node_id RETURN count(p)
MATCH (n) WHERE 'Meta' in labels(n) OR any(name in n.name WHERE name = 'postgres') WITH n MATCH (m:Process) WHERE id(m) > id(n) WITH m MATCH (p)-->(m) WITH p MATCH (j)<-[:PROC_OBJ_PREV]-(p) WHERE p.sys_time = j.sys_time RETURN count(j)
MATCH (a:Global {name:'postgres'})-->(b:Global) WITH b MATCH (c) WHERE c.sys_time = b.sys_time WITH c MATCH (c)<--(d) RETURN DISTINCT d.node_id ORDER BY d.node_id LIMIT 5
MATCH (a:Local)-->(b)<--(c:Process)<--(d) RETURN min(d.node_id)
MATCH (n) WHERE 'Global' in labels(n) AND any(name in n.name WHERE name = 'master') OR (exists(n.pid) AND n.status = 2) WITH n MATCH (m:Meta) WHERE m.node_id > n.node_id RETURN DISTINCT n LIMIT 10
MATCH (a) WHERE a.node_id < 345 OR ((a.node_id > 800 AND 'Process' in labels(a)) OR a.node_id = 983) RETURN count(a)
MATCH (a) WHERE (any(x in a.name where x = 'master') OR any(y in a.value where y in ['postgres', 'nginx'])) AND ('Global' in labels(a) OR 'Meta' in labels(a)) RETURN count(a)
MATCH (a)-[e]->(b)-[f]->(c) WHERE a.type = b.type AND c.pid < b.pid RETURN count(f)
MATCH (a)-[z]->(b)-[w]->(c) WHERE a.node_id < b.node_id RETURN w.state, c.type ORDER BY c.node_id ASC
MATCH (a)-[e]->(b:Process) WHERE e.state > 5 WITH b MATCH (c) WHERE (exists(c.pid) AND c.pid < b.pid) WITH c MATCH (c)<--(d:Local) WHERE any(n in d.name WHERE n = '4') RETURN count(d) AS cool_thing
MATCH (a)-->(b)-->(c) WHERE c.node_id < b.node_id WITH c MATCH (d)--(c) WHERE exists(d.ref_count) WITH d MATCH (e)-->(d)<--(f) WHERE f.node_id > e.node_id WITH f MATCH (g)<-[ww]-(f) WHERE ww.state = 5 WITH g MATCH (g)-->(ii)-->(i) RETURN DISTINCT i.node_id ORDER BY i.node_id ASC
MATCH (a)-->(b)-->(c:Process) WHERE a.node_id < b.node_id RETURN a.node_id, b.node_id, case c.type when 3 then 'boo' else 'hiss' end
MATCH (a:Global)-[:LOC_OBJ]->(b) WITH a, count(b) AS num_things WHERE num_things > 2 RETURN a.name ORDER BY a.sys_time DESC
MATCH (a)-->(b) WITH b MATCH (c)<--(b) WHERE id(c) < 643 WITH c MATCH ()-[r]-(c) RETURN count(r)
MATCH (n) WHERE id(n) IN [10, 110, 317] AND exists(n.pid) RETURN n.status, n.pid
MATCH (proc:Process)<-[po:PROC_OBJ]-(loc:Local)<-[lo:LOC_OBJ]-(gl:Global)-->(:Local)-->(proc2:Process) WHERE id(proc) IN [137, 149, 162, 278] RETURN DISTINCT proc2.pid ORDER BY proc2.pid ASC
