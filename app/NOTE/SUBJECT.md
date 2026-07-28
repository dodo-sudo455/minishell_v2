# Mandatory part

| Program Name | minishell |
| --- | --- |
| Files to Submit | Makefile, *.h, *.c |
| Makefile | NAME, all, clean, fclean, re |
| Arguments |  |
| External Function | readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs |
| Libft authorized | Yes |
| Description | Write a shell |

당신의 쉘은 반드시:

- 새로운 명령어를 기다리는 동안 프롬프트를 표시할 것
- 명령어 히스토리를 가질 것
- 실행파일을 검색하고 실행할 것(PATH 변수 && 절대 경로)
- 수신된 신호를 처리하기 위해 단 하나의 전역 변수를 사용할 것(이 접근 방식은 시그널 핸들러가 주요 데이터 구조에 접근하지 않도록 해줌)
    - 이 전역 변수는 신호 번호만 저장해야 함
    - norm 자료형 구조체를 사용하는 것은 금지됨
- 닫히지 않은 따옴표, 주어에 필요하지 않은 특수 문자(\ or ;)는 해석하지 말 것
- 따옴표(')를 처리하여 셸이 따옴표로 묶인 시퀀스의 메타문자를 해석하지 못하도록 할 것
- 큰따옴표("")를 처리하면 셸이 따옴표로 묶인 문자열에서 달러 기호($)를 제외한 메타 문자를 해석하지 못하도록 할 것
- 다음 리다이렉션을 구현:
    - `<`
    - `>`
    - `<<`: 구분자를 지정한 다음, 해당 구분자가 포함된 줄이 나타날 때까지 입력을 읽음. 단, 히스토리 업데이트 X.
    - `>>`: 추가 모드에서 출력 리다이렉션
- 파이프(|) 구현
- 환경 변수($ 뒤에 문자열이 오는 형식)를 처리하고, 해당 변수가 값으로 확장되도록 구현
- $? 입력 시 가장 최근에 실행된 포그라운드 파이프라인의 종료 상태 표시
- bash의 `ctrl+C`, `ctrl+D`, `ctrl+\` 동작 구현
    - 대화 모드(interactive mode)에서:
        - ctrl+C: 새 줄에 새 프롬프트 표시
        - ctrl+D: 쉘에서 exit
        - ctrl+\: 아무것도 안 함;;
- 빌트인 명령어 구현:
    - `echo`, `echo -n`
    - `cd [relative or absolute path]`
    - `pwd`
    - `export`
    - `unset`
    - `env`
    - `exit`

👉 readlin() 함수는 메모리 누수를 일으킬 수도 있으며, 이것을 고치는 것은 필수가 아님. 
