---
description: "Git auto commit & push — stage all changes, AI-generate Conventional Commit message, commit, and push to remote"
name: "git-push"
argument-hint: "(optional) custom commit message suffix"
agent: "agent"
---
# Git Auto Commit & Push

Automate the full git workflow: stage → generate commit message → commit → push.

## Instructions

Follow these steps **in order**, executing each via terminal:

### Step 1: Stage all changes
```bash
git add -A
```

### Step 2: Check if there are staged changes
```bash
git diff --cached --stat
```

If the output is empty (no changes staged), print `✅ 没有变更需要提交` in green/cyan and **stop** — do not proceed.

### Step 3: Read the full diff for message generation
```bash
git diff --cached
```

Analyze the diff output carefully. Understand *what* changed and *why*.

### Step 4: Generate a Conventional Commit message
Based on the diff, generate a **one-line** commit message following the Conventional Commits specification:

| Prefix | When to use |
|--------|-------------|
| `feat:` | New feature |
| `fix:` | Bug fix |
| `refactor:` | Code restructuring (no behavior change) |
| `perf:` | Performance improvement |
| `test:` | Adding/modifying tests |
| `docs:` | Documentation only |
| `style:` | Formatting, whitespace (no code change) |
| `chore:` | Build/config/tooling |
| `cleanup:` | Removing dead code, commented-out code |

Format: `<prefix>: <short imperative description>`

Examples:
- `feat: add SSE streaming support for chat API`
- `fix: handle empty input in read_mutiline_input`
- `refactor: extract http client setup to utility function`
- `cleanup: remove commented-out dead code from deepseek_chat.cpp`

Do NOT include a body or details — keep it to a single line.

If the user provided an argument (e.g. typed `git-push WIP`), append it in parentheses: `chore: update dependencies (WIP)`

### Step 5: Commit
```bash
git commit -m "<generated message>"
```

### Step 6: Push
```bash
git push
```

### Step 7: Report back
Print a brief summary in a friendly tone, including:
- The commit message that was used
- The short commit hash
- Which branch was pushed to
- Number of files changed (if available)

## Constraints
- DO NOT ask the user for confirmation — just execute the full workflow
- DO NOT use external APIs for message generation — analyze the diff yourself
- DO NOT create empty commits — skip if no changes
- If `git push` fails (e.g. network issue, divergence), print the error and stop — do not force push
