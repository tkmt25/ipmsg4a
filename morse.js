import System;
var separator = " "
var converter = {
    // �����
    table: {
	".-"     : ["�C", "A"],
	".-.-"   : ["��"],
	"-..."   : ["�n", "B"],
	"-.-."   : ["�j", "C"],
	"-.."    : ["�z", "D"],
	"."      : ["�w", "E"],
	"..-.."  : ["�g"],
	"..-."   : ["�`", "F"],
	"--."    : ["��", "G"],
	"...."   : ["�k", "H"],
	"-.--."  : ["��"],
	".---"   : ["��", "J"],
	"-.-"    : ["��", "K"],
	".-.."   : ["�J", "L"],
	"--"     : ["��", "M"],
	"-."     : ["�^", "N"],
	"---"    : ["��", "O"],
	"---."   : ["�\"],
	".--."   : ["�c", "P"],
	"--.-"   : ["�l", "Q"],
	".-."    : ["�i", "R"],
	"..."    : ["��", "S"],
	"-"      : ["��", "T"],
	"..-"    : ["�E", "U"],
	".-..-"  : ["��"],
	"..--"   : ["�m"],
	".-..."  : ["�I"],
	"...-"   : ["�N", "V"],
	".--"    : ["��", "W"],
	"-..-"   : ["�}", "X"],
	"-.--"   : ["�P", "Y"],
	"--.."   : ["�t", "Z"],
	"----"   : ["�R"],
	"-.---"  : ["�G"],
	".-.--"  : ["�e"],
	"--.--"  : ["�A"],
	"-.-.-"  : ["�T"],
	"-.-.."  : ["�L"],
	"-..--"  : ["��"],
	"-...-"  : ["��"],
	"..-.-"  : ["�~"],
	"--.-."  : ["�V"],
	".--.."  : ["��"],
	"--..-"  : ["�q"],
	"-..-."  : ["��"],
	".---."  : ["�Z"],
	"---.-"  : ["�X"],
	".-.-."  : ["��"],
	".."     : ["�J", "I"],
	"..--."  : ["�K"],
	
	// ����
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

    // �֐�
    // �t����
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
    
    // ���[���X�������J�i
    morseToKana : function(morse){
	var kana = ""
	for (var i = 0; i < morse.length; i++) {
	    var c = morse[i]
	    if (this.table[c]) { kana += this.table[c][0] + separator }
	}
	return kana
    },
    
    // �J�i�����[���X����
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

    // ���[���X�������A���t�@�x�b�g
    morseToAlpha : function(morse){
	var alpha = ""
	for (var i = 0; i < morse.length; i++) {
	    var c = morse[i]
	    if (this.table[c]) { alpha += this.table[c][1] + separator }
	}
	return alpha
    },
    
    // �A���t�@�x�b�g�����[���X����
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
