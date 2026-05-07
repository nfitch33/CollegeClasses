Overview

This project implements a voice cloning system using three main components:

Encoder – learns speaker embeddings from WAV recordings.

Synthesizer – converts text embeddings into mel-spectrograms.

Vocoder – converts mel-spectrograms into audio waveforms.

Once trained, the system can synthesize speech in the voice of the speaker using new text inputs.

Folder Structure
VoiceCloneProject/
│
├─ data/
│   ├─ wavs/               # Your training WAV recordings
│   ├─ metadata.csv        # Optional transcripts for TTS training
│   └─ mels/               # Generated mel-spectrograms (optional)
│
├─ models/
│   ├─ encoder/
│   ├─ synthesizer/
│   └─ vocoder/
│
├─ outputs/                # Generated WAV files
│
├─ train_encoder.py
├─ train_synthesizer.py
├─ train_vocoder.py
├─ infer.py
└─ README.md

Setup

Install Python 3.8+

Optional: Create a virtual environment

python -m venv venv
# Activate it
# Windows
venv\Scripts\activate
# Mac/Linux
source venv/bin/activate


Install dependencies

pip install torch librosa scipy numpy pandas


Prepare your data

Record WAV files of your voice and store in data/wavs/

Optional: create metadata.csv with columns [filename|transcript] for synthesizer training

Training
1. Encoder
python train_encoder.py


Trains the speaker encoder using your WAV files.

Checkpoints are saved to models/encoder/encoder.pt.

Supports epochs and shuffling to improve learning.

2. Synthesizer
python train_synthesizer.py


Converts speaker embeddings + text to mel-spectrograms.

Checkpoints are saved to models/synthesizer/synth.pt.

3. Vocoder
python train_vocoder.py


Converts mel-spectrograms into audio waveforms.

Checkpoints are saved to models/vocoder/vocoder.pt.

Tip: For small datasets, monitor for overfitting. Shuffle your data and adjust epochs accordingly.

Inference

Use infer.py to synthesize speech from any new text.

Single or multiple sentences

Enter multiple sentences separated by | to synthesize them in order.

The entire audio will be saved as one WAV file.

python infer.py


Example input:

Hello, this is my cloned voice. | This is the second sentence. | And finally the last one.


Output file: outputs/full_output.wav




QUICK START
# 1. Navigate to project folder
cd path/to/VoiceCloneProject

# 2. (Optional) Create and activate a virtual environment
python -m venv venv
# Windows
venv\Scripts\activate
# Mac/Linux
source venv/bin/activate

# 3. Install dependencies
pip install torch librosa scipy numpy pandas

# 4. Train the encoder (speaker embeddings)
python train_encoder.py

# 5. Train the synthesizer (text → mel)
python train_synthesizer.py

# 6. Train the vocoder (mel → waveform)
python train_vocoder.py

# 7. Run inference (enter sentences separated by '|')
python infer.py
# Example input:
# Hello, this is my cloned voice. | This is the second sentence. | And finally the last one.
# Output will be saved as outputs/full_output.wav



RUNNING CODE
# Train the encoder using your recorded WAV files
python train_encoder.py
# Train the synthesizer to convert text + embeddings to mel-spectrograms
python train_synthesizer.py
# Train vocoder to convert mel-spectrograms into audio waveform
python train_vocoder.py
# Run the inference script
python infer.py   (Separate Sentences with '|')

EXAMPLE:
Hello, this is my cloned voice. | This is the second sentence. | And finally the last one.
