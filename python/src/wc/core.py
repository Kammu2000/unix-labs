from src.constants import BUFFER_SIZE, WHITESPACE_BYTES


def wc(file_buffer):
    lines_count = words_count = characters_count = bytes_count = 0
    in_word = False

    last_byte = None

    while chunk := file_buffer.read(BUFFER_SIZE):
        bytes_count += len(chunk)

        for byte in chunk:
            last_byte = byte

            if byte & 0b11000000 != 0b10000000:
                characters_count += 1

            if byte == ord("\n"):
                lines_count += 1

            if byte in WHITESPACE_BYTES:
                in_word = False
            elif not in_word:
                words_count += 1
                in_word = True

    if bytes_count > 0 and last_byte != ord("\n"):
        lines_count += 1

    return lines_count, words_count, characters_count, bytes_count
