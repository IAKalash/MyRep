SELECT COMPANY FROM MANUFACTURER m
JOIN PRODUCT p ON p.RECIPE_ID = m.RECIPE_ID
LEFT JOIN MATERIAL mat ON mat.RECIPE_ID = m.RECIPE_ID
GROUP BY COMPANY
HAVING (count(DISTINCT p.WARE) > count(DISTINCT mat.WARE))
ORDER BY COMPANY