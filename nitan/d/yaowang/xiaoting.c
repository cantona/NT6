inherit ROOM;

void create()
{
        set("short", "書房內廳");
        set("long", @LONG
這裡是書房內廳，靠牆放著一排書架，窗前的小幾上一個小
書童正在其間抄寫著什麼。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
        "out": __DIR__"shufang",
        ]));

        set("objects", ([
                __DIR__"npc/sn" : 1,
        ]));
        setup();

}

int valid_leave(object me,string dir)
{
        if(!me)
                return 0;

        if(dir == "out")
        {
                if(sizeof(filter_array(deep_inventory(me),(: $1->is_yaowang_book() :))))
                        return notify_fail("書奴悄悄地對你說，這些書別拿出去呀!\n");
        }

        return ::valid_leave(me,dir);
}

