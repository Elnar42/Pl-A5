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
