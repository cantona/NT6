// Room: /d/jianzhong/qzroad1.c

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
山路終于走到了盡頭。一片茂密的樹林出現在你的眼前。
LONG
        );

        set("exits", ([
                "north" : __DIR__"shulin1",
                "west" : __DIR__"shanlu2",
        ]));

        set("outdoors", "jianzhong");
        set("coor/x", -400);
        set("coor/y", -490);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}