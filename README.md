# hijack

System call hijacking using loadable kernel modules

## Introduction

System call hijacking is an interesting low-level way for the hacker / penetration tester
to really gain system privileges of a system, and deploying rootkits for faster and intrusive-less
privilege mitigation. Today, let's take a look at how exactly this works by breaking down the anatomy
of a system call, and performing an actual hijacking.

## Compilation

```
make
```

will build all of the files.
