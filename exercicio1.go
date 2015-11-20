package main

import "fmt"

func main() {
	done := make(chan bool)
	go new_thread(done, 1)
	<-done
}

func new_thread(done chan bool, tid int) {
	fmt.Printf("Nova thread criada. TID = %d!\n", tid)
	done <- true
}