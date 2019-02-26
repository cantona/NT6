// Room: /wuliang/shanlu5.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "山坡");
        set("long", @LONG
爬上山坡，山路向下迴轉進入一個山坳。那一條條的裊裊青煙原
來都是從山坳裏冒出來的。這裏地勢突兀，正是看山景的好去處。不
過行人到此，見了這的人，恐怕都沒什麼好心情遊山玩水了。
LONG );
        set("outdoors", "wuliang");
        set("exits", ([
                "westdown"  : __DIR__"shanlu6",
                "southdown" : __DIR__"shanlu4",
        ]));
        set("objects", ([
                __DIR__"npc/shennongdizi" : 2,
        ]));
        set("coor/x", -70990);
        set("coor/y", -79980);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}