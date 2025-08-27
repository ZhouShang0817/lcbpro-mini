# LiveCodeBench Pro Mini (599 Tasks)

Author: LiveCodeBench Pro Team <shz060@ucsd.edu>

This dataset contains 599 competitive programming tasks that submit code to an external judge. Tasks range from lcbpro-1983a to lcbpro-2121h, covering Codeforces problems from contests 1983-2121.

For each task, the agent writes `/app/main.cpp`. The harness posts the code to the judge and polls `GET /result/{sid}?short=1`. The task passes if the judge returns `passed=true`.

## Difficulty Distribution

Tasks are categorized by Codeforces rating:
- **Easy**: Rating ≤ 2000 (basic algorithms, implementation)
- **Medium**: Rating 2000-3000 (data structures, graph algorithms)  
- **Hard**: Rating > 3000 (advanced algorithms, complex mathematics)

## Run
```bash
pip install -U terminal-bench
cd lcbpro-mini

# Run a single task
BASE_URL=http://38.80.122.117:8081 tb run --agent oracle --task-id lcbpro-2026a --livestream

# Run multiple tasks
tb run --agent oracle --task-pattern "lcbpro-212*" --livestream
```

## Generate Tasks
```bash
# Generate all 599 tasks
python3 generate_tasks.py benchmark_config.json

# Generate single task
python3 generate_tasks.py single_task_config.json
```

Environment variables: `BASE_URL`, `PID`, `LANG`, `CODE_PATH`, `JUDGE_TIMEOUT_SECS`.
