#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", RED "【地陰通道】" NOR);
       set("long", RED @LONG

                    地     陰     通     道

    一條由陰司向下延伸的階梯，不知道通往何方，階梯深不見底，仿
佛永遠沒有止境一般。

LONG NOR );
        set("exits", ([
                "up" : __DIR__"lunhuisi",
                "down" : __DIR__"diyin_road2",
        ]));

        set("no_sleep_room", 1);

        set("no_magic", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        int i;
        if (dir == "down")
        {
                i=query_temp("long_road", me);
                i = i + 1;

                if (i == 10)
                {
                        delete_temp("long_road", me);
                        return 1;
                }
           else {
                        set_temp("long_road", i, me);
                        return notify_fail( RED "\n你向下走着這深不見底的階梯……"
                                            "只覺階梯似乎在無限延伸，永遠到達不了盡頭"
                                            "一般。\n" NOR);
                }
        }
   else {
                if (dir == "up")
                {
                        delete_temp("long_road", me);
                        return 1;
                }
        return 1;
        }
}