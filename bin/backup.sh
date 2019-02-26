#!/bin/sh
cd ..
rq=`date +%y%m%d`
tar zcvf backup/nitan$rq.tar.gz nitan
