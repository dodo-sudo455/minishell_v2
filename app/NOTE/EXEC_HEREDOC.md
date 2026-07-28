# exec_heredoc.c 동작 문서

## 개요

`exec_heredoc.c`는 명령 리스트(`cmdlst`)에서 Here Document(redirection `<<`)를 찾아 처리합니다. 각 `t_cmd`의 `redlst`를 검사하여 `REDIR_HDOC`가 발견되면 별도 프로세스를 만들어 사용자 입력을 읽고 임시 파일로 저장합니다.

## 전체 흐름

### exec_heredoc():
1. `cmdlst_ref` 순회
2. 각 명령(`t_cmd`)의 `redlst`에서 `REDIR_HDOC` 타입 찾기
3. heredoc 발견 시 `_handle_cmd` 호출

### _handle_cmd():
1. 부모 프로세스의 `SIGINT`를 `SIG_IGN`로 설정
2. `_handle_heredoc` 호출
3. 

### _handle_heredoc():
1. 임시 파일 생성
	- `_heredoc_child()`에게 쓰기 파일 디스크립터(`wfd`) 전달
2. 자식 프로세스를 포크하여 입력 받음
3. `waitpid`로 자식 프로세스 종료 대기 및 종료 코드 수거

### _heredoc_child():
1. `SIGINT`를 `SIG_DFL`로 설정
2. `_heredoc_readline`호출

### _heredoc_readline():
1. 입력된 문자열을 `wfd`에 출력
	- `is_expand == true`면 본문에 입력된 환경변수 확장

## 임시 파일 처리

### 파일명

- 상수 `HEREDOC_FNAME`는 `/tmp/minishell-heredoc`로 정의되어 있습니다.

### 파일 열기 순서

- 쓰기 모드 파일 디스크립터를 `wfd`에 저장
	- 자식에서 종료 직전에 닫음
- 읽기 모드 파일 디스크립터를 `red_ref->docfd`에 저장
	- 이후 실행부에서 리다이렉션 처리 시 사용
- `unlink(HEREDOC_FNAME)`로 디렉터리 엔트리 삭제

> 임시 파일이 디스크에 노출되지 않도록 하면서도 부모/자식 프로세스가 열린 fd로 안전하게 접근할 수 있음

## 시그널 처리

### 부모 측 SIGINT 처리

- `_handle_cmd`에서 `SIGINT`를 `SIG_IGN`으로 설정
- 기존 `SIGINT` 핸들러는 `old_int`에 백업
- `_handle_heredoc`이 종료된 뒤 `safe_sigaction(c_ref, SIGINT, &old_int, NULL)`로 원래 핸들러를 복원

### 자식 측 SIGINT 처리

- `_heredoc_child`에서 `SIGINT` 핸들러를 `SIG_DFL`(기본 동작)로 복원
	- 즉, 사용자가 `Ctrl+C` 입력 시 heredoc 입력 종료됨
- 부모가 `waitpid`로 종료 상태를 확인 및 반환

### 예외 상황

- `SIGINT`가 자식에서 발생하면 `_handle_heredoc`은 종료 상태 `130`을 반환할 가능성이 있습니다.
- `_handle_cmd`는 이 값을 `ERROR_ABORT`로 변환하여 히어도크 처리 전체를 중단합니다.

## heredoc 입력 로직

### 종료 구분자 비교

- `_heredoc_readline`는 `safe_readline(c_ref, "> ")`를 반복 호출
- 입력이 `NULL`이면 EOF로 처리하고 경고 메시지를 출력한 뒤 `exit(0)`
- 입력 문자열이 `delim`과 정확히 일치하면 heredoc 입력을 종료

### 확장 동작

- `is_expand == true`이면 각 입력에 대해 `ctx_expand(c_ref, &input)`수행
	- `is_expand`는 `_heredoc_child`에 `!red_ref->has_quote`로 전달됨
- 따라서 구분자가 큰따옴표/작은따옴표로 감싸져 있으면 확장 비활성화됨

### 파일 쓰기

- 각 입력 줄은 `write(fd, input, ft_strlen(input))`로 파일에 저장됨
- 줄 끝에 `\n`을 추가
- 쓰기 실패 시 `panic(c_ref, FATAL_INTERNAL, "heredoc write failed")`로 치명적 오류 처리

## 에러 및 상태 반환

- `_handle_heredoc`가 자식 프로세스 종료 상태를 반환합니다.
- `WIFEXITED(status)`인 경우 `WEXITSTATUS(status)`를 리턴합니다.
- `WIFSIGNALED(status)`인 경우 `128 + WTERMSIG(status)`를 리턴합니다.
- `_handle_cmd`는 `status == 130`이면 `ERROR_ABORT`를 반환합니다.
- `exec_heredoc`는 `_handle_cmd`에서 `ERROR_ABORT`가 발생하면 즉시 `ERROR_ABORT`를 반환합니다.

## 설계 요약

- 임시 파일은 `/tmp/minishell-heredoc`로 생성되고 즉시 `unlink`되어 경로 노출을 최소화합니다.
- 부모는 히어도크 본문 쓰기용 fd와 읽기용 fd를 모두 열어 둡니다.
- 자식은 히어도크 입력 시 `SIGINT` 기본 동작을 사용하고, 부모는 SIGINT를 무시하여 셸이 중단되지 않도록 합니다.
- `safe_*` 래퍼를 통해 시스템 호출 실패 시 정리 또는 비상 종료를 관리합니다.

## 주의 사항

- 현재 구현은 임시 파일 이름이 고정되어 여러 히어도크 동시 실행 시 충돌이 발생할 수 있습니다.
- `exit(0)` 호출은 자식 프로세스 내에서만 안전해야 하므로, `safe_readline` 실패 시 부모 로직과 분리되어 있는지 주의해야 합니다.
- `unlink` 후에도 열린 fd를 유지하므로 시스템에서 파일이 올바르게 청소됩니다.
