# Copilot / AI agent instructions for minishell

Não gerar código a não ser que eu peça explicitamente
Responder em Português

## 🔧 Norma 42 v4.1 - Strict Compliance (C PROJECTS ONLY: 00, 01, 02, 03)

**⚠️ Applies to:** All C projects (libft, GNL, Printf, Minitalk, Push_swap, Minishell, Philosophers)  
**❌ Does NOT apply to:** C++ projects (04/), Graphics projects, or non-C code

### 1. **Palavras-chave e Estruturas PROIBIDAS**
❌ **Absolutamente Proibido:**
- `for` loops
- `do...while` loops
- `switch`, `case`, `goto`
- Operadores ternários: `?` `:`

✅ **Use instead:** `while` loops, `if/else`

### 2. **Restrições em Funções (RIGOROSO)**
- **Máximo 25 linhas** (sem contar as chaves `{}`)
- **Máximo 5 variáveis declaradas** por função
- **Máximo 4 parâmetros** por função
- **SEM comentários** dentro do corpo da função
- **Declaração E Inicialização em linhas separadas** (exceto globais/static/const)
- **Sem linhas vazias** dentro da função (exceto 1 após declarações de variáveis)

### 3. **Formatação (OBRIGATÓRIO)**
- **80 colunas** máximo por linha
- **Indentação:** Tabs reais (ASCII 9) = 4 caracteres (NÃO espaços)
- **Nenhuma linha vazia** consecutiva (max 1)
- **Sem espaços** no final de linhas
- **Sem dois ou mais espaços** consecutivos
- **Apenas ASCII padrão** (exceto strings literais)
- **Naming:** `snake_case` APENAS (letras MINÚSCULAS)

### 4. **Organização de Arquivos**
- **Máximo 5 funções** por arquivo `.c`
- **Sem structs declaradas em `.c`** (apenas em `.h`)
- **Sem includes de `.c` em outro `.c` ou `.h`**
- **Sem headers não utilizados**
- **Sem variáveis globais** (exceto `static` ou `const`)

### 5. **Pré-processadores (RESTRITO)**
- **Sem macros de múltiplas linhas**
- `#define` **apenas para constantes e valores literais**
- **Sem pré-processador fora do escopo global**
- **Sem ofuscação de código** com macros

### 6. **Makefile (OBRIGATÓRIO)**
- **SEM relink** - não recompila se não há mudanças
- **SEM wildcards** (`*.c`, `*.o`) - listar todos os arquivos explicitamente
- **Rules:** `all`, `clean`, `fclean`, `re`, `bonus` (if applicable)

### 2. **Project Structure** (Standard 42 Template)
```
project/
├── Makefile          # Build rules, re-linkable
├── README.md         # Project documentation
├── inc/              # Header files (.h)
├── src/              # Source files (.c)
├── libft/            # Reusable library (if used)
├── obj/              # Object files (gitignored)
└── .gitignore        # Exclude build artifacts
```

### 3. **Makefile Standards**
- **Rules:** `all`, `clean`, `fclean`, `re`, `bonus` (if applicable)
- **Flags:** `-Wall -Wextra -Werror -I<headers>`
- **No linking order issues** - use proper variable ordering
- **Re-linkable:** Remove `.o` only on `clean`, not on `fclean`

### 4. **Memory Management**
- **No leaks:** Use `valgrind --leak-check=full` before submitting
- **Free strategy:** Create `free_*` functions for cleanup
- **Exit handling:** Properly close/free on `exit()` and error paths
- **Forbidden functions only if project requires it** (some projects ban `malloc`)

### 5. **Error Handling**
- **Check return values** of all system calls (`malloc`, `open`, `read`, etc)
- **Use `perror()`** or custom error printing
- **Exit codes:** Use `EXIT_SUCCESS` (0) and `EXIT_FAILURE` (1) from stdlib
- **stderr vs stdout:** Errors to stderr, output to stdout

### 6. **Code Organization**
- **One responsibility per function** (SRP)
- **Logical file grouping** (parsing, execution, utils, etc)
- **Clear file naming:** `parser.c`, `executor.c`, `validation.c` (NOT `utils.c` for everything)
- **Constants in headers** as `#define` or `enum`

### 7. **Bonus Features**
- **Only if mandatory is perfect** - No partial bonus
- **Separate files:** `*_bonus.c`, `*_bonus.h` (when required)
- **Document bonus status** in README
- **All bonus must pass norminette**


---

---

## 🚫 CHECKLIST - Erros que FALHAM na Norminette v4.1

❌ **ERROS CRÍTICOS (Falha Automática):**
- [ ] Função com >25 linhas
- [ ] Função com >5 variáveis locais
- [ ] Função com >4 parâmetros
- [ ] Uso de `for`, `do...while`, `switch/case`, `goto`, `?:`
- [ ] Comentários dentro da função
- [ ] Linha com >80 caracteres
- [ ] Indentação com espaços (não tabs)
- [ ] Variável global não `static` ou `const`
- [ ] Struct declarada em `.c`
- [ ] Arquivo `.c` incluído em outro arquivo
- [ ] >5 funções no mesmo arquivo
- [ ] Macros com múltiplas linhas
- [ ] Wildcards no Makefile (`*.c`, `*.o`)
- [ ] Headers não utilizados
- [ ] Letras MAIÚSCULAS em nomes de função/variável/arquivo

