import wave, struct

def get_sine(period):
	print [int(255 * sin(pi * i / period)) for i in xrange(period)]


waveFile = wave.open('so_strangely.wav', 'r')

length = waveFile.getnframes()
w = []
for i in range(0,length):
	print i
	waveData = waveFile.readframes(1)
	data = struct.unpack("<h", waveData)
	w.append(int(data[0]))

print w