package ioo

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func IO() {
	fmt.Println("------------io learn ---------")
	reader := bufio.NewReader(os.Stdin)
	for i := 1; i > 0; i-- {
		text, err := reader.ReadString('\n')
		if err == nil {
			fmt.Println(strings.TrimSpace(text))
		} else {
			break
		}

	}
}

// 读取文件
// func main() {
// 	file, err := os.Open("words.txt")
// 	if err != nil{
// 	  fmt.Println(nil)
// 	  os.Exit(1)
// 	}
// 	defer file.Close()
// 	scanner := bufio.NewScanner(file)
// 	for scanner.Scan(){
// 	  fmt.Println(strings.TrimSpace(scanner.Text()))
// 	}
  
//   }