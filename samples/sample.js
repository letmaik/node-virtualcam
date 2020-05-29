const virtualcam = require('../');

const width = 1280;
const height = 720;
const fps = 30;
const delay = 10;
const frameMs = 1/fps * 1000;

let timerId;

// Catch ctrl-c.
process.on('SIGINT', () => {
    clearInterval(timerId);
    virtualcam.stop();
    console.log('virtual cam output stopped');
    process.exit(1);
});

virtualcam.start(width, height, fps, delay);
console.log(`virtual cam output started (${width}x${height} @ ${fps}fps)`);

let i = 0;
timerId = setInterval(() => {
    const frame = new Uint8Array(height * width * 4);
    frame.fill(i % 255);
    virtualcam.send(i, frame);
    i += 1;
}, frameMs);
