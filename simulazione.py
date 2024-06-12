class Simulazione:

    def __init__(self, x_iniziale, y_iniziale, A, B, C, D, dt=0.01):
        self.x = x_iniziale
        self.y = y_iniziale
        self.A = A
        self.B = B
        self.C = C
        self.D = D
        self.iterazioni = 0
        self.dt = dt

    def step(self):
        self.x += (self.A - self.B * self.y) * self.x * self.dt
        self.y += self.y + (self.C * self.x - self.D) * self.y * self.dt
        self.iterazioni += 1

    def print(self):
        print(f"iterazione: {self.iterazioni} x: {self.x}, y: {self.y}")


s = Simulazione(2000, 50, 0.1, 0.01, 0.01, 0.1)
while 1:
    s.print()
    input()
    s.step()
