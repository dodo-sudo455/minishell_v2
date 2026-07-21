# Pseudo Code: Exec

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
	ctx_update_status(ctx, last_status)

exec_run_cmd(ctx, cmd, infd, outfd):
	if (is_built_in(cmd)):
		tmp_stdin = dup(0)
		tmp_stdout = dup(1)
	
	if (infd >= 0):
		dup2(infd, 0)
	if (outfd >= 0):
		dup2(outfd, 1)

	_handle_redir(cmd.redlst)

	res := cmd_run(..)

	if (is_built_in(cmd)):
		dup2(tmp_stdin, 0)
		dup2(tmp_stdout, 1)
		return (res);

	if (res == ERROR)
		exit(1)
	else
		exit(0)

_handle_redir(ctx, redlst):
	for node in range cmd.redlst:
		redir := node.data
		fd := open(redir.str)
		
		if (redir.type == IN || redir.type == HDOC):
			dup2(fd, STDIN)
		else:
			dup2(fd, STDOUT)
```
