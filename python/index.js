var editor;

function outf(text) { 
    var mypre = document.getElementById("stdout"); 
    mypre.innerHTML = mypre.innerHTML + text; 
} 

function builtinRead(x) {
    if (Sk.builtinFiles === undefined || Sk.builtinFiles["files"][x] === undefined)
            throw "File not found: '" + x + "'";
    return Sk.builtinFiles["files"][x];
}
// Here's everything you need to run a python program in skulpt
// grab the code from your textarea
// get a reference to your pre element for output
// configure the output function
// call Sk.importMainWithBody()
function runit() {
    document.getElementById("stdout").textContent = "";

    var prog = editor.getValue();

    var myPromise = Sk.misceval.asyncToPromise(function() {
        return Sk.importMainWithBody("<stdin>", false, prog, true);
    });
    myPromise.then(function(mod) {
        console.log('success');
   },
        function(err) {
        console.log(err.toString());
    });
}

function init() {
    document.body.style.maxWidth="100%";

    editor = ace.edit("editor");
//    editor.setTheme("ace/theme/twilight");
    editor.session.setMode("ace/mode/python");

    Sk.pre = "stdout";
    Sk.configure({output:outf, read:builtinRead});
    if (! Sk.TurtleGraphics) {
        Sk.TurtleGraphics = {};
    }
    Sk.TurtleGraphics.target = "turtlepen";
}

window.addEventListener('load', init);
