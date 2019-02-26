#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "飯廳");
        set("long", @LONG
這裏是武館內用餐的地方。屋裏佈置很簡單, 只擺着幾張
桌椅幾個人在一聲不響地吃着。一個廚子在不停的忙碌着，你
可以向他要(serve)食物和水。
LONG);
        set("exits", ([
                "east" : __DIR__"guofu_shilu-4",
        ]));

        set("objects", ([
          	__DIR__"npc/chushi" : 1,
        ]));       
        set("no_fight", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        if ((dir == "east")
           && present("chu shi", environment(me)))
	{
	        if (present("tea", me))
              		return notify_fail(CYN "廚師攔住你道：你還是先把茶"
                                           "喝完再走吧。\n" NOR);

	        if (present("rice", me))
              		return notify_fail(CYN "廚師攔住你道：你還是先把飯"
                                           "吃完再走吧。\n" NOR);

        }
        return ::valid_leave(me, dir);
}