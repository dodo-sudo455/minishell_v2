# Pseudo Code: Exec

## `status`
두가지 경우가 있음
- 정상 종료: `exit(code)` 또는 `return code`로 끝난 경우
- 시그널 종료

정상 종료인 경우
- `WIFEXITED(status)`: 정상 종료면 `true` 아니면 `false` 반환
- `WEXITSTATUS(status)`: `exit(code)`에 인자로 전달된 코드 반환

시그널 종료인 경우
- `WIFSIGNALED(status)`: 시그널 종료면 `true` 반환
- `WTERMSIG(status)`: 시그널 번호 반환


## exec_run
```go
exec_run(ctx, cmdlst):
	if (cmdlst.size == 1 && cmdlst[0].is_builtin()):
		exec_run_cmd(ctx, cmdlst[0], NULL)
		
	set_sig_parent()

	prev_readfd := -1
	pipefd := int[2]
	
	for node in range cmdlst:
		cmd := node.data
		
		if (node.next):
			pipe(pipefd)
		cmd.pid = fork()
		if (cmd.pid == 0):
			exec_run_cmd(ctx, cmd, prev_readfd, pipefd[1])
		prev_readfd = pipefd[0]
	
	last_status := wait_all(cmdlst)
	if (WIFEXITED(&last_status))
	
	ctx_update_status(ctx, last_status)


exec_run_cmd(ctx, cmd, infd, outfd):
	
	set_sig_child()
	
	dup2(infd, STDIN)
	dup2(outfd, STDOUT)
	
	for node in range cmd.redlst:
		redir := node.data
		fd := open(redir.str)
		
		if (redir.type == IN || redir.type == HDOC):
			dup2(fd, STDIN)
		else:
			dup2(fd, STDOUT)
	
	res := cmd_run(ctx, cmd)
	if (res == ERROR)
		exit(1)
	else
		exit(0)
```
