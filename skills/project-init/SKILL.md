## Project Initiation Skill: project-init

**Goal:** To collaboratively define the complete initial scope, naming, and foundational artifacts for a new project. This skill replaces the interactive session flow used previously.

**Inputs:** None required upon invocation.
**Outputs:** A comprehensive Project Context object containing {Objective, Details, Dependencies, AppName} and triggers artifact generation.

### Execution Flow (Transactional)
The skill executes a guided drill-down sequence:

1.  **{TASK: Define Objective}**: Prompts for core purpose.
2.  **{TASK: Gather Details}**: Iteratively prompts for additional context until {TASK: Stop} is signaled.
3.  **{TASK: Check Dependencies}**: Confirms use of external libraries.
4.  **{TASK: Finalize Name}**: Prompts for the final `AppName`.
5.  **{TASK: Output Artifacts}**: Upon successful completion, this step triggers the generation/update of:
    *   `README.md`
    *   `AGENTS.md`
    *   `CMakeLists.txt` (conditional on build stage)

**Invocation:** Use `project-init` when starting a new project setup. The skill manages the entire dialogue until the project is sufficiently scoped to proceed with artifact generation.

**Stop Condition:** The user signals completion at any phase or chooses to stop the drill-down.

---
*Note: The initial run successfully executed this sequence. Future calls to this skill should either resume from a checkpoint or restart the process.*