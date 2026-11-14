# What is left?

[What is left? #1964](https://eolymp.com/problems/1964)

Numbers from 1 to `n` are written in a row. Positions start at 1. Three passes repeat until one number is left:

1. Remove every number in an even position.
2. Number the remaining values from 1 again, then remove every number in an odd position.
3. Number the remaining values from 1 again, then remove every number in a position divisible by 3.

The cycle then starts again. The input is one integer `n` (`1 ≤ n ≤ 10^8`). The output is the last remaining number. For the sample, input `10` prints `3`. The limit is 5 seconds and 512 MB.

The same elimination is solved twice. Each folder has the program, the compiler to select on Eolymp, and a screenshot of the score.

| Solution | Compiler | Approach | Score |
| --- | --- | --- | --- |
| [CPP](CPP/README.md) | C++ | In-place array | 100/100 |
| [Haskell](Haskell/README.md) | Haskell (ghc 8.8) | List filtering | 97/100 |

## C++: 100/100

[CPP/main.cpp](CPP/main.cpp) stores `1..n` in one vector. Each pass writes the surviving values back to the front of that same array, so the next pass numbers positions from 1 again. That array manipulation passed every test. The score screenshot is in [CPP/README.md](CPP/README.md).

## Haskell: 97/100

[Haskell/Main.hs](Haskell/Main.hs) keeps the values in a list. `zip [1..]` numbers the current list from 1, and a comprehension keeps the positions for that phase. The filtered list is the input of the next pass.

This scored **97/100**. The small tests passed. The last test set exceeded the 5 second limit: a list allocates a separate cell for every number, so the largest values of `n` spend their time on allocation rather than on the filtering. The score screenshot is in [Haskell/README.md](Haskell/README.md).

The first Haskell program scored **70/100**. It built each pass with `foldl'`, consing the kept values and reversing them. Eolymp stopped it with a memory overflow at 512 MB.

```haskell
module Main where

import Data.List (foldl')

-- Phase 0 keeps odd positions, phase 1 keeps even positions,
-- phase 2 drops positions divisible by 3. Positions start at 1.
keep :: Int -> Int -> Bool
keep 0 pos = pos `mod` 2 == 1
keep 1 pos = pos `mod` 2 == 0
keep _ pos = pos `mod` 3 /= 0

-- Number the list from 1 and collect the values this phase keeps.
filterPhase :: Int -> [Int] -> [Int]
filterPhase phase xs = reverse (snd (foldl' step (1, []) xs))
  where
    step (pos, acc) y =
      let pos' = pos + 1
          acc' = if keep phase pos then y : acc else acc
      in pos' `seq` (pos', acc')

solve :: [Int] -> Int -> Int
solve [] _ = error "empty sequence"
solve [x] _ = x
solve xs phase = solve (filterPhase phase xs) ((phase + 1) `mod` 3)

main :: IO ()
main = do
  n <- readLn
  print (solve [1 .. n] 0)
```
