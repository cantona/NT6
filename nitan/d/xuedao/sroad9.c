inherit ROOM;

void create()
{
        set("short", "雪山山谷");
        set("long", @LONG
山谷裡遍地積雪，四周都是峭壁。只北面有一個出口，東面似乎
有個山洞。
LONG );
        set("exits", ([
                "westdown" : __DIR__"wangyougu",
                "east"     : __DIR__"shandong2",
        ]));
        set("objects", ([
                CLASS_D("xuedao") + "/shengdi" :1,
        ]));
        set("outdoors", "xuedao");
        setup();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (dir == "east" &&
            objectp(guarder = present("sheng di", this_object())))
        {
                return guarder->permit_pass(me, dir);
        }

        return ::valid_leave(me, dir);
}
