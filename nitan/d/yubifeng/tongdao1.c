// /yubifeng/tongdao1.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "通道");
        set("long", @LONG
山洞通道里盤旋曲折，接連轉了幾個彎，仍是未到盡頭。洞中到處
是千年不化的尖冰，有些處所的冰條如刀劍般鋒鋭突出。
LONG );
        set("exits", ([
                "up"   : __DIR__"yuanfengding",
                "east" : __DIR__"tongdao2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 6100);
        set("coor/y", 5120);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}