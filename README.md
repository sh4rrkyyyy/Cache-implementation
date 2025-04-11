# Cache-implementation
## Description
Simulation of processor and cache behavior during code execution on RISC-V, with eviction policies LRU and bit-pLRU, translation of assembly code into machine code.

The simulated cache is shared for both instructions and data.
It follows a look-through, write-back policy.

This program accepts arguments via the command line.  
Arguments can be provided in any order.

### Available Arguments

| Argument | Description |
|----------|-------------|
| `--asm <assembly_code_filename>` | Specifies the file containing the assembly code to be executed. |
| `--bin <machine_code_filename>` | Specifies the name of the file where the resulting machine code (translated from assembly) will be saved. |

##  Output Format

The simulation results are printed to the standard output using the `printf` format.

The output includes:
- The overall cache hit rate as a percentage (number of hits to total accesses).
- The instruction cache hit rate.
- The data cache hit rate.

If there were no memory accesses, the output is:

```
nan%
```

## Instruction Encoding

The program takes as input a file containing RISC-V assembly code and executes it.  
The instruction set architecture is based on the unprivileged RISC-V specification:  
[https://github.com/riscv/riscv-isa-manual/releases/tag/riscv-isa-release-b796659-2024-11-14](https://github.com/riscv/riscv-isa-manual/releases/tag/riscv-isa-release-b796659-2024-11-14)

### Supported Features

- **Instruction set**: RV32I, RV32M
- **Register format**: ABI
- **Assembly syntax**:
  - Arguments in instructions are separated by commas: `,`
  - Arbitrary whitespace (spaces, tabs, newlines) is allowed:
    - Before the instruction
    - Between arguments
    - At the end of the line
  - Instruction mnemonics and register names must be written in lowercase
  

## Instruction Execution

Instructions are executed sequentially and are fetched from memory immediately before execution, using a single memory read operation.

### Execution Termination

Program execution ends when either:
- A jump is made to the address stored in register `ra` at program start, or
- A jump is made to an address outside the range of the provided instructions.

### Execution Guarantees

- It is guaranteed that instruction and data memory do not overlap.  
  For example, a store operation will not modify the instruction code.
- Instructions are placed in memory starting from address `0x10000`.
- The instruction execution sequence (e.g., number of loop iterations) and the accessed memory addresses are guaranteed to be independent of the data stored in memory.
- Multi-byte memory accesses are counted as a single memory operation.
- All memory accesses are guaranteed to be aligned (i.e., address is divisible by the access size).
- The instructions `ecall` and `ebreak` are interpreted as `nop` (no operation).