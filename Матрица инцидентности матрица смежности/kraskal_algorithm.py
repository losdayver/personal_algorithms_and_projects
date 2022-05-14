import pygame as pg
import random
import math
random.seed(6)

resolution = [800, 600]
margin = 100

class Point:
    points = []
    _id_counter = 0

    def __init__(self):
        self.screen_location = [
            random.randint(margin, resolution[0]),
            random.randint(margin, resolution[1])
        ]

        self.id = Point._id_counter

        self.color = Point._id_counter

        self.points.append(self)

        Point._id_counter += 1
Point.points = [Point() for x in range(7)]

class Line:
    lines = []
    def __init__(self, point1:Point, point2:Point, length):
        self.point1 = Point.points[point1]
        self.point2 = Point.points[point2]
        self.length = length
        self.lines.append(self)

    def __str__(self):
        return f'({self.point1}, {self.point2}, {self.length})'

Line(0,1,7)
Line(0,3,5)
Line(1,2,8)
Line(1,4,7)
Line(1,3,9)
Line(2,4,5)
Line(3,4,15)
Line(3,5,6)
Line(4,5,8)
Line(4,6,9)
Line(5,6,11)

tree = []

def propagate_change_color(line:Line):
    color1 = line.point1.color
    color2 = line.point2.color

    line.point1.color = color1
    line.point2.color = color1

    end_flag = False
    while not end_flag:
        end_flag = True
        for l in Line.lines:
            if (l.point1.color == color1 and l.point2.color == color2)\
                    or (l.point1.color == color2 and l.point2.color == color1):
                l.point1.color = color1
                l.point2.color = color1
                end_flag = False


end_flag = False
while not end_flag:
    end_flag = True
    min = -1
    min_index = -1
    min_line = None

    for i, line in enumerate(Line.lines):
        same_color = line.point1.color == line.point2.color

        if (min == -1 or line.length < min) and not same_color:
            min = line.length
            min_index = i
            min_line = line

            end_flag = False

    if not end_flag: #выполняется, если ребро минимально и цвета вершин разные
        tree.append(min_line)
        propagate_change_color(min_line)

pg.init()
screen = pg.display.set_mode(resolution)

my_font = pg.font.SysFont('Comic Sans MS', 30)

for l in Line.lines:
    pg.draw.line(screen, [0,255,0], l.point1.screen_location, l.point2.screen_location, 3)

for l in tree:
    pg.draw.line(screen, [255,0,0], l.point1.screen_location, l.point2.screen_location,2)

for p in Point.points:
    pg.draw.circle(screen, [0,255,0], p.screen_location, 10)
    text_surface = my_font.render(f'point: {p.id}', False, (0, 0, 255))
    screen.blit(text_surface, [p.screen_location[0], p.screen_location[1]])

pg.display.flip()

locked_on_point:Point = None

while 1:

    for e in pg.event.get():
        if e.type == pg.QUIT:
            quit()

    if pg.mouse.get_pressed(3)[0]:

        if locked_on_point == None:
            for p in Point.points:
                if math.sqrt((p.screen_location[0]-pg.mouse.get_pos()[0])**2+(p.screen_location[1]-pg.mouse.get_pos()[1])**2) < 10:
                    locked_on_point = p
                    break
        else: locked_on_point.screen_location = pg.mouse.get_pos()

        screen.fill([0, 0, 0])

        for l in Line.lines:
            pg.draw.line(screen, [0, 255, 0], l.point1.screen_location, l.point2.screen_location, 3)

        for l in tree:
            pg.draw.line(screen, [255, 0, 0], l.point1.screen_location, l.point2.screen_location, 2)

        for p in Point.points:
            pg.draw.circle(screen, [0, 255, 0], p.screen_location, 10)
            text_surface = my_font.render(f'point: {p.id}', False, (0, 0, 255))
            screen.blit(text_surface, [p.screen_location[0], p.screen_location[1]])

        pg.display.flip()

    else:
        locked_on_point = None
