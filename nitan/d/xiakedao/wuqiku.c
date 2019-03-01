// wuqiku.c
inherit ROOM;

void create()
{
        set("short", "武器庫");
        set("long", @LONG
這裡是俠客島的武器庫，架上擺滿了各種武器，任由來島的武士
們挑選。
LONG );
        set("exits", ([
                "east" : __DIR__"dating",
        ]));
        set("objects", ([
                WEAPON_DIR"sword/zhujian" : 2,
                WEAPON_DIR"changjian" : 2,
                WEAPON_DIR"changbian" : 1,
                WEAPON_DIR"gangdao" : 1,
                WEAPON_DIR"whip/fuchen" : 1,
                "/d/city/obj/zhubang" : 2,
                "/d/city/obj/duanjian" : 1,
        ]));
        set("coor/x", -3090);
        set("coor/y", -22110);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}