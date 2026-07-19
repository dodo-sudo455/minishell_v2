# /shell

## redirection

```c
static void	_open_redir(t_ctx *c_ref, t_redir *red_ref)
{
	int	fd;

	if (red_ref->t == REDIR_IN)
		fd = open(red_ref->s, O_RDONLY);
	else if (red_ref->t == REDIR_OUT)
		fd = open(red_ref->s, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (red_ref->t == REDIR_APPEND)
		fd = open(red_ref->s, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
		perror("minishe ~~");
		exit();
}
```

## here document

```bash
cat << $USER
cat << '$USER'
cat << "$USER"
```
전부 종료 구분자는 `$USER`
대신, 따옴표로 감싸지지 않은 경우 heredoc 본문에서 환경 변수 확장 나타남

## `exec_heredoc.c`

1. 