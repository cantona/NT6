// Room: /d/fuzhou/xidajie1.c
// may. 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
這裏是福州老城的西大街。大街兩旁三三兩兩幾位小販正在叫賣，
街的南邊就是南后街了。
LONG );

        set("exits", ([
                "east"  : __DIR__"dongjiekou",
                "west"  : __DIR__"xidajie",
                "south" : __DIR__"nanhoujie1",
        ]));
        set("objects", ([
                __DIR__"npc/xiaofan" : 1,
        ]));
        set("outdoors", "fuzhou");
	set("coor/x", -90);
	set("coor/y", -6180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}