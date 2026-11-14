## Run it on Eolymp

Compiler: **Haskell (ghc 8.8)**

Open [What is left? #1964](https://eolymp.com/problems/1964), choose **Haskell** as the compiler, paste the program below, and run it. For the sample, use input `10`. The program prints `3`.

```haskell
module Main where

solve :: [Int] -> Int -> [Int]
solve [x] _ = [x]  -- one value left
solve xs phase =
    solve
        -- zip [1..] numbers positions from 1 on the current list.
        -- The next call sees only the kept values, so positions start at 1 again.
        [x | (i, x) <- zip [1..] xs, keep phase i]
        ((phase + 1) `mod` 3)

keep :: Int -> Int -> Bool
keep 0 i = odd i             -- odd positions stay
keep 1 i = even i            -- even positions stay
keep 2 i = i `mod` 3 /= 0    -- positions divisible by 3 go

main :: IO ()
main = do
    n <- readLn
    print (head (solve [1..n] 0))
```

This submission scored **97/100** on Eolymp. The solution filters a list: `zip [1..]` numbers the current values from 1, and each pass keeps the positions for that phase. The last test set exceeded the 5 second limit.

![Eolymp result: 97/100 on problem 1964](97-score.png)

The source file is [Main.hs](Main.hs).
