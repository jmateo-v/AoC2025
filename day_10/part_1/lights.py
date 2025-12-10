from collections import deque

def apply_move(state, move):
    s = list(state)

    if isinstance(move, int):
        s[move] = '#' if s[move] == '.' else '.'
    else:
        for idx in move:
            s[idx] = '#' if s[idx] == '.' else '.'
    return tuple(s)

def is_goal(state):
    return state == goal_str

def bfs(start, goal, moves):
    queue = deque([(start, [])])
    visited = {start}

    while queue:
        state, path = queue.popleft()
        if is_goal(state):
            return path
        for move in moves:
            next_state = apply_move(state, move)
            if next_state not in visited:
                visited.add(next_state)
                queue.append((next_state, path + [move]))
    return None

total_presses = 0

with open("input.txt", "r") as file:
    for line_num, line in enumerate(file, start = 1):
        line = line.strip()
        if not line:
            continue

        parts = line.split()
        goal_str = tuple(parts[0].strip("[]"))
        start_str = tuple("." for _ in goal_str)
        moves_str = parts[1:-1]

        moves = []
        for m in moves_str:
            nums = m.strip("()").split(",")
            if len(nums) == 1:
                moves.append(int(nums[0]))
            else:
                moves.append(tuple(map(int, nums)))
        
        solution = bfs(start_str, goal_str, moves)
        
        if solution is not None:
            presses = len(solution)
            total_presses += presses
            
print(f"Total number of buttons pressed: {total_presses}")
