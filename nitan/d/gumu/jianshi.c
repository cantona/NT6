// Room: /d/gumu/jianshi.c
// Last Modifyed by Winder on Jan. 14 2002

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIC"劍室"NOR);
        set("long", @LONG
一間擺滿兵器的石室，很多種劍都整齊地堆放在地上。周圍的火把
照的整個石室燈火通明，幾個古墓弟子正站在室中仔細挑選自己合手的
兵刃。牆角放着一個木製的護具架，上面掛着些古墓弟子平時防身用的
護具。
LONG        );
        set("exits", ([
                "south" : __DIR__"mudao07",
        ]));

        set("objects", ([
                WEAPON_DIR"changjian" : 2,
                WEAPON_DIR"sword/zhujian" : 2,
                __DIR__"obj/huju-jia" : 1,
        ]));
        set("coor/x", -3180);
        set("coor/y", 30);
        set("coor/z", 90);
        setup();
}

int valid_leave(object ob, string dir)
{
        string* jian = keys(query("objects"));
        object* sword = deep_inventory(ob);

        int i = sizeof(sword), count = 0;
        while (i--)
                if (member_array(base_name(sword[i]), jian) != -1) count++;
        if (count > 1)
                return notify_fail("你一下子拿這麼多劍，別人不要用了嗎？\n");
        return ::valid_leave(ob, dir);
}
