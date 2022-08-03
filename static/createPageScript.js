var chapterIndex = 0;

function addFields() {
    // Get the element where the inputs will be added to
    const container = document.getElementById('chapters');
    // Create an <input> element, set its type and name attributes
    const titleLabel = document.createElement('label');
    const title = document.createElement('input');
    const textLabel = document.createElement('label');
    const text = document.createElement('textarea');
    const imageLabel = document.createElement('label');
    const image = document.createElement('select');
    const opt1 = document.createElement('option');
    const opt2 = document.createElement('option');
    const opt3 = document.createElement('option');
    opt1.value = "rain.jpg";
    opt1.innerText = "Rain";
    opt2.value = "sunset.png";
    opt2.innerText = "Sunset";
    opt3.value = "night_sky.png";
    opt3.innerText = "Night Sky";
    image.appendChild(opt1);
    image.appendChild(opt2);
    image.appendChild(opt3);
    image.type = 'radio';
    title.name = 'titles[' + chapterIndex + ']';
    text.name = 'chapterText[' + chapterIndex + ']';
    image.name = 'images[' + chapterIndex + ']';
    titleLabel.for = 'titles[' + chapterIndex + ']';
    titleLabel.innerText = "Chapter Title";
    textLabel.for = 'chapterText[' + chapterIndex + ']';
    textLabel.innerText = "Chapter Text";
    imageLabel.for = 'images[' + chapterIndex + ']';
    imageLabel.innerText = "Image Backdrop";
    container.appendChild(titleLabel);
    container.appendChild(title);
    container.appendChild(textLabel);
    container.appendChild(text);
    container.appendChild(imageLabel);
    container.appendChild(image);
    // Append a line break
    container.appendChild(document.createElement('br'));
    chapterIndex += 1;
}

function mapFormToArray(formObj) {
    var newObj = {};
    for (const [key, value] of Object.entries(formObj)) {
        if (key[key.length - 3] === '[' && key[key.length - 1] === ']') {
            if (!newObj[key.slice(0, -3)]) newObj[key.slice(0, -3)] = [];
            newObj[key.slice(0, -3)][key[key.length - 2]] = value;
        } else {
            newObj[key] = value;
        }
    }
    return newObj
}

var form = document.getElementById('storyForm');
form.onsubmit = function (event) {
    var xhr = new XMLHttpRequest();
    var formData = new FormData(form);
    //open the request
    xhr.open('POST', 'addStory')
    xhr.setRequestHeader("Content-Type", "application/json");

    //send the form data
    xhr.send(JSON.stringify(mapFormToArray(Object.fromEntries(formData))));

    xhr.onreadystatechange = function () {
        if (xhr.readyState == XMLHttpRequest.DONE) {
            form.reset(); //reset form after AJAX success or do something else
        }
    }
    //Fail the onsubmit to avoid page refresh.
    return false;
}
//        <input type="text" id="storytitle" name="fname"><br>
//        <label for="chapter">Chapter: </label><br>
//        <input type="text" id="chapter" name="chapter"></input>
