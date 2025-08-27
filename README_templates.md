# Task Template System

This system allows you to create programming contest problems in batch using templates and configuration files.

## Directory Structure

```
.
├── templates/                    # Template files with placeholders
│   ├── task.yaml.template       
│   ├── docker-compose.yaml.template
│   ├── Dockerfile.template
│   ├── run-tests.sh.template
│   ├── main.cpp.template
│   ├── solution.sh.template
│   └── tests/
│       ├── test_outputs.py.template
│       └── run-tests.sh.template
├── generate_tasks.py            # Batch generation script
├── example_config.json          # Example configuration
└── tasks/                       # Generated tasks output directory
```

## Available Placeholders

The following placeholders can be used in template files:

- `{{TASK_NAME}}` - Task folder name (e.g., "lcbpro-2121d")
- `{{PROBLEM_ID}}` - Problem ID for judge (e.g., "2121D") 
- `{{PROBLEM_STATEMENT}}` - Full problem statement text
- `{{BASE_URL}}` - Judge server URL
- `{{LANGUAGE}}` - Programming language (e.g., "cpp")
- `{{CODE_PATH}}` - Path to solution file
- `{{TIMEOUT_SECS}}` - Judge timeout in seconds
- `{{AUTHOR_EMAIL}}` - Author's email
- `{{DIFFICULTY}}` - Problem difficulty level
- `{{TAGS}}` - Comma-separated tags
- `{{AGENT_TIMEOUT}}` - Agent timeout in seconds
- `{{TEST_TIMEOUT}}` - Test timeout in seconds
- `{{SOLUTION_CODE}}` - C++ solution code
- `{{SOLUTION_SCRIPT}}` - Shell script for oracle solution

## Usage

1. **Create your configuration file** (see `example_config.json`)
2. **Run the generation script**:
   ```bash
   python generate_tasks.py your_config.json
   ```

## Configuration File Format

```json
{
  "templates_dir": "templates",
  "output_dir": "tasks", 
  "tasks": [
    {
      "TASK_NAME": "lcbpro-2121d",
      "PROBLEM_ID": "2121D",
      "PROBLEM_STATEMENT": "Your problem statement here...",
      "BASE_URL": "http://38.80.122.117:8081",
      "LANGUAGE": "cpp",
      "CODE_PATH": "/app/main.cpp",
      "TIMEOUT_SECS": "120",
      "AUTHOR_EMAIL": "shz060@ucsd.edu",
      "DIFFICULTY": "medium",
      "TAGS": "",
      "AGENT_TIMEOUT": 300,
      "TEST_TIMEOUT": 180,
      "SOLUTION_CODE": "#include <iostream>\\nusing namespace std;\\n...",
      "SOLUTION_SCRIPT": "#!/bin/bash\\necho \\\"Solution script\\\""
    }
  ]
}
```

## Example

Generate tasks from the example configuration:
```bash
python generate_tasks.py example_config.json
```

This will create:
- `tasks/lcbpro-2121d/` - Array manipulation problem
- `tasks/lcbpro-2121c/` - String processing problem

Each generated task contains all necessary files with placeholders replaced by actual values from the configuration.