// Room: /d/jianzhong/qzroad1.c

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在一條山路上。路邊的樹木逐漸茂密起來，山路越發地窄了。
LONG
        );

        set("exits", ([
                "east" : __DIR__"shanlu3",
                "west" : __DIR__"shanlu1",
                "northwest" : "/d/baihuagu/ent",
        ]));

        set("outdoors", "jianzhong");
        set("coor/x", -420);
        set("coor/y", -490);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}