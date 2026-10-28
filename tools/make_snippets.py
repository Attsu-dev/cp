import json
import os
from pathlib import Path

root = Path(os.environ["CP_ROOT"])
snippets = {}

for path in sorted((root / "snippets").glob("*.hpp")):
    lines = path.read_text().splitlines()
    name = path.stem
    if lines and lines[0].startswith("//"):
        name = lines.pop(0).removeprefix("//").strip()
    snippets[name] = {"prefix": path.stem, "body": lines}

output = root / ".vscode" / "cpp.code-snippets"
output.write_text(json.dumps(snippets, ensure_ascii=False, indent=4) + "\n")
