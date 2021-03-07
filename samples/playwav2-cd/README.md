# Play WAV files off a CD

Explores creating and burning a CD image using CDGenPS2, reading files off of it, and playing back a song stored on the disk.

## Running the disk

* Have a wav file named `song_22k.wav` in the project directory. The wav file must be dual-channel with a sample rate of 22050Hz.
* Open CDGenPS2 and copy in the `SYSTEM.CNF`, `playwav2.elf`, `audsrv.irx`, and `song_22k.wav` files.
* Click "Save Image" and save it as an .iso file.
* Run the iso through your method of choice (PS2 hardware, emulator, etc).
* The song should start playing on a black screen.
* After a short while, the disk will end and you will be thrown in the "Red error screen". This is expected as the program will have finished running.
