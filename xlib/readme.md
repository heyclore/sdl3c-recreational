# PROJECT: Xlib Raycaster — Incremental Derivation Roadmap

## PURPOSE
This document defines the canonical build state machine for the project.

Assistant must:
- Track phase progression
- Compare current implementation vs final target when provided
- Help user derive next step incrementally (not jump to final code)

---

# USER SESSION INPUT CONTRACT

User may provide ANY of:

## Case A — Phase Only
"I am on Phase X"

Assistant must:
- Assume all previous phases complete and stable
- Continue roadmap from that phase

---

## Case B — Phase + Current Code
User provides:
1) Current Phase Code
2) Phase label

Assistant must:
- Treat code as ground truth implementation
- Detect missing requirements vs phase definition
- Suggest next minimal milestone

---

## Case C — Phase + Current Code + Final Code (IMPORTANT MODE)

User provides:
1) FINAL CODE (reference target)
2) CURRENT CODE (working state)
3) CURRENT PHASE

Assistant must:
- Treat FINAL CODE as destination architecture
- Treat CURRENT CODE as derivation checkpoint
- DO NOT jump directly to final implementation
- Help user re-derive step-by-step
- May diff conceptually, not dump final solution

---

# CODE INTERPRETATION RULES

## FINAL CODE
Used for:
- Architecture understanding
- Detecting upcoming systems
- Predicting future phase requirements

NOT used for:
- Copy-paste solutions
- Skipping derivation steps

---

## CURRENT CODE
Used for:
- Debugging
- Phase validation
- Gap detection
- Incremental extension planning

Priority:
CURRENT CODE > README phase assumptions

---

# GLOBAL CONSTRAINTS

## Development Philosophy
- Feature-by-feature derivation
- Compile → Run → Verify loop mandatory
- No multi-phase jumps unless user explicitly requests

## Rendering Model
Software rendering pipeline only:
X11 Window → Framebuffer → Raycaster → Present

## Math Model
2D grid world
Raycasting projection (pseudo 3D)

---

# PHASE ORDER (CLEANUP EARLY)

Phase 1 → Window + Event Loop  
Phase 2 → Expose Rendering Hook  
Phase 3 → Framebuffer Memory + Early Cleanup Discipline  
Phase 4 → Drawing Primitives  
Phase 5 → World + Camera Data Models  
Phase 6 → Single Ray Math  
Phase 7 → DDA Grid Traversal  
Phase 8 → Projection Math  
Phase 9 → Full Column Renderer  
Phase 10 → Lighting / Shading  
Phase 11 → Input + Movement  
Phase 12 → Frame Lifecycle Optimization  

---

# PHASE DEFINITIONS

---

## PHASE 1 — X11 Window Skeleton

### Goal
Stable window + event loop.

### Must Exist
- Display open
- Window created
- Event loop running

### Verify
Window visible and persistent.

---

## PHASE 2 — Expose Rendering Trigger

### Goal
Render only on Expose event.

### Must Exist
Expose event handler branch.

### Verify
Visible debug render or log.

---

## PHASE 3 — Framebuffer + EARLY CLEANUP DISCIPLINE

### Goal
Manual pixel rendering + safe memory lifecycle.

### Must Exist
Framebuffer struct:
- pixel buffer
- XImage wrapper
- width / height

### REQUIRED CLEANUP (MANDATORY FROM THIS PHASE)
Must safely:
- Detach pixel pointer from XImage before destroy
- Destroy XImage
- Free pixel buffer
- Close X display

### Verify
Solid color framebuffer render + clean exit.

---

## PHASE 4 — Drawing Primitives

### Goal
Reusable pixel drawing helpers.

### Must Exist
- framebuffer clear
- vertical line renderer

### Verify
Hardcoded vertical bars visible.

---

## PHASE 5 — World + Camera Data Model

### Goal
Simulation state separated from rendering.

### Must Exist
Map grid
Camera struct:
- position
- direction
- camera plane

### Verify
Camera values stable and printable.

---

## PHASE 6 — Single Ray Math

### Goal
Correct ray direction generation for one column.

### Must Exist
cameraX transform
rayDir calculation

### Verify
Ray direction changes smoothly across screen space.

---

## PHASE 7 — DDA Grid Traversal

### Goal
Correct grid stepping traversal.

### Must Exist
deltaDist
sideDist
step selection
hit loop

### Verify
Ray visits expected grid cells.

---

## PHASE 8 — Projection Math

### Goal
Correct wall distance → wall height projection.

### Must Exist
Perpendicular distance calculation
Wall slice height math

### Verify
Distance visually maps to size.

---

## PHASE 9 — Full Screen Column Renderer

### Goal
Render full scene width.

### Must Exist
Column loop performing full ray pipeline.

### Verify
Visible 3D corridor.

---

## PHASE 10 — Lighting / Shading

### Goal
Improve depth perception.

### Must Exist
Side-based shading or equivalent.

---

## PHASE 11 — Input + Movement

### Goal
Interactive camera control.

### Must Exist
Forward/back movement along direction vector.
Rotation matrix applied to direction + plane.

---

## PHASE 12 — Frame Lifecycle Optimization

### Goal
Performance + stability polish.

### May Include
Frame throttling
Dirty frame tracking
Optional double buffering

---

# ASSISTANT RESPONSE POLICY

When user provides code:
1. Validate phase correctness
2. Identify missing phase guarantees
3. Suggest next smallest step
4. Avoid rewriting architecture unless requested

---

# STATE DECLARATION FORMAT (OPTIONAL BUT RECOMMENDED)

User may include:

CURRENT_PHASE: <number>
LAST_WORKING_FEATURE: <short text>
KNOWN_BUG: <optional>
GOAL: <optional>

---

# END TARGET

Interactive Xlib raycaster with:
- Deterministic memory lifecycle
- Correct projection math
- Stable camera movement
- Clean frame presentation

