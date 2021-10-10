# Test for `minitalk`

## Compile
```shell
$ gcc -o server server.c
$ gcc -o client client.c
```

## Execute
### Usage
```shell
$ ./server
$ ./client [pid] [signum]
```

1. Run the `server`
2. Check the `server`'s PID
3. Run the `client` with `pid` and `signum`
4. Check the signal the `server` receives from the `client`.

#### `[signum]`
- `30`: `SIGUSR1`
- `31`: `SIGUSR2`

### Example
1. terminal window 1
	```shell
	$ ./server
	SERVER PID: 30000
	# After running the client...
	Received Signal: SIGUSR1(30)
	```
2. terminal window 2
	```shell
	$ ./client 30000 30
	# After running the server...
	Send signal: '30' to 31755
	```

