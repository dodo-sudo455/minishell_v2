# Built-in Pseudo Codes

## print_error
```go
print_error():
```

## echo
```go
int cmd_built_echo(ctx, cmd):
	n_opt := is_n_opt(cmd.arglst)

	for arg in cmd.arglst[1:]:
		if arg.is_flag:
			continue
		printf("%s", arg)
	
	if n_opt:
		printf("\n")
```

## cd
```go
int cmd_built_cd(ctx, cmd):
	if cmd.arglst.is_empty:
		chdir(ctx_getenv(ctx, "HOME"))
		return
	
	if cmd.arglst.size >= 3:
		print_error("minishell: cd: too many arguments")
	
	chdir(cmd.arglst[1])
```

## pwd
```go
int cmd_built_pwd(ctx, cmd):
	path := getcwd(path, PATH_MAX)
	if path == NULL:
		path = ctx_getenv(ctx, "PWD")
		if path == NULL:
			perror("minishell: pwd: error retrieving current directory")
			return (1)

	printf("%s\n", path)
```

## export
```go
int cmd_built_export(ctx, cmd):
	if cmd.arglst.size == 1:
		print_declare_x(ctx.envlst)
		return
	
	for arg in cmd.arglst[1:]:
		if strchr(arg, '='):
			sp := split(arg, '=')
			key := sp[0]
			val := sp[1]
		
		else:
			key := arg
			val := NULL // or ""
		
		if is_format_wrong(key):
			perror("minishell: export: not a valid identifier")
			return 1
		
		ctx_setenv(ctx, key, val)
```

## unset
```go
int cmd_built_unset(ctx, cmd):
	
```

## env
```go
int cmd_built_env(ctx, cmd):
	
```

## exit
```go
int cmd_built_exit(ctx, cmd):
	
```
