SELECT WARE, min(PRICE) AS MIN, max(PRICE) AS MAX
FROM PRODUCT
GROUP BY WARE

ORDER BY (MAX - MIN) DESC
LIMIT 3