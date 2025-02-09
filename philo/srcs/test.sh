#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

print_test() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${GREEN}Test Case: $1${NC}"
    echo -e "${BLUE}Command: ${NC}$2"
    echo -e "${BLUE}Expected: ${NC}$3"
    echo -e "${BLUE}========================================${NC}"
}

# Basic valid tests
print_test "Basic test - should not die" \
    "./philo 4 410 200 200" \
    "No philosopher should die, all should eat in turns"

print_test "Basic test with eating limit" \
    "./philo 5 800 200 200 7" \
    "Should stop after each philosopher eats 7 times"

print_test "Test with 2 philosophers" \
    "./philo 2 410 200 200" \
    "No philosopher should die, they should alternate eating"

# Death tests
print_test "Death test - should die" \
    "./philo 4 310 200 200" \
    "A philosopher should die due to tight timing"

print_test "One philosopher test" \
    "./philo 1 800 200 200" \
    "The philosopher should die after 800ms"

print_test "Quick death test" \
    "./philo 4 200 210 200" \
    "Should die quickly as time_to_die < time_to_eat"

# Edge cases
print_test "Tight timing test" \
    "./philo 4 399 200 200" \
    "Should die - timing too tight"

print_test "Large number of philosophers" \
    "./philo 200 800 200 200" \
    "Should handle many philosophers without issues"

print_test "Long times test" \
    "./philo 4 2000 1000 1000" \
    "Should work with longer times"

# Error handling tests
print_test "Invalid philosopher count" \
    "./philo 0 400 200 200" \
    "Should return error: Invalid number of philosophers"

print_test "Negative time" \
    "./philo 4 -400 200 200" \
    "Should return error: Invalid time values"

print_test "Zero time" \
    "./philo 4 0 200 200" \
    "Should return error: Invalid time values"

echo -e "\n${GREEN}Test Categories Summary:${NC}"
echo "1. Basic Tests (should survive):"
echo "   ./philo 4 410 200 200"
echo "   ./philo 5 800 200 200"
echo "   ./philo 4 500 200 200"

echo -e "\n2. Death Tests (should die):"
echo "   ./philo 4 310 200 200"
echo "   ./philo 4 200 210 200"
echo "   ./philo 1 800 200 200"

echo -e "\n3. Edge Cases:"
echo "   ./philo 2 310 200 100"
echo "   ./philo 200 800 200 200"

echo -e "\n4. Error Cases:"
echo "   ./philo 0 400 200 200"
echo "   ./philo 4 -400 200 200"
echo "   ./philo 4 0 200 200"

echo -e "\n${RED}Critical Test Cases:${NC}"
echo "1. ./philo 4 310 200 100"
echo "   - Tests precise timing with death"
echo "2. ./philo 4 410 200 200"
echo "   - Tests basic functionality"
echo "3. ./philo 5 800 200 200 7"
echo "   - Tests meal count limit"
echo "4. ./philo 2 400 200 200"
echo "   - Tests minimum multi-philosopher case"
