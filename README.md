# LiveCodeBench Pro Mini (2 Tasks) — Scheme A (single-container + external judge)

Author: Shang Zhou <shz060@ucsd.edu>

This mini dataset contains two tasks that submit code to an external judge (no local test cases).
- `tasks/lcbpro-2121f` (PID=2121F, C++)
- `tasks/lcbpro-2121e` (PID=2121E, C++)

For each task, the agent writes `/app/main.cpp`. The harness posts the code to the judge and
polls `GET /result/{sid}?short=1`. The task passes if and only if the judge returns `passed=true`.

## Run
```bash
pip install -U terminal-bench
cd livecodebench-pro-mini-2tasks-with-statements
BASE_URL=http://38.80.122.117:8081 tb run --agent oracle --task-id lcbpro-2121f --livestream
BASE_URL=http://38.80.122.117:8081 tb run --agent oracle --task-id lcbpro-2121e --livestream
```

You may override via env vars: `BASE_URL`, `PID`, `LANG`, `CODE_PATH`, `JUDGE_TIMEOUT_SECS`.
For fully offline/reproducible runs, consider a multi-container task with a local judge.
