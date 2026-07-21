# Pseudo Code: Parse

## parse_split_word
```go
parse_split_word(ctx, toklst):
	for node in range toklst:
		token := node.data;
		if token.type != WORD:
			continue;
		
		sp := split(token.str);
		for s in range sp:
			toklst.insert(token_make(WORD, s))
```
