# 데이터 구조

## t_token

```text
t_token
├── t
│   ├── TOKEN_WORD
│   ├── TOKEN_PIPE
│   ├── TOKEN_REDIR_IN
│   ├── TOKEN_REDIR_OUT
│   ├── TOKEN_REDIR_HDOC
│   └── TOKEN_REDIR_APPEND
└── s
```


## t_cmd

```text
t_cmd
├── arglst   : 명령 및 인자 리스트
├── redlst   : 리다이렉션 리스트
└── pid      : 실행된 자식 PID
```


## t_redir

```text
t_redir
├── t
│   ├── REDIR_IN
│   ├── REDIR_OUT
│   ├── REDIR_HDOC
│   └── REDIR_APPEND
├── s       : 파일명 또는 heredoc delimiter
└── docfd   : heredoc FD
```


## t_ctx

```text
t_ctx
├── envlst
├── status
├── err
├── errcmd
└── errarg
```

### envlst

환경 변수는 `t_env` 링크드 리스트로 관리됩니다.

```text
t_env
├── key
└── val
```

조회 및 수정 함수

- `ctx_getenv()`
- `ctx_setenv()`
- `ctx_unsetenv()`

### status

`c_ref->status`에는 **마지막 foreground pipeline의 종료 상태**가 저장됩니다.

`parse_expand()`에서 `$?`를 만나면 이 값을 문자열로 치환합니다.