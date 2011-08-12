/* This isn't a secure hash function.  On the other hand, if you can
 * compute a hash collision for this, you don't really need to do the
 * tutorials. */

function hash(a) {
    var r = 5381;

    for (var i = 0; i < a.length; i += 1) {
        r = (((r << 5) + r) + a.charCodeAt(i)) & 0xffff;
    }
    return r;
}

function ans(id, answer) {
    var p = document.getElementById(id);
    var i = document.createElement("input");
    var g = document.createElement("span");

    var d = document.getElementById("debug");

    function chk() {
        var h = hash(i.value);

        if (d) {
            d.innerHTML = h;
        }

        if (h == answer) {
            g.innerHTML = "Correct!";
            g.style.color = "#00cc00";
        } else {
            g.innerHTML = "Try again.";
            g.style.color = "#ff4444";
        }
    }

    p.innerHTML = "Answer:";

    p.appendChild(i);
    i.onchange = chk;

    var s = document.createElement("input");
    p.appendChild(s);
    s.type = "submit";
    s.value = "check";
    s.onclick = "chk();";

    p.appendChild(g);

}
