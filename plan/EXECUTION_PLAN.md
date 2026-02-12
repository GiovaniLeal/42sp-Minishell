# Plano: Execução de comandos simples (fork + execve + busca no PATH)

Objetivo
- Implementar execução de comandos simples usando `fork`, `execve` e `waitpid`.
- Buscar o executável no `PATH` quando o comando não for um caminho absoluto.

Pré-requisitos
- `libft` disponível (já presente em `libft/`).
- Biblioteca `readline` para leitura interativa (incluída em `includes/minishell.h`).

Passos (priorizados)
1. Adicionar protótipos em `includes/minishell.h`:
   - `char *find_in_path(char *cmd);`
   - `int exec_simple(char **argv, char **envp);`

2. Implementar `find_in_path()`:
   - Ler a variável de ambiente `PATH` (via `getenv("PATH")` ou `envp`).
   - Separar por `:` e tentar concatenar cada diretório com `/` + `cmd`.
   - Verificar `access(path_candidate, X_OK)` para determinar executável.
   - Retornar `NULL` se não encontrado.

3. Implementar `exec_simple()`:
   - Receber `argv` (array terminado em NULL) e `envp`.
   - Se `argv[0]` contém `/`, tentar `execve(argv[0], argv, envp)` diretamente.
   - Caso contrário, chamar `find_in_path(argv[0])` e, se encontrado, `execve(found, argv, envp)`.
   - Fazer `fork()`;
     - No filho: chamar `execve()` e, se falhar, `perror()` e `exit(127)`.
     - No pai: chamar `waitpid(pid, &status, 0)` e retornar o código de saída apropriado.

4. Integração mínima para testes em `src/main.c`:
   - Substituir momentaneamente a chamada ao `lexer` por um `ft_split(line, ' ')` (só para testar).
   - Chamar `exec_simple(argv, environ)` (use `extern char **environ;`).

5. Testes rápidos
   - Compilar com `make` na raiz do repositório.
   - Testar comandos absolutos:

```sh
./minishell
> /bin/ls -l
> /bin/echo hello
```

   - Testar busca no `PATH`:

```sh
./minishell
> ls -l
> echo hello
```

Notas e cuidados
- Tratar corretamente sinais (SIGINT) e liberar memória de `ft_split` entre execuções.
- Retornar códigos de erro compatíveis com POSIX:
  - `127` quando comando não encontrado ou `execve` falha.
  - `126` quando comando encontrado mas não executável.
- Não misturar mudanças grandes no `lexer`/parser — mantenha a integração de teste temporária isolada.

Arquivos a editar
- `includes/minishell.h` — adicionar protótipos.
- `src/exec.c` (sugerido) — implementar `find_in_path` e `exec_simple`.
- `src/main.c` — integrar chamada de teste (temporária).

Quer que eu implemente estas funções agora (aplico patches e testo), ou prefere só os trechos de exemplo no MD para implementar após revisão?
