inherit ROOM;

void create()
{
        set("short", "黃土路");
        set("long", @LONG
你走在一條塵土飛揚的黃土路上，兩旁盡是陰森森的樹林。這裡
是湖北境界，據說經常有土匪出沒，不可久留。南邊一條小道，通向
密林深處。
LONG );
        set("outdoors", "sanbuguan");
        set("exits", ([
                "north"    : __DIR__"wdroad9",
                "southup"  : __DIR__"tufeiwo1",
                "west"     : __DIR__"slxl1",
        ]));
        set("objects", ([
                __DIR__"npc/xiao_louluo":1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -320);
        set("coor/y", -180);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
