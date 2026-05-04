*Este projeto foi criado como parte do currículo da 42 por giodos-s e anunes-o*

## 🐚 Minishell - Descrição

O projeto Minishell tem como objetivo criar um interpretator de comandos inspirado no **bash**, capaz de executar comandos externos, builtins, gerenciar pipes, redirecionamentos, variaveis de ambiente e sinais.

O projeto tem como foco principal:

- Interpretar e executar **comandos externos** utilizando `fork`, `execve` e wait.
- Implementar pipes (`|`) para comunicação entre múltiplos processos.
- Gerenciar redirecionamentos de entrada e saída, incluindo `<`, `>`, `>>` e `<<` (heredoc).
- Implementar builtins essenciais, como `cd`, `echo`, `pwd`, `export`, `unset`, `env` e `exit`.
- Manipular corretamente variáveis de ambiente, incluindo expansão (`$VAR`, `$?`).
- Tratar sinais do sistema (`SIGINT`, `SIGQUIT`, `EOF`) de forma semelhante ao bash.
- Garantir **gerenciamento correto de memória e descritores de arquivo**, evitando vazamentos e comportamentos indefinidos.

Esse projeto visa aprofundar a compreensão de conceitos fundamentais de sistemas operacionais, como **execução concorrente, comunicação entre processos, controle de sinais e arquitetura de software em C**.


## 💻 Instalação

Para compilar o projeto, clone esse repositorio e execute o comando abaixo no terminal:

```
git clone https://github.com/GiovaniLeal/42sp-Minishell.git
cd 42sp-Minishell
make 
```

O comando irá clonar esse repositório e compilar todos os arquivos-fonte, gerando o executável `minishell`

A seguir todos os comandos disponíveis do Makefile:

- `make` - Compila o projeto
- `make re` - Recompila o projeto do zero (faz fclean seguido de all).
- `make clean` - Remove os arquivos objeto (.o)
- `make flean` - Remove os arquivos objeto e o executável.

## ▶️ Execução
Após a compilação execute o programa utilizando o comando abaixo:
``` 
./minishell 
```
Ao iniciar, o minishell exibirá um prompt interativo, no qual é possível digitar comandos da mesma forma que em um shell Unix tradicional.

Para encerrar o programa utilize o comando `exit` ou pressione `ctrl + D`

**Exemplos de uso**
```
ls -la
echo "Hello, minishell"
ls | grep minishell
cat < input.txt | wc -l > output.txt
```

## Recursos
O **minishell** implementa funcionalidades essenciais de um shell Unix, reproduzindo o comportamento esperado do **bash** dentro do escopo do projeto.

### 🔹 Execução de Comandos
- Execução de **comandos externos** a partir das variáveis de ambiente (`PATH`).
- Suporte a **argumentos**, aspas simples (`'`) e aspas duplas (`"`).
- Resolução de caminhos relativos e absolutos.

### 🔹 Builtins
O projeto implementa os seguintes comandos internos:
- `echo` (com suporte à flag `-n`)
- `cd` (com caminhos relativos, absolutos e `~`)
- `pwd`
- `export`
- `unset`
- `env`
- `alias`
- `unalias`
- `exit`

### 🔹 Pipes
- Suporte a **pipelines** com o operador `|`.
- Execução correta de múltiplos comandos encadeados.
- Comunicação entre processos através de **pipes anônimos**.

### 🔹 Redirecionamentos
- Redirecionamento de entrada (`<`)
- Redirecionamento de saída (`>`)
- Redirecionamento de saída em modo append (`>>`)
- **Heredoc** (`<<`), com leitura interativa até o delimitador definido.

### 🔹 Variáveis de Ambiente
- Expansão de variáveis com `$VAR`.
- Expansão do código de saída do último comando (`$?`).
- Manipulação dinâmica do ambiente com `export` e `unset`.

### 🔹 Sinais
- Tratamento adequado de sinais:
  - `Ctrl + C` (`SIGINT`)
  - `Ctrl + \` (`SIGQUIT`)
  - `Ctrl + D` (EOF)
- Comportamento consistente com o bash em modo interativo.

### 🔹 Modo de Execução
- **Modo interativo**, com prompt persistente.
- **Modo não interativo** (`-c`), permitindo execução direta de comandos.

### 🔹 Gerenciamento de Recursos
- Gerenciamento correto de **memória dinâmica**.
- Fechamento adequado de **descritores de arquivo**.
- Execução validada com ferramentas como `valgrind`, sem vazamentos de memória.

## 📌 Notas
Essa projeto não replica exatamente o comportamento do bash, o foco principal é compreender as interações do sistema low-level.

## 👥 Autoria e Licença

- [Giovani Leal](https://github.com/GiovaniLeal]) 
- [Ana Clara Nunes](https://github.com/Ana-Clara-Nunes)

📘 Uso permitido:
Pode ser utilizado como referência para estudos e aprendizado individual

🚫 Proibido: Submeter cópias deste projeto como se fossem de sua autoria em avaliações da 42 ou outras instituições