import System;
import System.IO;

var source = File.ReadAllText("test.cpp");

var ret = source.match(/aplog_error[\s\S]*?;/g) 

for (var i = 0; i < ret.length; i++) {
    var r2 = ret[i].match(/aplog_error[\s\S]*?\((.*?),[\s\S]*?(.*?)\);/)
    for (var j = 1; j < r2.length; j++) {
	Console.WriteLine(r2[j].Trim())
    }
    //Console.WriteLine(ret[i])
}
