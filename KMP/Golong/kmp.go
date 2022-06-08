package kmp

func getNext(T string) []int {
	L := len(T)
	next := make([]int, L)
	i := 0
	k := -1
	for i < L-1 {
		if k == -1 || T[i] == T[k] {
			i++
			k++
			if T[i] != T[k] {
				next[i] = k
			} else {
				next[i] = next[k]
			}
		}
	}
	return next
}

func KMP(S, T string) int {
	var Ls, Lt int = len(S), len(T)
	var i, j int
	next := getNext(T)
	for i < Ls && j < Lt {
		if j == -1 || S[i] == T[j] {
			i++
			j++
		} else {
			j = next[j]
		}
	}
	if j == Lt {
		return i - j
	}
	return -1
}
