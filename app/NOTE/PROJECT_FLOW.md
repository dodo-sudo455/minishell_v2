# 데이터 흐름

`session_run(c_ref, s_ref)`는 **입력 → 파싱 → 실행**의 순서로 동작합니다.

## 전체 요약

```text
사용자 입력
        │
        ▼
session_prompt()	(s_ref->input)
        │
        ▼
session_parse()		(s_ref->toklst)
        │
        ▼
session_exec()		(s_ref->cmdlst)
```


## 1. 입력

`session_prompt()`는

```c
prompt(c_ref, &s_ref->input);
```

을 호출하여 사용자의 입력 문자열을 `s_ref->input`에 저장합니다.


## 2. 파싱

`session_parse()`는 다음 순서로 입력을 처리합니다.

| 단계 | 함수 | 역할 |
|------|------|------|
| 1 | `parse_is_quote_ok()` | 따옴표 짝 검사 |
| 2 | `parse_tokenize()` | 문자열 → `t_token` 리스트 생성 |
| 3 | `parse_expand()` | `$VAR`, `$?` 환경 변수 확장 |
| 4 | `parse_split_word()` | 공백 기준 단어 분리 |
| 5 | `parse_quote()` | `'`, `"` 제거 |
| 6 | `parse_command()` | `t_cmd` 명령 리스트 생성 |

### Tokenize

`parse_tokenize()`는 입력 문자열을 `t_token` 리스트(`s_ref->toklst`)로 변환합니다.

메타 문자는 각각 하나의 토큰으로 분리됩니다.

```
|
<
<<
>
>>
```

각 토큰은 다음 정보를 가집니다.

```text
t_token
├── t : 토큰 타입
└── s : 토큰 문자열
```

### Expand

`parse_expand()`는 `TOKEN_WORD`에 대해서만

- `$VAR`
- `$?`

를 실제 값으로 치환합니다.

단, **heredoc 구분자(`<<`) 바로 뒤 토큰은 확장을 수행하지 않습니다.**

### Command 생성

`parse_command()`는 토큰 리스트를 순회하여 `t_cmd` 리스트를 생성합니다.

명령 분리는

- `token_is_pipe()`
- `token_is_redir()`

를 이용하며 내부적으로 `cmd_new()`를 호출하여 명령 노드를 생성합니다.


## 3. 실행

`session_exec()`는 다음 순서로 실행됩니다.

```text
exec_heredoc()
        │
        ▼
exec_run()
        │
        ▼
cmd_run()
```

`exec_run()`은 명령 리스트를 순회하면서

- `safe_pipe()`로 파이프 생성
- 리다이렉션 적용
- `cmd_run()` 호출

을 수행합니다.

### cmd_run()

`cmd_run()`은 먼저 빌트인 명령인지 검사합니다.

```
echo
cd
pwd
export
unset
env
exit
```

빌트인이라면 해당 함수를 직접 호출하고,

그 외 명령은

1. `PATH`에서 실행 파일 탐색
2. 절대 경로인 경우 그대로 사용
3. `execve(cmd_path, argv, c_ref->envp)` 실행

순으로 처리합니다.
