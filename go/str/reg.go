package str

import (
	"fmt"
	"regexp"
)

func Reg() {
	fmt.Println("--------this is regexp learn part ---------")
	st := "2021  ps"
	reg := regexp.MustCompile(` +`)
	regDigit := regexp.MustCompile(`\d+`)
	fmt.Println(reg.MatchString(st))
	fmt.Println(regDigit.FindAllString(st, -1))
	fmt.Println(regDigit.FindStringIndex(st))
	fmt.Println(reg.ReplaceAllString(st, " "))

}
