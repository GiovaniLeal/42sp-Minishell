#!/bin/bash

# Check if norminette is installed (multiple possible locations)
NORM_CMD=""

# Try virtualenv first
if [ -f "/home/anunes-o/Projects/.venv/bin/norminette" ]; then
    NORM_CMD="/home/anunes-o/Projects/.venv/bin/norminette"
# Try global command
elif command -v norminette &> /dev/null; then
    NORM_CMD="norminette"
# Try python module
elif python3 -m norminette --version &> /dev/null 2>&1; then
    NORM_CMD="python3 -m norminette"
fi

# If not found, show error
if [ -z "$NORM_CMD" ]; then
    echo "Error: norminette is not installed!"
    echo "Install with: pip3 install norminette"
    exit 1
fi

# Directories to check
MINISHELL_ROOT="/home/anunes-o/Projects/minishell/"
OUTPUT_FILE="/home/anunes-o/Projects/minishell/tests analysis/norminette_report_$(date +%Y%m%d_%H%M%S).txt"

echo "========================================" | tee "$OUTPUT_FILE"
echo "  NORMINETTE REPORT - MINISHELL" | tee -a "$OUTPUT_FILE"
echo "  $(date '+%Y-%m-%d %H:%M:%S')" | tee -a "$OUTPUT_FILE"
echo "========================================" | tee -a "$OUTPUT_FILE"
echo "" | tee -a "$OUTPUT_FILE"

# Check includes
echo "==> Checking includes..." | tee -a "$OUTPUT_FILE"
echo "----------------------------------------" | tee -a "$OUTPUT_FILE"
$NORM_CMD "$MINISHELL_ROOT/includes" 2>&1 | tee -a "$OUTPUT_FILE"
echo "" | tee -a "$OUTPUT_FILE"

# Check includes_bonus
echo "==> Checking includes_bonus..." | tee -a "$OUTPUT_FILE"
echo "----------------------------------------" | tee -a "$OUTPUT_FILE"
$NORM_CMD "$MINISHELL_ROOT/includes_bonus" 2>&1 | tee -a "$OUTPUT_FILE"
echo "" | tee -a "$OUTPUT_FILE"

# Check libft
echo "==> Checking libft..." | tee -a "$OUTPUT_FILE"
echo "----------------------------------------" | tee -a "$OUTPUT_FILE"
$NORM_CMD "$MINISHELL_ROOT/libft" 2>&1 | tee -a "$OUTPUT_FILE"
echo "" | tee -a "$OUTPUT_FILE"

# Check src
echo "==> Checking src..." | tee -a "$OUTPUT_FILE"
echo "----------------------------------------" | tee -a "$OUTPUT_FILE"
$NORM_CMD "$MINISHELL_ROOT/builtins" 2>&1 | tee -a "$OUTPUT_FILE"
$NORM_CMD "$MINISHELL_ROOT/environment" 2>&1 | tee -a "$OUTPUT_FILE"
$NORM_CMD "$MINISHELL_ROOT/execution" 2>&1 | tee -a "$OUTPUT_FILE"
$NORM_CMD "$MINISHELL_ROOT/expander" 2>&1 | tee -a "$OUTPUT_FILE"
$NORM_CMD "$MINISHELL_ROOT/lexer" 2>&1 | tee -a "$OUTPUT_FILE"
$NORM_CMD "$MINISHELL_ROOT/parsing" 2>&1 | tee -a "$OUTPUT_FILE"
$NORM_CMD "$MINISHELL_ROOT/redirs" 2>&1 | tee -a "$OUTPUT_FILE"
$NORM_CMD "$MINISHELL_ROOT/utils" 2>&1 | tee -a "$OUTPUT_FILE"
echo "" | tee -a "$OUTPUT_FILE"

# Check src_bonus
echo "==> Checking src_bonus..." | tee -a "$OUTPUT_FILE"
echo "----------------------------------------" | tee -a "$OUTPUT_FILE"
$NORM_CMD "$MINISHELL_ROOT/src_bonus" 2>&1 | tee -a "$OUTPUT_FILE"
echo "" | tee -a "$OUTPUT_FILE"

# Summary
echo "========================================" | tee -a "$OUTPUT_FILE"
echo "  SUMMARY" | tee -a "$OUTPUT_FILE"
echo "========================================" | tee -a "$OUTPUT_FILE"

# Count errors
ERROR_COUNT=$(grep -c "Error" "$OUTPUT_FILE" 2>/dev/null || echo "0")
OK_COUNT=$(grep -c "OK!" "$OUTPUT_FILE" 2>/dev/null || echo "0")

echo "Files OK: $OK_COUNT" | tee -a "$OUTPUT_FILE"
echo "Errors found: $ERROR_COUNT" | tee -a "$OUTPUT_FILE"
echo "" | tee -a "$OUTPUT_FILE"
echo "Report saved to: $OUTPUT_FILE" | tee -a "$OUTPUT_FILE"

# Return appropriate exit code
if [ "$ERROR_COUNT" -gt 0 ]; then
    exit 1
else
    exit 0
fi
