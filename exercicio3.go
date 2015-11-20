package main

import (
	"fmt"
	"runtime"
)

var max_threads int = 5000
var global_counter int = 0

func main() {
	runtime.GOMAXPROCS(4)

	done := make(chan bool)

	for i := 0; i < max_threads; i++ {
		go new_thread(done, i)
	}

	for i := 0; i < max_threads; i++ {
		<-done
	}

	fmt.Printf("The value of global_counter is %d\n", global_counter)
}

func new_thread(done chan bool, tid int) {
	for i := 0; i < 100; i++ {
		global_counter++
	}

	done <- true
}
