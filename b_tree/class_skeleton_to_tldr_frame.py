def handle_comment(line: str) -> tuple[str | None, bool]:
    content = line.removeprefix('///').strip()
    space_split_parts = content.split(' ')
    should_start_new_group = False
    line_to_be_added = None

    if content.startswith('@param') and len(space_split_parts) > 2:
        # param contains description
        line_to_be_added = line
    elif content.startswith('@brief') and len(space_split_parts) > 1:
        line_to_be_added = '/// ' + content.removeprefix('@brief').strip()
    elif content.startswith('@return') and len(space_split_parts) > 1:
        line_to_be_added = '/// ' + content.removeprefix('@return').strip()
    elif len(content) > 1:
        line_to_be_added = line
    
    return line_to_be_added, should_start_new_group

def handle_method_declaration(line: str) -> tuple[str | None, bool]:
    return line.removesuffix(';'), True

def handle_inline_defined_method(line: str) -> tuple[str | None, bool]:
    return line, True

def handle_stray_curly(line: str) -> tuple[str | None, bool]:
    return None, False

def handle_field(line: str) -> tuple[str | None, bool]:
    return line, True

def handle_misc(line: str) -> tuple[str | None, bool]:
    return None, False

def group_code(rawCode: list[str]) -> list[list[str]]:
    '''Group code elements and their descriptions together'''

    # any line will be one of the following cases:
    #   - blank line (ignore)
    #   - comment. Starts with '///'
    #       - followed by '@param' (ignore if there is no description after the parameter name)
    #       - followed by '@brief' (remove '@brief' and add the rest to group)
    #       - followed by '@return' (remove '@' and add the rest to group if not empty)
    #       - followed by empty space (ignore)
    #       - followed by text without annotation
    #   - method declaration. Ends with ');' or 'const;' (add to current group and start a new group)
    #   - inline defined method. Ends with ')' (add to current group and start a new group)
    #   - stray curly brace. Ends with '{', '}' or '};' (ignore)
    #   - field/property. Ends with just ';' (add to current group and start new group)
    #   - anything else (ignore)

    current_group:list[str]=[]
    groups:list[list[str]] = []

    for rawLine in rawCode:
        line = rawLine.strip()
        should_start_new_group = False
        line_to_be_added = None

        if line.startswith('///'):
            line_to_be_added, should_start_new_group = handle_comment(line)
        elif line.endswith('};') or line.endswith('const;'):
            line_to_be_added, should_start_new_group = handle_method_declaration(line)
        elif line.endswith(')'):
            line_to_be_added, should_start_new_group = handle_inline_defined_method(line)
        elif line.endswith('{') or line.endswith('}') or line.endswith('};'):
            line_to_be_added, should_start_new_group = handle_stray_curly(line)
        elif  line.endswith(';'):
            line_to_be_added, should_start_new_group = handle_field(line)
        else:
            line_to_be_added, should_start_new_group = handle_misc(line)

        if line_to_be_added is not None:
            current_group.append(line_to_be_added)
        
        if should_start_new_group:
            groups.append(current_group)
            current_group = []

    return groups