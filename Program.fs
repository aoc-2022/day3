open System.IO
let lines = File.ReadAllLines "/tmp/aoc/input" |> Array.toList 

let splitLine (s:string) =
    let l = s.Length / 2
    let s1 = s.Substring(0,l)
    let s2 = s.Substring(l)
    (s1,s2)

let toSet (s:string) =
    s.ToCharArray () |> Array.toSeq |> Set.ofSeq
let toSets ((s1,s2):string*string) =
    (s1 |> toSet, s2 |> toSet)

let findCommon ((s1,s2):Set<char>*Set<char>) =
    let s = Set.intersect s1 s2
    s.MinimumElement

let toPriority (c:char) =
    if c >= 'a' && c <= 'z' then (c |> int) - ('a' |> int) + 1
    else (c |> int) - ('A' |> int) + 27
    
lines |> List.map (splitLine) |> List.map toSets |> List.map findCommon
      |> List.map toPriority
      |> List.sum
      |> printfn "%A"

let rec toGroupSets (lines: List<string>) =
    match lines with
    | a :: b :: c :: rest ->
        (Set.intersectMany [a |> toSet; b |> toSet; c |> toSet]) :: (toGroupSets rest)
    | [] -> []
    
let badges = lines |> toGroupSets |> List.map (Set.minElement)

let sum = badges |> List.map toPriority |> List.sum  |> printfn "%A"

printfn $"{badges}"