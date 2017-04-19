# Midi Experiments

# Install rtmidi

# Input Ports

Sample code:

```

try {

    MidiInputPort in_port(0);
    in_port.listen();
    std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
    char input;
    std::cin.get(input);

} catch ( RtMidiError &error ) {
  error.printMessage();
} catch (...) {
    std::cout << "this didn't work";
}

```
