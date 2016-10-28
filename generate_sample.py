from math import sin, pi
import itertools

SAMPLE_FREQ = 25000 #Hz
C = 261.6 #Hz
E = 329.6 #Hz
G = 392.0 #Hz

def single_sinus_cycle(period):
    return (int(255 * sin(pi * i / period)) for i in xrange(period))

def sinus(duration, frequency):
    """
    Args:
        duration (float): The duration, in seconds
        frequency (float): The frequency, in Hz
    """
    period = int(SAMPLE_FREQ / frequency)
    repeats = int(duration * frequency)
    return itertools.chain.from_iterable(
        single_sinus_cycle(period) for i in xrange(repeats)
    )

if __name__ == '__main__':
    composition = itertools.chain(
        sinus(0.1, C),
        sinus(0.1, E),
        sinus(0.1, G),
    )
    with open('output.txt', 'w') as f:
        f.write(', '.join(str(s) for s in composition))
