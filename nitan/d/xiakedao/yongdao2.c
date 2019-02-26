// yongdao2.c 甬道


inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
這是一條長長的甬道，兩邊點着油燈，光線雖暗，卻也可辨道
路，甬道依着山腹中天然洞穴修鑿而成，此處開鑿的豁然開朗，有
很多的江湖豪傑在此休息。
LONG );
        set("exits", ([
               "south" : __DIR__"shidong1",
               "north" : __DIR__"yongdao1",
        ]));
        set("objects", ([
               "/d/huashan/npc/haoke" : 2,
        ]));
        set("coor/x", -3100);
        set("coor/y", -22070);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}