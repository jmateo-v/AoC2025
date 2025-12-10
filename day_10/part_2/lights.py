import pulp

def solve_lights(goal, moves):
    
    move_vectors = []
    for m in moves:
        vec = [0]*len(goal)
        for idx in m:
            vec[idx] = 1
        move_vectors.append(vec)
    
    prob = pulp.LpProblem("Lights", pulp.LpMinimize)

    x = [pulp.LpVariable(f"x{i}", lowBound = 0, cat="Integer") for i in range(len(moves))]

    prob += pulp.lpSum(x), "TotalPresses"

    for j in range(len(goal)):
        prob += pulp.lpSum(move_vectors[i][j] * x[i] for i in range(len(moves))) == goal[j]

    
    prob.solve(pulp.PULP_CBC_CMD(msg=0))

    solution = [var.value() if var.value() is not None else 0 for var in x]
    total_presses = sum(solution)
    return solution, total_presses


total_presses = 0

with open("input.txt", "r") as file:
    for line_num, line in enumerate(file, start = 1):
        line = line.strip()
        if not line:
            continue

        parts = line.split()
        goal = tuple(map(int, parts[-1].strip("{}").split(",")))
        start = tuple(0 for _ in goal)

        moves = []
        for m in parts[1:-1]:
            nums = m.strip("()").split(",")
            moves.append(tuple(map(int, nums)))

        
        solution, presses = solve_lights(goal, moves)
        total_presses += presses
            
            
print(f"Total number of buttons pressed: {int(total_presses)}")
