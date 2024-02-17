# Selection operator $\sigma$
it selects rows from a relation
$\sigma_{\text{condition1} \wedge \text{condition2}} \text{  relationName}$  
(in sql `where`)
# Project operator $\Pi$
it selects columns from a relation
$\Pi_{\text{attributeName1,attributeName2}} \text{  relationName}$
(in sql `select`)
# Composition
Relational operators return relations so we can compose the operators.
e.g. $\Pi_{\text{id,name}}(\sigma_{\text{GPA>3.7}} \text{  Student})$

# Duplicates
If the result of the query contains duplicates they are eliminated in relational algebra. (not in SQL bcs uses multisets)
(in sql to have unique tuples only we use `distinct`)
# Cross-Product $\times$ 
The same as set cartesian product, in RA if two attributes have the same name we prefix them with the name of the relation they belong to.
Given relations $A$ and $B$, $|A\times B|=|A||B|$.
Can be useful for obtaining all the possible combinations of rows in two relations and do some query on this set.
# Natural Join $\bowtie$ 

A natural join is a like a cartesian product combined with a selection operator with the condition that attributes with the same name in the 2 relations must be equal (it then removes duplicate columns).

# Theta Join $\bowtie_{\theta}$

$\text{Exp1} \bowtie_{\theta} \text{Exp2}=\sigma_{\theta}(\text{Exp1}\times\text{Exp2})$
Where $\theta$ is a condition to use in the selection operation.
(in sql `inner join`)
# Union operator $\cup$

With joins we can merge relations horizontally, when we want to obtain e.g. a column that's the union of two columns we can use the union.
(in sql `union`)
# Difference operator $-$
E.g. IDs of students that didn't apply anywhere

$\Pi_{ID} \text{ Student} - \Pi_{ID} \text{ Apply}$

If we want the names of the students that didn't apply anywhere we can use a trick called `join back`
$\Pi_{\text{name}}((\Pi_{ID} \text{ Student} - \Pi_{ID} \text{ Apply})\bowtie \text{Student})$

 We cannot do:
$\Pi_{ID,\text{name}} \text{ Student} - \Pi_{ID} \text{ Apply}$ because they are sets with different items inside, we need to use the `join back`.

(in sql `except`)
# Intersection operator $\cap$
Intersect two relations, so we find the tuples that are in both relations.
(Intersection could also be defined as $E_{1}\cap E_{2}=E_{1}-(E_{1}-E_{2})$)
For intersection and union we should actually only use relations with the same schema, to make two expressions have the same schema we can use the rename operator.

(in sql `intersect`)
# Rename operator $\rho$
$\rho_{R(A_{1},A_{2},\dots,A_{n})}(E)$ (in general)
$\rho_{R}(E)$ to only rename the relation
$\rho_{A_{1},A_{2},\dots,A_{n}}(E)$ to only rename the attributes 
rename is useful for when we want to do union or intersections on for example 2 string attributes that have different names.
It can also be useful for `self join` e.g. Pairs of colleges in same state, we cannot do $\sigma_{\text{state=state}}(\text{College}\times\text{College})$ but we can do: 
$\sigma_{\text{s1=s2}}(\rho_{c1(n1,s1,e1)}(\text{College})\times\rho_{c2(n2,s2,e2)}(\text{College}))$
to distinguish the attributes or equivalently using natural join:
$(\rho_{c1(n1,s,e1)}(\text{College})\bowtie\rho_{c2(n2,s,e2)}(\text{College}))$
using the same for attribute state to use natural join.

(in sql we use `as` and table variables to rename relations)

---
# Sub-queries
You can do sub-queries in the where clause, some queries can only be written using sub-queries.
Sub-queries can also be used in the from clause or the select clause to get a relation that we want to reuse in multiple parts of the query. If the sub-query is in the select clause it need to return just one value.
Example of sub-query in where:
```
SELECT customer_num, company FROM customer
  WHERE NOT EXISTS
    (SELECT * FROM orders
       WHERE customer.customer_num = orders.customer_num);
```
Example of sub-query in from (derived tables/table expressions):
```
SELECT LIMIT 1 * FROM 
   (SELECT c.customer_num, c.lname, c.company, 
           c.phone, u.call_dtime, u.call_descr
                 FROM customer c, cust_calls u
                 WHERE c.customer_num = u.customer_num
    ORDER BY u.call_dtime DESC);
```
in this case we use the sub-query to get all the customers and their corresponding calls, and the external query to get only the tuple with the longest call time.

Example of sub-query in select:
```
SELECT customer.customer_num,
   (SELECT SUM(ship_charge) 
       FROM orders
       WHERE customer.customer_num = orders.customer_num) 
         AS total_ship_chg
   FROM customer;
```
we use it to get a summary value for a column in another relation (orders) that corresponds to a customer.

---
# Joins
## Inner join
To do $\bowtie_{\theta}$ in sql we use `inner join` which does the cross products and then only shows tuples for which the condition after `on` is verified.
```
select distinct sName, major
from Student inner join Apply
on Student.sID = Apply.sID;

select distinct sName, major
from Student join Apply
on Student.sID = Apply.sID;
```
these two queries are equivalent and they are the same as:
```
select distinct sName, major
from Student, Apply
where Student.sID = Apply.sID;
```

In some sql implementations `join` is binary, in some you use it like this:```

```
College join Apply join Student
```

## Natural join/using
If we use `natural join` it's the same as $\bowtie$ in RA, the tuples are matched where the attributes with the same name are equal and duplicate columns are not shown (and we don't need to put equality in the `where` clause).

It's considered good practice to use instead use an `inner join` and specify on which attributes with `using`, e.g.:
```
select sName, GPA
from Student join Apply using(sID)
where sizeHS < 1000 and major = 'CS' and cName = 'Stanford';
```
Most sql implementation don't allow to use both `using` and `on` at the same time, in this case just use `where`.

## Outer join
Sometimes we may want the `join` to also show tuples that don't have a matching tuple in the other relation, if for example we want to also include the students who haven't applied anywhere we can do a `left join`:
```
select sName, sID, cName, major
from Student left outer join Apply using(sID);
```
If we want instead to see the applications for which there is no student we can use `right join`:
```
select sName, sID, cName, major
from Student natural right outer join Apply;
```
Note from the query above that outer joins can also be natural, we can just avoid specifying `using`.

if we want to have both students that haven't applied anywhere and applications with no corresponding student we can use `full join`:
```
select sName, sID, cName, major
from Student full outer join Apply using(sID);
```

Note that in all outer joins the `outer` keyword can be omitted.

Outer joins are ***not*** associative!
# Aggregation

---
`in`, `like`,`exists`,`all`,`any`,`abs`,`max`,`min`, `avg`,`count`,`sum`