-- Queries for the Sakila sample database.
-- These are read-only examples that explore rentals, films, and customers.

-- 1) Top 5 categories by number of rentals.
SELECT
    c.name AS category,
    COUNT(*) AS rental_count
FROM category AS c
JOIN film_category AS fc ON fc.category_id = c.category_id
JOIN inventory AS i ON i.film_id = fc.film_id
JOIN rental AS r ON r.inventory_id = i.inventory_id
GROUP BY c.name
ORDER BY rental_count DESC
LIMIT 5;

-- 2) Customers with the most rentals and their last rental date.
SELECT
    cu.customer_id,
    CONCAT(cu.first_name, ' ', cu.last_name) AS customer_name,
    COUNT(r.rental_id) AS total_rentals,
    MAX(r.rental_date) AS last_rental
FROM customer AS cu
JOIN rental AS r ON r.customer_id = cu.customer_id
GROUP BY cu.customer_id, cu.first_name, cu.last_name
ORDER BY total_rentals DESC, last_rental DESC;

-- 3) Actors with the largest filmographies.
SELECT
    a.actor_id,
    CONCAT(a.first_name, ' ', a.last_name) AS actor_name,
    COUNT(fa.film_id) AS film_count
FROM actor AS a
JOIN film_actor AS fa ON fa.actor_id = a.actor_id
GROUP BY a.actor_id, a.first_name, a.last_name
ORDER BY film_count DESC
LIMIT 10;

-- 4) Average payment amount by store.
SELECT
    s.store_id,
    ROUND(AVG(p.amount), 2) AS avg_payment
FROM store AS s
JOIN staff AS st ON st.store_id = s.store_id
JOIN payment AS p ON p.staff_id = st.staff_id
GROUP BY s.store_id;

-- 5) Films that have never been rented.
SELECT
    f.film_id,
    f.title
FROM film AS f
LEFT JOIN inventory AS i ON i.film_id = f.film_id
LEFT JOIN rental AS r ON r.inventory_id = i.inventory_id
WHERE r.rental_id IS NULL
ORDER BY f.title;
