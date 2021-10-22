// Palette array of 256 colors
var palette = [];

// (...)

// Generate palette
function generatePalette() {
    // Calculate a gradient
    var roffset = 24;
    var goffset = 16;
    var boffset = 0;
    for (var i=0; i<256; i++) {
        palette[i] = { r:roffset, g:goffset, b:boffset};

        if (i < 64) {
            roffset += 3;
        } else if (i<128) {
            goffset += 3;
        } else if (i<192) {
            boffset += 3;
        }
    }
}

generatePalette();
console.log(JSON.stringify(palette));