SET SSDIR=\\DIASBACK\WF\VSS
SET SSUSER=LIVOV
REM there is no password
REM if there is password, it's possible to use -Yuser,pass syntax
ss cp "$/LVOV/DevHelper"
ss Get *
