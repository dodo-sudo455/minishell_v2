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
