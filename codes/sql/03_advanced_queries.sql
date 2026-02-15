-- Advanced SQL patterns: window functions, CTEs, and recursive queries.

-- 1) Window function: rank products by price within each category.
SELECT
    category,
    product_name,
    unit_price,
    RANK() OVER (PARTITION BY category ORDER BY unit_price DESC) AS price_rank
FROM products;

-- 2) Common table expression: daily revenue summary with a running total.
WITH daily_revenue AS (
    SELECT
        o.order_date,
        SUM(oi.quantity * oi.unit_price) AS revenue
    FROM orders AS o
    JOIN order_items AS oi ON oi.order_id = o.order_id
    GROUP BY o.order_date
)
SELECT
    order_date,
    revenue,
    SUM(revenue) OVER (ORDER BY order_date) AS running_total
FROM daily_revenue
ORDER BY order_date;

-- 3) Conditional aggregation: split revenue by payment method.
SELECT
    p.payment_method,
    COUNT(*) AS payment_count,
    SUM(p.paid_amount) AS total_paid
FROM payments AS p
GROUP BY p.payment_method
ORDER BY total_paid DESC;

-- 4) Recursive CTE: employee reporting chain.
WITH RECURSIVE org_chart AS (
    SELECT
        employee_id,
        manager_id,
        full_name,
        1 AS level
    FROM employees
    WHERE manager_id IS NULL

    UNION ALL

    SELECT
        e.employee_id,
        e.manager_id,
        e.full_name,
        oc.level + 1 AS level
    FROM employees AS e
    JOIN org_chart AS oc ON oc.employee_id = e.manager_id
)
SELECT *
FROM org_chart
ORDER BY level, full_name;

-- 5) Percentile calculation: find the 90th percentile order value.
SELECT
    PERCENTILE_CONT(0.9) WITHIN GROUP (ORDER BY order_total) AS p90_order_total
FROM (
    SELECT
        o.order_id,
        SUM(oi.quantity * oi.unit_price) AS order_total
    FROM orders AS o
    JOIN order_items AS oi ON oi.order_id = o.order_id
    GROUP BY o.order_id
) AS totals;
