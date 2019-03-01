// Room: /d/fuzhou/shiqiao.c
// Date: May 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "石橋");
        set("long", @LONG
這是城裡一條普普通通的石橋。大概總有幾百年歷史了，橋側生滿
青苔，橋下有小孩戲水，岸邊洗衣的母親大聲呵斥著自己的孩子。
LONG );

        set("exits", ([
                "west"  : __DIR__"xiangyang",
                "east"  : __DIR__"nanmendou",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "fuzhou");
	set("coor/x", -90);
	set("coor/y", -6200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}