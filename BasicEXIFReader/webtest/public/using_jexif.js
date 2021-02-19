//WunderVision 2020

//Some Simple Code that demonstrates, retrieving a file from the server
//Writing it to the MEMFS, then passing that path to the constructor of
//the C++ EXIF Class.

const img = document.getElementById("imgInput");
const output = document.getElementById("tagOutput");
async function test(){
    var file = await fetch('/testpic.jpg')
    if(file.ok){
       file.arrayBuffer().then(function(buffer){
            console.log('Decoding File');
            FS.writeFile("uploaded.jpg", new Uint8Array(buffer));
            console.log('Written to MEMFS .. Creating Class');
            var exifData = new Module.EXIF('uploaded.jpg');
            var orientation = exifData.getTag(274); 
            var model = exifData.getTag(272);
            var description = exifData.getTag(270);  
            output.innerHTML = "Orienation: " + orienation + "<br>" +
                                "Model: " + model + "<br>" + 
                                "Description: " + description + "<br>";
            exifData.delete();
            img.src = '/testpic.jpg';
       });

    }

}

var Module = {
    onRuntimeInitialized: test
};
