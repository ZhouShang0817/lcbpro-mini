#!/usr/bin/env python3
"""
Generate complete benchmark configuration from ids.txt, problem_statements_all.jsonl, and std folder
"""
import json
import os
from pathlib import Path

def load_problem_statements(jsonl_file):
    """Load problem statements from JSONL file"""
    problems = {}
    try:
        with open(jsonl_file, 'r', encoding='utf-8') as f:
            for line in f:
                line = line.strip()
                if line:
                    data = json.loads(line)
                    problem_id = data.get('problem_id')
                    if problem_id:
                        problems[problem_id] = {
                            'statement': data.get('problem_statement', ''),
                            'difficulty': data.get('difficulty', 'medium')
                        }
    except Exception as e:
        print(f"Error loading problem statements: {e}")
    
    return problems

def load_solution_code(problem_id, std_dir):
    """Load solution code from std directory"""
    cpp_file = Path(std_dir) / f"{problem_id}.cpp"
    if cpp_file.exists():
        try:
            with open(cpp_file, 'r', encoding='utf-8') as f:
                content = f.read()
                # Return raw content - no escaping needed for direct file writing
                return content
        except Exception as e:
            print(f"Error reading {cpp_file}: {e}")
    return ""

def generate_benchmark_config():
    """Generate complete benchmark configuration"""
    
    # Load problem IDs from ids.txt
    ids_file = "ids.txt"
    if not os.path.exists(ids_file):
        print(f"Error: {ids_file} not found")
        return None
    
    with open(ids_file, 'r') as f:
        problem_ids = [line.strip() for line in f if line.strip()]
    
    print(f"Found {len(problem_ids)} problem IDs in ids.txt")
    
    # Load problem statements
    statements_file = "problem_statements_all.jsonl"
    if not os.path.exists(statements_file):
        print(f"Error: {statements_file} not found")
        return None
    
    problem_data = load_problem_statements(statements_file)
    print(f"Loaded {len(problem_data)} problem statements")
    
    # Check std directory
    std_dir = "std"
    if not os.path.exists(std_dir):
        print(f"Error: {std_dir} directory not found")
        return None
    
    # Generate configuration
    config = {
        "templates_dir": "templates",
        "output_dir": "tasks",
        "tasks": []
    }
    
    missing_statements = 0
    missing_solutions = 0
    
    for problem_id in reversed(problem_ids):
        # Get problem statement and difficulty
        problem_info = problem_data.get(problem_id, {})
        statement = problem_info.get('statement', f'Problem {problem_id} - Statement not available')
        difficulty = problem_info.get('difficulty', 'medium')
        
        if not problem_info:
            missing_statements += 1
        
        # Get solution code
        solution_code = load_solution_code(problem_id, std_dir)
        if not solution_code:
            missing_solutions += 1
            solution_code = f"// Solution for {problem_id} not found\\n#include <iostream>\\nusing namespace std;\\n\\nint main() {{\\n    // TODO: Implement solution\\n    return 0;\\n}}"
        
        # Create task configuration with lowercase task name
        task_config = {
            "TASK_NAME": f"lcbpro-{problem_id.lower()}",
            "PROBLEM_ID": problem_id,
            "PROBLEM_STATEMENT": statement,
            "BASE_URL": "http://38.80.122.117:8081",
            "LANGUAGE": "cpp",
            "CODE_PATH": "/app/main.cpp",
            "TIMEOUT_SECS": "120",
            "AUTHOR_EMAIL": "shz060@ucsd.edu",
            "DIFFICULTY": difficulty,
            "AGENT_TIMEOUT": 300,
            "TEST_TIMEOUT": 180,
            "SOLUTION_CODE": solution_code,
            "SOLUTION_SCRIPT": "#!/bin/bash\\necho \\\"Oracle solution script\\\""
        }
        
        config["tasks"].append(task_config)
    
    print(f"Generated configuration for {len(config['tasks'])} tasks")
    if missing_statements > 0:
        print(f"Warning: {missing_statements} tasks missing problem statements")
    if missing_solutions > 0:
        print(f"Warning: {missing_solutions} tasks missing solution code")
    
    return config

def main():
    print("Generating complete benchmark configuration...")
    print("=" * 60)
    
    # Generate configuration
    config = generate_benchmark_config()
    
    if config is None:
        print("Failed to generate configuration")
        return 1
    
    # Save configuration
    output_file = "benchmark_config.json"
    try:
        with open(output_file, 'w', encoding='utf-8') as f:
            json.dump(config, f, indent=2, ensure_ascii=False)
        
        print("=" * 60)
        print(f"✓ Benchmark configuration saved to: {output_file}")
        print(f"✓ Total tasks: {len(config['tasks'])}")
        print(f"✓ Ready to generate with: python generate_tasks.py {output_file}")
        
        return 0
    except Exception as e:
        print(f"Error saving configuration: {e}")
        return 1

if __name__ == "__main__":
    exit(main())