package dataType

import "fmt"

func Runee() {
	fmt.Println("---------this is data type learn -----------")
	str := "xxxxx"
	strc := "你你你"
	fmt.Println(str[0:2])
	fmt.Println(strc[0:2])
	fmt.Println(string([]rune(strc)[0:2]))
}
