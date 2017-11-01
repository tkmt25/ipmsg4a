import System;
var separator = " "
var converter = {
    // いろは
    table: {
	".-"     : ["イ", "A"],
	".-.-"   : ["ロ"],
	"-..."   : ["ハ", "B"],
	"-.-."   : ["ニ", "C"],
	"-.."    : ["ホ", "D"],
	"."      : ["ヘ", "E"],
	"..-.."  : ["ト"],
	"..-."   : ["チ", "F"],
	"--."    : ["リ", "G"],
	"...."   : ["ヌ", "H"],
	"-.--."  : ["ル"],
	".---"   : ["ヲ", "J"],
	"-.-"    : ["ワ", "K"],
	".-.."   : ["カ", "L"],
	"--"     : ["ヨ", "M"],
	"-."     : ["タ", "N"],
	"---"    : ["レ", "O"],
	"---."   : ["ソ"],
	".--."   : ["ツ", "P"],
	"--.-"   : ["ネ", "Q"],
	".-."    : ["ナ", "R"],
	"..."    : ["ラ", "S"],
	"-"      : ["ム", "T"],
	"..-"    : ["ウ", "U"],
	".-..-"  : ["ヰ"],
	"..--"   : ["ノ"],
	".-..."  : ["オ"],
	"...-"   : ["ク", "V"],
	".--"    : ["ヤ", "W"],
	"-..-"   : ["マ", "X"],
	"-.--"   : ["ケ", "Y"],
	"--.."   : ["フ", "Z"],
	"----"   : ["コ"],
	"-.---"  : ["エ"],
	".-.--"  : ["テ"],
	"--.--"  : ["ア"],
	"-.-.-"  : ["サ"],
	"-.-.."  : ["キ"],
	"-..--"  : ["ユ"],
	"-...-"  : ["メ"],
	"..-.-"  : ["ミ"],
	"--.-."  : ["シ"],
	".--.."  : ["ヱ"],
	"--..-"  : ["ヒ"],
	"-..-."  : ["モ"],
	".---."  : ["セ"],
	"---.-"  : ["ス"],
	".-.-."  : ["ン"],
	".."     : ["゛", "I"],
	"..--."  : ["゜"],
	
	// 数字
	".----" : ["1"],
	"..---" : ["2"],
	"...--" : ["3"],
	"....-" : ["4"],
	"....." : ["5"],
	"-...." : ["6"],
	"--..." : ["7"],
	"---.." : ["8"],
	"----." : ["9"],
	"-----" : ["0"]
    },

    // 関数
    // 逆引き
    search: function(val) {
	for (var m in this.table) {
	    for (var i = 0; i < this.table[m].length; i++) {
		if (this.table[m][i] === val) {
		    return m
		}
	    }
	}
	return undefined
    },
    
    // モールス符号→カナ
    morseToKana : function(morse){
	var kana = ""
	for (var i = 0; i < morse.length; i++) {
	    var c = morse[i]
	    if (this.table[c]) { kana += this.table[c][0] + separator }
	}
	return kana
    },
    
    // カナ→モールス符号
    kanaToMorse : function(kana){
	var morse = ""
	for (var i = 0; i < kana.length; i++) {
	    var c = this.search(kana[i])
	    if (c) {
		morse += c + separator
	    }
	}
	return morse
    },

    // モールス符号→アルファベット
    morseToAlpha : function(morse){
	var alpha = ""
	for (var i = 0; i < morse.length; i++) {
	    var c = morse[i]
	    if (this.table[c]) { alpha += this.table[c][1] + separator }
	}
	return alpha
    },
    
    // アルファベット→モールス符号
    alphaToMorse : function(alpha){
	var morse = ""
	for (var i = 0; i <alpha.length; i++) {
	    var c = this.search(alpha[i])
	    if (c) {
		morse += c + separator
	    }
	}
	return morse

    }
}


var args = Environment.GetCommandLineArgs()
var findArgs = function(v){
    for (var i = 0; i < args.length; i++) {
	if (args[i] === v) {
	    return true
	}
    }
    return false
}

if (findArgs("-a")) {
    if (findArgs("-r")) {
	Console.WriteLine(converter.morseToAlpha(args[1]))
    }else {
	Console.WriteLine(converter.alphaToMorse(args[1]))
    }
}else{
    if (findArgs("-r")) {
	Console.WriteLine(converter.morseToKana(args[1]))
    } else {
	Console.WriteLine(converter.kanaToMorse(args[1]))
    }
    
}
