package main

import "fmt"

var max_threads int = 5

func main() {
	done := make(chan bool)

	for i := 0; i < max_threads; i++ {
		go new_thread(done, i)
	}

	for i := 0; i < max_threads; i++ {
		<-done
	}
}

func new_thread(done chan bool, tid int) {
	fmt.Printf("Nova thread criada. TID = %d!\n", tid)
	done <- true
}