---

## ✅ EXEMPLO CORRETO (Norma 4.1)

### ✅ Função Válida:
```c
// CORRETO: Segue todas as restrições
static int  process_token(t_token *tok, t_list **head, char *value)
{
    char    *expanded;
    char    *temp;

    expanded = ft_strdup(value);
    if (!expanded)
        return (-1);
    temp = expanded;
    expanded = expand_variables(expanded, tok->env);
    free(temp);
    return (0);
}
```
- ✅ 13 linhas (< 25)
- ✅ 3 variáveis locais (< 5)
- ✅ 3 parâmetros (< 4)
- ✅ Sem comentários no corpo
- ✅ Tabs para indentação
- ✅ Sem linhas vazias consecutivas

### ❌ Função Inválida:
```c
// ERRADO: Viola múltiplas restrições
static void process_all(t_data *data)
{
    for (int i = 0; i < data->count; i++)  // ❌ for loop
    {
        int result = (data->items[i] > 0 ? 1 : 0);  // ❌ ternário
        char *temp = data->values[i]; // ❌ inicializa na mesma linha
        
        // ❌ comentário no corpo
        process_item(temp);
    }
}
```

---

## 🔍 Code Quality Checks (BEFORE Implementation)

**Always do these before suggesting code:**

1. ✅ **Norminette check** - `norminette inc src` (if available)
2. ✅ **Compile warnings** - `-Wall -Wextra -Werror`
3. ✅ **Norma 4.1 compliance** - Check against strict rules above
4. ✅ **Memory leaks** - `valgrind --leak-check=full ./program`
5. ✅ **Edge cases** - Empty input, NULL pointers, boundary conditions
6. ✅ **Exact line count** - Function must be exactly ≤25 lines
7. ✅ **Variable count** - Exactly ≤5 local variables

---
## 🎯 Implementation Guidelines

### When Making Changes:

1. **Read the code first** - Understand structure before modifying
2. **Find exact location** - Line numbers, context matching
3. **Include 3-5 lines of context** - Before and after changes
4. **Test after changes** - Compile and run immediately
5. **Track progress** - Use todo lists for multi-step tasks
6. **Document in chat notes** - Keep `CHAT_NOTES_*.md` updated

### When Creating Files:

- **Only create essential files** - Don't over-engineer
- **Follow project template** - Consistency matters
- **Add to Makefile** - If new source files are added
- **Update headers** - Include newly created header files

### When Fixing Bugs:

1. **Reproduce the bug** - Verify it exists
2. **Understand root cause** - Don't patch symptoms
3. **Check for side effects** - Ensure fix doesn't break other features
4. **Add edge case handling** - Prevent regression
5. **Test thoroughly** - Normal + edge cases

---

## 🚫 Things to AVOID

- ❌ **Global variables** (unless absolutely necessary)
- ❌ **Magic numbers** - Use named constants
- ❌ **Deeply nested code** - Refactor into functions
- ❌ **Commented-out code** - Delete or explain with `// TODO:`
- ❌ **Unclear variable names** - Use descriptive names
- ❌ **Large functions** - Break into smaller functions
- ❌ **Memory leaks** - Test with valgrind
- ❌ **Mixed concerns** - Separate parsing/execution/display logic
- ❌ **Duplicate code** - Extract to reusable functions

---

## ✅ Things to DO

- ✅ **Write modular code** - Reusable functions
- ✅ **Check all return values** - malloc, open, read, etc
- ✅ **Handle errors gracefully** - Don't crash silently
- ✅ **Use const correctly** - For pointers, parameters
- ✅ **Test edge cases** - Empty input, large input, invalid input
- ✅ **Document complex logic** - Comments for "why", not "what"
- ✅ **Keep files organized** - Related functions in same file
- ✅ **Follow project naming** - Consistency across team
- ✅ **Update README** - Keep project docs current

---
## 📝 Communication Style with AI

- **Be specific:** "Fix the pipe bug in parser.c line 57" (not "Fix parser")
- **Provide context:** Link related chat notes or test reports
- **Ask for explanations:** If something seems unclear
- **Use todos:** For complex multi-step tasks
- **Request code review:** Before committing major changes

Regras gerais:
- Responder SEMPRE em português brasileiro (pt-BR) em todas as interações, explicações, comentários e documentação gerada.
- Não alterar código (arquivos fonte, headers, Makefiles, scripts) sem solicitação prévia e expressa do usuário. Em caso de dúvida, solicitar confirmação explícita antes de qualquer modificação.
- Para qualquer alteração de código solicitada: apresentar um plano curto (o que, onde, impacto), aplicar mudanças com patch mínimo, e executar testes/compilação imediatos após a alteração.
- Ao gerar novos .md de análise, criar diretamente na pasta adequada ou mover para lá imediatamente.
- Manter respostas concisas, diretas e objetivas; priorizar comandos e caminhos claros.
- Evitar formatações pesadas; usar listas curtas quando necessário.



