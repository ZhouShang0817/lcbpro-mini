#!/usr/bin/env python3
"""
Batch task generation script
Usage: python generate_tasks.py config.json
"""
import json
import os
import shutil
import sys
from pathlib import Path

def replace_placeholders(content, replacements):
    """Replace placeholders in content with actual values"""
    for placeholder, value in replacements.items():
        if placeholder == "PROBLEM_STATEMENT":
            # Fix indentation for YAML multi-line strings
            if isinstance(value, str):
                # Replace problematic Unicode characters with ASCII equivalents
                value = value.replace('—', '--')   # Replace em dash with double hyphen
                value = value.replace('–', '--')   # Replace en dash with double hyphen
                value = value.replace(''', "'")    # Replace left single quote
                value = value.replace(''', "'")    # Replace right single quote
                value = value.replace('"', '"')    # Replace left double quote
                value = value.replace('"', '"')    # Replace right double quote
                value = value.replace('…', '...')  # Replace ellipsis
                value = value.replace('‚', ',')    # Replace single low quote
                value = value.replace('„', '"')    # Replace double low quote
                
                lines = value.split('\n')
                # Remove any existing indentation and add proper indentation (6 spaces for YAML)
                indented_lines = []
                for line in lines:
                    if line.strip():  # Non-empty line
                        # Remove existing indentation and add 6 spaces
                        indented_lines.append('      ' + line.strip())
                    else:  # Empty line
                        indented_lines.append('')
                value = '\n'.join(indented_lines)
        elif placeholder == "SOLUTION_SCRIPT":
            # Handle escaped newlines in solution scripts only
            if isinstance(value, str):
                value = value.replace('\\n', '\n').replace('\\"', '"').replace('\\\\', '\\')
        content = content.replace(f"{{{{{placeholder}}}}}", str(value))
    return content

def create_task_from_template(task_config, templates_dir, output_dir):
    """Create a single task from template"""
    task_name = task_config["TASK_NAME"]
    task_path = Path(output_dir) / task_name
    
    # Create task directories
    task_path.mkdir(exist_ok=True)
    (task_path / "tests").mkdir(exist_ok=True)
    (task_path / "tmp").mkdir(exist_ok=True)
    
    # Template file mappings
    template_files = {
        "task.yaml.template": "task.yaml",
        "docker-compose.yaml.template": "docker-compose.yaml", 
        "Dockerfile.template": "Dockerfile",
        "run-tests.sh.template": "run-tests.sh",
        "main.cpp.template": "main.cpp",
        "solution.sh.template": "solution.sh",
        "testsrun-tests.sh.template": "testsrun-tests.sh",
        "tests/test_outputs.py.template": "tests/test_outputs.py",
        "tests/run-tests.sh.template": "tests/run-tests.sh"
    }
    
    # Process each template file
    for template_file, output_file in template_files.items():
        template_path = Path(templates_dir) / template_file
        output_path = task_path / output_file
        
        if template_path.exists():
            # Read template content
            with open(template_path, 'r', encoding='utf-8') as f:
                content = f.read()
            
            # Replace placeholders
            content = replace_placeholders(content, task_config)
            
            # Create output directory if needed
            output_path.parent.mkdir(parents=True, exist_ok=True)
            
            # Write processed content
            with open(output_path, 'w', encoding='utf-8') as f:
                f.write(content)
            
            # Skip setting permissions due to file system limitations
        else:
            print(f"Warning: Template file {template_path} does not exist")
    
    print(f"✓ Generated task: {task_name}")

def generate_tasks_from_config(config_file):
    """Generate tasks in batch from configuration file"""
    # Read configuration file
    with open(config_file, 'r', encoding='utf-8') as f:
        config = json.load(f)
    
    templates_dir = config.get("templates_dir", "templates")
    output_dir = config.get("output_dir", "tasks")
    tasks = config.get("tasks", [])
    
    # Ensure output directory exists
    Path(output_dir).mkdir(exist_ok=True)
    
    print(f"Starting batch generation of {len(tasks)} tasks...")
    print(f"Templates directory: {templates_dir}")
    print(f"Output directory: {output_dir}")
    print("-" * 50)
    
    # Generate each task
    for i, task_config in enumerate(tasks, 1):
        print(f"[{i}/{len(tasks)}] ", end="")
        try:
            create_task_from_template(task_config, templates_dir, output_dir)
        except Exception as e:
            print(f"✗ Error generating task {task_config.get('TASK_NAME', 'Unknown')}: {e}")
    
    print("-" * 50)
    print(f"Batch generation complete! Processed {len(tasks)} tasks")

def main():
    if len(sys.argv) != 2:
        print("Usage: python generate_tasks.py <config.json>")
        print("Example: python generate_tasks.py example_config.json")
        sys.exit(1)
    
    config_file = sys.argv[1]
    
    if not os.path.exists(config_file):
        print(f"Error: Configuration file {config_file} does not exist")
        sys.exit(1)
    
    try:
        generate_tasks_from_config(config_file)
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()