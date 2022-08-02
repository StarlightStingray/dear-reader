console.log('Hello, Drogon.');

function addFields() {
	// Get the element where the inputs will be added to
	const container = document.getElementById('chapters');
	// Create an <input> element, set its type and name attributes
    const title = document.createElement('input');
    const text = document.createElement('textarea');
    const image = document.createElement('input');
	input.type = 'text';
    image.type = 'radio';
    title.name = 'titles[]';
    text.name = 'chapterText[]';
    image.name = 'backdrop[]';
    container.appendChild(title);
    container.appendChild(text);
    container.appendChild(image);
	// Append a line break
	container.appendChild(document.createElement('br'));
}

//        <input type="text" id="storytitle" name="fname"><br>
//        <label for="chapter">Chapter: </label><br>
//        <input type="text" id="chapter" name="chapter"></input>
