-----------------------------------------------------------------------------
-- |
-- Module      :  SQLHSExample
-- Copyright   :  (c) 2019-2021 Konstantin Pugachev
--                (c) 2019 Denis Miginsky
-- License     :  MIT
--
-- Maintainer  :  K.V.Pugachev@inp.nsk.su
-- Stability   :  experimental
-- Portability :  portable
--
-- The SQLHSExample module provides examples of using SQLHS/SQLHSSugar module.
--
-----------------------------------------------------------------------------

import SQLHSSugar
import DBReader

-- CATEGORY:     WARE,    CLASS
-- MANUFACTURER: RECIPE_ID, COMPANY
-- MATERIAL:     RECIPE_ID, WARE,   AMOUNT
-- PRODUCT:      RECIPE_ID, WARE,   AMOUNT, PRICE

main = readDB' defaultDBName >>= executeSomeQueries

executeSomeQueries :: (Named Table, Named Table, Named Table, Named Table) -> IO ()
executeSomeQueries (categories, manufacturers, materials, products) = do
  test "task1" task1
  test "task2" task2
  test "task3" task3
  -- test "lecPlan1'" lecPlan1'
  -- test "lecPlan2" lecPlan2
  -- test "lecPlan3" lecPlan3
  -- test "lecPlan4" lecPlan4
  -- test "lecPlan4'" lecPlan4'
  
  where
    test msg p = do
      putStrLn $ "===== execute " ++ msg ++ " ====="
      -- putStrLn . debugTable $ p & enumerate
      printResult $ p & enumerate
    
    task1 = 
      categories // "c" `wher` col "c.CLASS" `eq` str "Mineral"
      `hjoin` (materials // "m" `indexby` col "WARE") `on` col "c.WARE"
      `hjoin` (products // "p" `indexby` col "RECIPE_ID") `on` col "m.RECIPE_ID"
      `orderby` ["p.WARE":asc]
      `select` ["p.WARE"] & distinct

    task2 =
      categories // "cm" `wher` col "cm.CLASS" `eq` str "Mineral"
      `hjoin` (materials // "m") `indexby` col "WARE" `on` col "cm.WARE"
      `hjoin`
      (categories // "cp" `wher` col "cp.CLASS" `eq` str "Stuff"
      `hjoin` (products // "p") `indexby` col "WARE" `on` col "cp.WARE") 
      `indexby` col "RECIPE_ID" `on` col "m.RECIPE_ID"
      `orderby` ["m.RECIPE_ID":asc] 
      `select` ["m.RECIPE_ID", "m.WARE", "p.WARE"]
      & limit 0 50

    task3 = 
      manufacturers // "man1"
      `hjoin` (materials // "m") `indexby` col "RECIPE_ID" `on` col "man1.RECIPE_ID"
      `hjoin` (products // "p") `indexby` col "WARE" `on` col "m.WARE"
      `hjoin` (manufacturers // "man2") `indexby` col "RECIPE_ID" `on` col "p.RECIPE_ID"
      `wher` col "man2.COMPANY" `eq` col "man1.COMPANY"
      `orderby` ["man1.COMPANY":asc]
      `select` ["man1.COMPANY"] & distinct

    -- lecPlan1' = 
    --   -- MANUFACTURER NL_JOIN PRODUCT ON m.RECIPE_ID=p.RECIPE_ID
    --   manufacturers // "m" `njoin` products // "p" `on` "m.RECIPE_ID" `jeq` "p.RECIPE_ID"
    --   -- -> NL_JOIN CATEGORY ON c.WARE=p.WARE
    --   `njoin` categories // "c" `on` "p.WARE" `jeq` "c.WARE"
    --   -- -> FILTER c.CLASS='Raw food'
    --   `wher` col "CLASS" `eq` str "Raw food"
    --   -- -> SORT_BY p.WARE
    --   `orderby` ["p.WARE":asc]
    --   -- -> MAP (p.WARE, m.COMPANY)
    --   `select` ["p.WARE", "m.COMPANY"]
    --   -- -> DISTINCT
    --   & distinct 
    --   -- -> TAKE 10
    --   & limit 0 10
  
    -- lecPlan2 = 
    --   -- CATEGORY FILTER c.CLASS='Raw food'
    --   categories // "c" `wher` col "c.CLASS" `eq` str "Raw food"
    --   -- -> NL_JOIN PRODUCT ON c.WARE=p.WARE
    --   `njoin` products // "p" `on` "c.WARE" `jeq` "p.WARE"
    --   -- -> NL_JOIN MANUFACTURER ON m.RECIPE_ID=p.RECIPE_ID
    --   `njoin` manufacturers // "m" `on` "p.RECIPE_ID" `jeq` "m.RECIPE_ID"
    --   -- -> SORT_BY p.WARE
    --   `orderby` ["p.WARE":asc]
    --   -- -> MAP (p.WARE, m.COMPANY)
    --   `select` ["p.WARE", "m.COMPANY"]
    --   -- ->DISTINCT
    --   & distinct 
    --   -- -> TAKE 10
    --   & limit 0 10
  
    -- lecPlan3 = 
    --   -- CATEGORY FILTER c.CLASS='Raw food'
    --   categories // "c" `wher` col "c.CLASS" `eq` str "Raw food"  
    --   -- -> HASH_JOIN PRODUCT INDEX BY WARE ON c.WARE=p.WARE
    --   `hjoin` (products // "p" `indexby` col "WARE") `on` col "c.WARE"
    --   -- -> HASH_JOIN MANUFACTURER INDEX BY RECIPE_ID ON m.RECIPE_ID=p.RECIPE_ID
    --   `hjoin` (manufacturers // "m" `indexby` col "RECIPE_ID") `on` col "p.RECIPE_ID"
    --   -- -> SORT_BY p.WARE
    --   `orderby` ["p.WARE":asc]
    --   -- -> MAP (p.WARE, m.COMPANY)
    --   `select` ["p.WARE", "m.COMPANY"]
    --   -- ->DISTINCT
    --   & distinct 
    --   -- -> TAKE 10
    --   & limit 0 10

    -- lecPlan4 = 
    --   -- CATEGORY FILTER c.CLASS='Raw food'
    --   (categories // "c" `indexby` col "WARE" & flatten) `wher` col "CLASS" `eq` str "Raw food"
    --   -- -> MERGE_JOIN PRODUCT INDEX BY WARE ON c.WARE=p.WARE
    --   `mjoin` (products // "p" `indexby` col "WARE" & flatten) `on` "c.WARE" `jeq` "p.WARE"
    --   -- -> HASH_JOIN MANUFACTURER INDEX BY RECIPE_ID ON m.RECIPE_ID=p.RECIPE_ID
    --   `hjoin` (manufacturers // "m" `indexby` col "RECIPE_ID") `on` col "p.RECIPE_ID"
    --   -- -> MAP (p.WARE, m.COMPANY)
    --   `select` ["p.WARE", "m.COMPANY"]
    --   -- ->DISTINCT
    --   & distinct 
    --   -- -> TAKE 10
    --   & limit 0 10
  
    -- lecPlan4' = 
    --   -- CATEGORY FILTER c.CLASS='Raw food'
    --   (categories // "c" `indexby` col "WARE" & flatten) `wher` col "CLASS" `eq` str "Raw food"
    --   -- -> HASH_JOIN PRODUCT INDEX BY WARE ON c.WARE=p.WARE
    --   `hjoin` (products // "p" `indexby` col "WARE") `on` col "c.WARE"
    --   -- -> HASH_JOIN MANUFACTURER INDEX BY RECIPE_ID ON m.RECIPE_ID=p.RECIPE_ID
    --   `hjoin` (manufacturers // "m" `indexby` col "RECIPE_ID") `on` col "p.RECIPE_ID"
    --   -- -> MAP (p.WARE, m.COMPANY)
    --   `select` ["p.WARE", "m.COMPANY"]
    --   -- ->DISTINCT
    --   & distinct 
    --   -- -> TAKE 10
    --   & limit 0 10