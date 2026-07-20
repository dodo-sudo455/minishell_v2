# Pseudo Code: Parse

## parse_tokenize2
```go
parse_tokenize2(ctx, toklst):
	for node in range toklst:
		token := node.data;
		if token.type != WORD:
			continue;
		
		sp := split(token.str);
		for s in range sp:
			toklst.insert(token_make(WORD, s))
```
