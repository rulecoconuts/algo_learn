def reverse_words(s: str) -> str:
    n = len(s)

    parts = [part[::-1] for part in s.split(" ")]

    return " ".join(parts)
