from typing import Optional
def handle_comment(line: str) -> tuple[Optional[str], bool]:
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
        main_out = content.removeprefix('@return').strip()
        line_to_be_added = '/// ' + 'Return ' + main_out[0].lower() + main_out[1:]
    elif (not content.startswith("@")) and len(content) > 1:
        line_to_be_added = line
    
    return line_to_be_added, should_start_new_group

def handle_method_declaration(line: str) -> tuple[Optional[str], bool]:
    return line.removesuffix(';'), True

def handle_inline_defined_method(line: str) -> tuple[Optional[str], bool]:
    return line, True

def handle_stray_curly(line: str) -> tuple[Optional[str], bool]:
    return None, False

def handle_field(line: str) -> tuple[Optional[str], bool]:
    return line.removesuffix(";"), True

def handle_misc(line: str) -> tuple[Optional[str], bool]:
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
        elif line.endswith(');') or line.endswith('const;'):
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

def find_private_and_public_points(rawCode: list[str]) -> tuple[Optional[int], Optional[int]]:
    '''Return the positions of the private and pulic labels, in that order'''
    private = None
    public = None

    for index in range(len(rawCode)):
        rawLine = rawCode[index]
        line = rawLine.strip()
        if line == "private:":
            private = index
        elif line == "public:":
            public = index

    return private, public

def generate_final_output_lines_from_group(group: list[str]) -> list[str]:
    output_lines = []

    for index in range(len(group)):
        line = group[index]
        
        if index == 0:
            output_lines.append('- ' + line)
        else:
            output_lines.append('  '+line)
        
    return output_lines

def get_private_and_public_ranges(private_pos, public_pos, last_pos):
    private_start=  None
    private_end = None
    public_start = None
    public_end = None

    if private_pos is not None and public_pos is not None:
        if public_pos < private_pos:
            public_start = public_pos + 1
            public_end  = private_pos - 1
            private_start = private_pos+1
            private_end = last_pos
        else:
            private_start = private_pos + 1
            private_end  = public_pos - 1
            public_start = public_pos+1
            public_end = last_pos
    elif public_pos is None:
        private_start = private_pos
        private_end = last_pos
    else:
        public_start = public_pos
        public_end = last_pos

    return (private_start, private_end), (public_start, public_end)

def write_final_output(output:list[str], output_groups: list[list[str]]):
    n = len(output_groups)
    for index in range(n):
        group = output_groups[index]
        output.extend(group)

        if index  < n -1:
            output.append("")


def convert_raw_to_tldr_frame(rawCode: list[str]) -> list[str]:
    private_pos, public_pos = find_private_and_public_points(rawCode)
    private_bounds, public_bounds = get_private_and_public_ranges(private_pos, public_pos, len(rawCode)-1)
    private_groups = None
    public_groups = None

    if private_bounds[0] is not None:
        private_groups = group_code(rawCode[private_bounds[0]:private_bounds[1]+1])

    if public_bounds[0] is not None:
        public_groups = group_code(rawCode[public_bounds[0]:public_bounds[1]+1])

    private_output_groups = None
    public_output_groups = None


    if private_groups is not None:
        private_output_groups = [generate_final_output_lines_from_group(group) for group in private_groups]

    if public_groups is not None:
        public_output_groups = [generate_final_output_lines_from_group(group) for group in public_groups]

    output = []

    if private_output_groups is not None:
        output.append("Private:")
        write_final_output(output, private_output_groups)
    
    if public_output_groups is not None:
        if private_output_groups is not None:
            output.append("")
        output.append("Public:")
        write_final_output(output, public_output_groups)

    return output
    
file_name = "class_skeleton.txt"

with open(file_name) as file:
    output = convert_raw_to_tldr_frame(file.readlines())
    print(*output, sep="\n")