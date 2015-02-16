# run_external
Introduction
============

`run_external` is MySQL UDF function which runs external command. You should simply specify command like you'd do it ir run a command in sheel.

Command does not output anything, but excutes by itself. You can redirect output to file.

*Warning*: Please be aware that anyone can use this to run OS commands with the privileges of the useraccount which is used for MySQL.

    mysql> SHOW GRANTS;
    +---------------------------------------------------------------------------------------------------------------+
    | Grants for nobody@localhost                                                                                   |
    +---------------------------------------------------------------------------------------------------------------+
    | GRANT USAGE ON *.* TO 'nobody'@'localhost' IDENTIFIED BY PASSWORD '*6C387FC3893DBA1E3BA155E74754DA6682D04747' |
    +---------------------------------------------------------------------------------------------------------------+
    1 row in set (0.00 sec)
    
    mysql> SELECT run_external('date > /tmp/date123');
    +-------------------------------------+
    | run_external('date > /tmp/date123') |
    +-------------------------------------+
    |                                   1 |
    +-------------------------------------+
    1 row in set (0.01 sec)
    
    mysql> \! cat /tmp/date123
    Mon Feb 16 11:09:29 CET 2015


Compiling
=========

Build uses CMake. To compile, run:

    cmake . -DMYSQL_DIR=/path/to/mysql/installation
    make

Installing
==========

Copy `librun_external.so` into plugin directory of your MySQL server, then login and type:

    CREATE FUNCTION run_external RETURNS INT SONAME 'librun_external.so';
    
Uninstallation
==============

Connect to MySQL command line client and run:

    DROP FUNCTION run_external;

Usage examples
==============

    mysql> SELECT run_external('date >$HOME/tmp/run_external.test');
    +---------------------------------------------------+
    | run_external('date >$HOME/tmp/run_external.test') |
    +---------------------------------------------------+
    |                                                 1 |
    +---------------------------------------------------+
    1 row in set (0.01 sec)
    mysql> \q
    Bye
    Svetas-MacBook-Pro:mysql-test sveta$ cat $HOME/tmp/run_external.test
    Wed Jan 28 23:00:41 GMT 2015

    mysql> SELECT run_external(concat('$HOME/build/mysql-trunk/bin/mysqldump  --socket=', @@socket, ' --all-databases > /Users/sveta/src/BACKUPDIR/plugin_test/backup_test.sql'))\G 
    *************************** 1. row ***************************
    run_external(concat('$HOME/build/mysql-trunk/bin/mysqldump  --socket=', @@socket, ' --all-databases > /Users/sveta/src/BACKUPDIR/plugin_test/backup_test.sql')): 1
    1 row in set (0.54 sec)

    mysql> \q
    Bye
    Svetas-MacBook-Pro:mysql-test sveta$ ../bin/mysql -uroot -h127.0.0.1 -P13000 </Users/sveta/src/BACKUPDIR/plugin_test/backup_test.sql
    Svetas-MacBook-Pro:mysql-test sveta$ wc -l /Users/sveta/src/BACKUPDIR/plugin_test/backup_test.sql
        1133 /Users/sveta/src/BACKUPDIR/plugin_test/backup_test.sql
    Svetas-MacBook-Pro:mysql-test sveta$ head /Users/sveta/src/BACKUPDIR/plugin_test/backup_test.sql
    -- MySQL dump 10.13  Distrib 5.7.6-m16, for osx10.10 (x86_64)
    --
    -- Host: localhost    Database: 
    -- ------------------------------------------------------
    -- Server version	5.7.5-labs-preview-debug-log
    
    /*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
    /*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
    /*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
    /*!40101 SET NAMES utf8 */;
