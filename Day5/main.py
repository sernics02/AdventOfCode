def convert(sources: set, mapping_section):
    destinations = set()
    for source in sources:
        for mapping in mapping_section:
            d, s, r = mapping
            offset = d - s
            if s <= source < s + r:
                destinations.add(source + offset)
                break
        else:
            destinations.add(source)

    return destinations


def puzzle1(input_file):
    with open(input_file) as file:
        data = file.read().strip().split('\n\n')
    seeds = {int(number) for number in data[0].split(' ')[1:]}
    mapping_sections = [section.splitlines()[1:] for section in data[1:]]
    mapping_sections = [{tuple(int(number) for number in mapping_str.split(' '))
                         for mapping_str in section} for section in mapping_sections]
    # print(*mapping_sections, sep='\n')
    sources = seeds
    for section in mapping_sections:
        sources = convert(sources, section)

    return min(sources)


def convert_range(sources: set, mapping_section):
    destinations = set()
    while sources:
        source_start, source_end = sources.pop()
        for mapping in mapping_section:
            d, s, r = mapping
            offset = d - s
            if s <= source_start <= source_end < s + r:
                destinations.add((source_start + offset, source_end + offset))
                break
            elif s <= source_start < s + r <= source_end:
                destinations.add((source_start + offset, s + r - 1 + offset))
                sources.add((s + r, source_end))
                break
            elif source_start < s <= source_end < s + r:
                destinations.add((s + offset, source_end + offset))
                sources.add((source_start, s - 1))
                break
        else:
            destinations.add((source_start, source_end))

    return destinations


def puzzle2(input_file):
    with open(input_file) as file:
        data = file.read().strip().split('\n\n')
    seeds_str = data[0].split(' ')[1:]
    seeds = {(int(seeds_str[i]), int(seeds_str[i]) + int(seeds_str[i + 1]) - 1)
             for i in range(0, len(seeds_str), 2)}
    mapping_sections = [section.splitlines()[1:] for section in data[1:]]
    mapping_sections = [{tuple(int(number) for number in mapping_str.split(' '))
                         for mapping_str in section} for section in mapping_sections]
    # print(*mapping_sections, sep='\n')
    source_ranges = seeds
    for section in mapping_sections:
        source_ranges = convert_range(source_ranges, section)

    return min(range_[0] for range_ in source_ranges)


print('Day #5, part one:', puzzle1('./input.txt'))
print('Day #5, part two:', puzzle2('./input.txt'))
