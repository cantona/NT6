// Room: /heizhao/shanlu6.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
向西走了七八十裡，道路癒來癒窄，再行八九裡，道路兩旁山
峰壁立，中間一條羊腸小徑，僅容一人勉強過去。
LONG );
        set("outdoors", "taoyuan");
        set("no_clean_up", 0);
        set("exits", ([
                "southeast" : "/d/henshan/hsroad6",
                "westup"    : __DIR__"shanlu7",
        ]));
        set("coor/x", -5000);
        set("coor/y", -1300);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}