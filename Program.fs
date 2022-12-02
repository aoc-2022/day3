open System.IO
let lines = File.ReadAllLines "/tmp/aoc/input" |> Array.toList 

lines |> List.map (printfn "%A")