import tkinter as tk
import math


class NewCanvas(tk.Canvas):
    def __init__(self, master, h_line_width=1, v_line_width=1, radius=2, **kwargs):
        tk.Canvas.__init__(self, master, **kwargs)
        self.h_line_width = h_line_width
        self.v_line_width = v_line_width
        self.radius = radius

    def h_line(self, x, y, l):
        self.create_line(x, y, x + l, y, width=self.h_line_width)

    def v_line(self, x, y, l):
        self.create_line(x, y, x, y + l, width=self.v_line_width)

    def h_segment(self, x, y, l):
        self.h_line(x, y, l)
        self.create_oval(x - self.radius, y - self.radius, x + self.radius, y + self.radius, fill='black')
        self.create_oval(x + l - self.radius, y - self.radius, x + l + self.radius, y + self.radius, fill='black')

    def v_segment(self, x, y, l):
        self.v_line(x, y, l)
        self.create_oval(x - self.radius, y - self.radius, x + self.radius, y + self.radius, fill='black')
        self.create_oval(x - self.radius, y + l - self.radius, x + self.radius, y + l + self.radius, fill='black')


class OddEvenMerger:
    def __init__(self, index):
        self.size = len(index)
        self.index = index
        if self.size > 2:
            sub_index1, sub_index2 = [], []
            for i, item in enumerate(index):
                if i&1:
                    sub_index2.append(item)
                else:
                    sub_index1.append(item)
            self.sub_merger1 = OddEvenMerger(sub_index1)
            self.sub_merger2 = OddEvenMerger(sub_index2)

    def v_lines(self):
        if self.size <= 1:
            return 0
        elif self.size == 2:
            return 1
        else:
            return self.sub_merger2.v_lines() + self.sub_merger1.v_lines() + 1

    def draw(self, cvs, cur_x, h_scale, w_scale, h_space_up, w_space_up, tot_size):
        if self.size <= 1:
            return cur_x
        elif self.size == 2:
            idx1, idx2 = self.index[0], self.index[1]
            cur_y = h_space_up + (idx1 - 1) * h_scale
            delta_y = (idx2 - idx1) * h_scale
            cvs.v_segment(cur_x, cur_y, delta_y)
            return cur_x
        else:
            n = int(self.size / 2)
            m = int(tot_size / self.size)
            self.sub_merger1.draw(cvs, cur_x, h_scale, w_scale, h_space_up, w_space_up, tot_size)
            cur_x = self.sub_merger2.draw(cvs, cur_x + m * w_scale, h_scale, w_scale, h_space_up, w_space_up, tot_size)
            cur_x = cur_x + m * w_scale
            for k in range(1, n):
                idx1, idx2 = self.index[2 * k - 1], self.index[2 * k]
                cur_y = h_space_up + (idx1 - 1) * h_scale
                delta_y = (idx2 - idx1) * h_scale
                cvs.v_segment(cur_x, cur_y, delta_y)
            return cur_x

class Sorter:
    def __init__(self, index):
        self.size = len(index)
        self.index = index
        if self.size > 1:
            sub_index1, sub_index2 = [], []
            for i, item in enumerate(index):
                if i < self.size / 2:
                    sub_index1.append(item)
                else:
                    sub_index2.append(item)
            self.sub_sorter1 = Sorter(sub_index1)
            self.sub_sorter2 = Sorter(sub_index2)
            self.merger = OddEvenMerger(index)

    def v_lines(self):
        return self.sub_sorter1.v_lines() + self.merger.v_lines() if self.size > 1 else 0

    def draw(self, cvs, cur_x, h_scale, w_scale, h_space_up, w_space_up, tot_size):
        if self.size > 1:
            m = int(tot_size / self.size)
            self.sub_sorter1.draw(cvs, cur_x, h_scale, w_scale, h_space_up, w_space_up, tot_size)
            self.sub_sorter2.draw(cvs, cur_x, h_scale, w_scale, h_space_up, w_space_up, tot_size)
            cur_x = cur_x + self.sub_sorter2.v_lines() * w_scale
            self.merger.draw(cvs, cur_x, h_scale, w_scale, h_space_up, w_space_up, self.size)


if __name__ == '__main__':
    n = int(input('Please enter the number n (should be a power of 2): '))
    log2_n = math.log2(n)
    if int(log2_n) != log2_n:
        print('Error! n should be a power of 2')
        exit(1)
    n = n * 2
    index = range(1, n + 1)
    p = Sorter(index)
    total_v_lines = p.v_lines()

    w_width, w_height = 2000 * 0.6, 1200 * 0.6
    w_space_up, h_space_up = w_width / 20, w_height / 20
    w_scale, h_scale = (w_width - 2 * w_space_up) / (total_v_lines + 1), (w_height - 2 * h_space_up) / (n - 1)

    root = tk.Tk()
    root.title(str(n) + '-input Odd-even Sorting Network')
    cvs = NewCanvas(root, bg='white', width=w_width, height=w_height)
    for i in range(n):
        cvs.h_line(w_space_up, i * h_scale + h_space_up, w_width - 2 * w_space_up)
    p.draw(cvs, w_space_up + w_scale, h_scale, w_scale, h_space_up, w_space_up, n)
    cvs.pack()
    root.mainloop()

