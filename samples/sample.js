const virtualcam = require('../');

const width = 1280;
const height = 720;
const fps = 30;
const delay = 10;

function sleep(secs) {
    return new Promise((resolve) => {
      setTimeout(resolve, secs / 1000);
    });
}

async function main() {
    virtualcam.start(width, height, fps, delay);
    console.log(`virtual cam output started (${width}x${height} @ ${fps}fps)`);
    try {
        let i = 0;
        while (true) {

            const frame = new Uint8Array(height * width * 4);
            frame.fill(i % 255);

            // Send to the virtual cam.
            virtualcam.send(i, frame);

            // Wait until it's time to prepare the next frame.
            sleep(1/fps);

            i += 1;
        }
    } finally {
        virtualcam.stop();
        console.log('virtual cam output stopped');
    }
}

main();
