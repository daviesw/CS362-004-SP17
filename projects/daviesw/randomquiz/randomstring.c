I implemented inputChar() by first creating an array of 9 chars, each of which
is one of the characters that would change the state variable. Then I use rand()
and the % operator to randomly select a number within the range of indices in
that array. The char at that index is returned. inputString works by creating an
array of every letter in reset and then allocates enough memory to a pointer
for the word reset (with the null terminator at the end). Then a loop that
iterates 5 times uses rand() and the % operator to find an integer within the
range of indices in that array. The char at that index is put at the index equal
to the loop counter in the array to which memory was allocated. A null
terminator is added at the last available index in the newly made string and
it is returned as a pointer. With c always being one of the characters that
change state and s always being a string comprised only of letters found in
reset, state eventually becomes 9 and the string is eventually "reset." This
yields the error message.
