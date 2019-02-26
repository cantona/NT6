// Summer 9/25/96

#include "room.h"
inherit ROOM;

void create()
{
        int i;
        set("short", "塔底");
        set("long", @LONG
這兒是舍利塔底。四壁都是粗糙的巖片，牆腳燃着一盞長明燈，
照射出很微弱的光茫。四周灰塵厚積，蛛網密佈。看來很少有人光顧
這兒。
LONG );
        set("invalid_startroom", 1);
        i = random(10);
        switch (i)
        {
        case 0:
        set("objects", ([
            "/d/xueshan/obj/faling" : 1,
        ]));
        break;
        case 1:
        set("objects", ([
                "/d/xueshan/obj/klguan" : 1,
        ]));
        break;
        case 2:
        set("objects", ([
            "/d/city/obj/stone" : 1,
        ]));
        break;
        case 3:
        set("objects", ([
            "/d/xueshan/obj/lubo" : 1,
        ]));
        break;
        case 4:
        set("objects", ([
                 "/d/xueshan/obj/fojing" : 1,
                "/d/xueshan/obj/fojing2" : 1,
                "/d/xueshan/obj/fojing3" : 1,
                "/d/xueshan/obj/fojing4" : 1,
        ]));
        break;
        case 5:
        set("objects", ([
            DRUG_D("sheli-zi") : 1,
        ]));
        break;
        case 6:
        set("objects", ([
            "/clone/beast/snake" : 1,
        ]));
        break;
        case 7:
        set("objects", ([
                "/d/city/obj/branch2" : 1,
        ]));
        break;
        case 8:
        set("objects", ([
            "/clone/book/book-stone.c" : 1,
        ]));
        break;
        case 9:
        set("objects", ([
            "/d/xueshan/obj/rtlian" : 1,
        ]));
        break;
        }
        set("exits", ([
                "out" : "/d/xueshan/tower",
        ]));
        set("cost", 2);
        setup();
}
int valid_leave(object me, string dir)
{
        if( dir == "out" && present("sheli zi", me) )
        {
                return notify_fail("你不能把舍利子帶走 !\n");
        }
        return ::valid_leave(me, dir);
}       

