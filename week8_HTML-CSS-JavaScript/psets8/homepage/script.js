function changeBackgroundColor() {
    let backgrounds = document.querySelectorAll(".color")
    let redRand = Math.floor(Math.random() * 256)
    let greenRand = Math.floor(Math.random() * 256)
    let blueRand = Math.floor(Math.random() * 256)
    for (let i = 0; i < backgrounds.length; i++) {
        backgrounds[i].style.backgroundColor = `rgb(${redRand}, ${greenRand}, ${blueRand})`
    }
}
