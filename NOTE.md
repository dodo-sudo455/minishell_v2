# NOTE

## 왜 자식에서 heredoc 처리할까?

Ctrl+C 처리를 해야해.
- 이게 heredoc 입력 종료 신호야.

근데 인터럽트는 시그널 핸들러로만 다룰수 있어.

시그널 핸들러로 프로세스가 이동하면 메인 프로세스로 돌아올 수 없어.
- 자식 프로세스에게 시그널 핸들러를 주고
- 자식이 종료되면
- 부모 프로세스는 안전하게 메인 프로세스에서 계속하면 돼.


## 처리 시그널
`Ctrl+C` (SIGINT)
- 새 프롬프트

`Ctrl+D` (EOF)
- 경고문 출력
- 현재 heredoc 마무리

`Ctrl+\\` (SIGQUIT)
- 무시

main_loop:
    prompt()
    parse()
    exec()

prompt():
    시그널 자기 필요한거 등록
    prompt 입력

...


exec():
    시그널 자기 필요한거 등록
    fork()
    execve()