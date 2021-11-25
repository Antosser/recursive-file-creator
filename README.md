# Recursive File Creator
Creates a folder with x folders with x folders inside x folder including x folders ... ... ... of x files

## Syntax
`recursive-file-creator [-name] [-depth] [-size] [-filecount] [-c] [-bin]`

### Parameters
- **-name** - Name of the created folder
- **-depth** - How deep the files are
- **-size** - Size of each file in bytes
- **-c** - Number of folders/files in each subdirectory
- **-hex** - Whether to give the folders/file a hexedecimal name for example 00c3f34b

## Limitations
You are limited to 4'294'967'296 (2^32) files/folders in a subdirectory and 18'446'744'073'709'551'616 (2^64) files in total
