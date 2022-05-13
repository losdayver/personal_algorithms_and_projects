class Line:
    def __init__(self, point1, point2, length):
        self.point1 = point1
        self.point2 = point2
        self.length = length

    def __str__(self):
        return f'({self.point1}, {self.point2}, {self.length})'

graph = [
Line(1,2,7),
Line(1,4,5),
Line(2,3,8),
Line(2,5,7),
Line(2,4,9),
Line(3,5,5),
Line(4,5,15),
Line(4,6,6),
Line(5,6,8),
Line(5,7,9),
Line(6,7,11),
]

colors = [i+1 for i in range(8)]
tree = []

def propagate_change_color(line):
    color1 = colors[line.point1]
    color2 = colors[line.point2]

    colors[line.point1] = color1
    colors[line.point2] = color1

    end_flag = False
    while not end_flag:
        end_flag = True
        for l in graph:
            if (colors[l.point1] == color1 and colors[l.point2] == color2)\
                    or (colors[l.point2] == color1 and colors[l.point1] == color2):
                colors[l.point1] = color1
                colors[l.point2] = color1
                end_flag = False


end_flag = False
while not end_flag:
    end_flag = True
    min = -1
    min_index = -1
    min_line = None

    for i, line in enumerate(graph):
        same_color = colors[line.point1] == colors[line.point2]

        if (min == -1 or line.length < min) and not same_color:
            min = line.length
            min_index = i
            min_line = line

            end_flag = False

    if not end_flag: #выполняется, если ребро минимально и цвета вершин разные
        tree.append(min_line)
        propagate_change_color(min_line)

print(colors)
for l in tree:
    print(l)
