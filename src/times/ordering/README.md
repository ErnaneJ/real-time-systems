# Comparison of Sorting Times (QuickSort vs Bubble Sort)

![Comparison of Sorting Times (QuickSort vs Bubble Sort)](./assets/Comparison_of_Sorting_Times_(QSort_vs_BubbleSort).png)

| Algorithm       | O (Worst Case) | Θ (Average Case) | Ω (Best Case)   |
|------------------|----------------|------------------|------------------|
| **QuickSort**    | O(n²)          | Θ(n log n)      | Ω(n log n)       |
| **Bubble Sort**  | O(n²)          | Θ(n²)            | Ω(n)             |

**QuickSort** is generally much more efficient than Bubble Sort in practice, especially for large lists, due to its average complexity of Θ(n log n). While **Bubble Sort** is easy to understand and implement, it is not efficient for larger datasets and is primarily used in educational contexts.

### QuickSort

**1. Big O Notation (O)**  
- **O(n²)**: In the worst-case scenario (when the list is already sorted or sorted in reverse order, and the chosen pivot is always the smallest or largest element), the complexity is quadratic.

**2. Theta Notation (Θ)**  
- **Θ(n log n)**: In the average case, QuickSort has a complexity of Θ(n log n), which is considered efficient for most practical situations.

**3. Omega Notation (Ω)**  
- **Ω(n log n)**: In the best-case scenario, where the pivot divides the array into two equal parts at each recursive call, the complexity is Ω(n log n).

### Bubble Sort

**1. Big O Notation (O)**  
- **O(n²)**: Bubble Sort has quadratic complexity in the worst case, which occurs when the list is sorted in reverse order.

**2. Theta Notation (Θ)**  
- **Θ(n²)**: In the average case, the complexity is also Θ(n²). However, in certain situations, such as when the list is already sorted, the complexity can be optimized to Θ(n) because the algorithm includes a mechanism to terminate early.

**3. Omega Notation (Ω)**  
- **Ω(n)**: In the best-case scenario (when the list is already sorted), the complexity is Ω(n), as the algorithm only requires a single pass through the list to verify that it is sorted.

---

### VENV

```
python3 -m venv venv
deactivate
source venv/bin/activate
pip freeze > requirements.txt
pip install -r requirements.txt
```