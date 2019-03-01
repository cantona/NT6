// Room: /d/baihuagu/ent.c
// Last Modified by Winder on Mar. 5 2001

inherit ROOM;
void create()
{
        set("short", "小路");
        set("long", @LONG
這是一條羊腸小路，北邊是濃鬱的大森林，不知道你進去之後
還能不能出來。你走著走著，不禁害怕起來。
LONG);
        set("outdoors", "baihuagu");
        set("exits", ([ 
                "north" : __DIR__"tree",
                "southeast" : "/d/jianzhong/shanlu2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -450);
        set("coor/y", -400);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}