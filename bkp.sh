#!/bin/sh
echo "[01;32mBackuping started. If you don't have USB flash drive labeled BACKUPS in any USB port, it will fail.[00m"
mkdir /media/cat/BACKUPS/backup
cp * /media/cat/BACKUPS/backup
