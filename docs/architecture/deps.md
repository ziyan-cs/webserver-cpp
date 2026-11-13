# Moudle Dependencies

Arrows point from each module to its dependencies.

```text
    server ──┬── http ──> net ──> core ──> base
             ├── pool ──> base
             └── base
```

`base` is the foundational module and has no dependencies.
