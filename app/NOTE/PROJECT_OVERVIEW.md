# 프로젝트 개요

## 디렉토리 구조
```
minishell
├── app/
│   └── main.c                  # 앱 엔트리
├── src/
│   ├── shell/                  # 셸 동작
│   │   ├── prompt
│   │   ├── parser
│   │   ├── executor
│   │   └── heredoc
│   ├── lib/                    # 빌트인 및 라이브러리 레벨 로직
│   │   ├── cd
│   │   ├── echo
│   │   ├── export
│   │   └── ...
│   └── def/                    # 컨텍스트 관리, 안전 래퍼, 에러·GC
├── include/
│   ├── def.h
│   └── shell.h
├── libft/                      # libft 라이브러리 유틸
└── Makefile                    # 빌드 규칙
```

## 모듈 경계 및 인터페이스
- 컨텍스트(`t_ctx`): 전역 상태, 환경변수 리스트, 에러/상태 저장
  - 정의: include/def.h
  - 초기화/소멸: `ctx_init`, `ctx_clear` (src/def/ctx.c)
- 입력/프롬프트
  - 인터페이스: `prompt(t_ctx*, char**)` — 안전한 readline 래퍼를 통해 입력을 받고 히스토리에 추가 (src/shell/prompt.c, src/def/safe.c)
- 파서
  - 단계: 토큰화 -> 확장(환경변수) -> 스플릿 -> 쿼트 처리
  - 공개 함수: `parse_tokenize`, `parse_expand`, `parse_split_word`, `parse_quote` (src/shell/session_run.c에서 호출 순서 확인)
- 실행 엔진
  - 인터페이스: `exec`, `exec_run`, `exec_run_cmd`, `exec_heredoc`
  - 책임: 파이프 생성, 포크, 리다이렉션, child/parent 시그널 설정 (src/shell/exec_run.c)
- 빌트인
  - 각 기능은 `cmd_built_*`로 분리되어 있으며 실행자는 `cmd_run`에서 빌트인 판별 후 직접 호출 (src/shell/cmd_run.c)

## 에러 처리 및 로깅 정책
- 에러 타입: `enum e_error`로 정의된 여러 에러 코드(include/def.h)
- 에러 기록: `seterr(c_ref, err, errcmd, errarg)`로 컨텍스트에 에러 정보 저장, 이후 `geterr`/`logerr`로 출력/처리
- 치명적 오류: `panic(c_ref, FATAL_*, msg)` 호출로 즉시 종료 또는 디버그 동작(src/def/panic.c)
- 출력/로깅:
  - 사용자 수준 메시지: 표준 출력/표준 에러 사용(`util_puterr`, `perror` 등)
  - 테스트·디버깅용 로깅은 `test/`내 유틸로 기록
- 예외/종료 코드 규약: 외부 프로그램 실행 실패는 `127`(not found) 또는 `126`(permission) 등 쉘 관습을 따름 (src/shell/cmd_run.c)
