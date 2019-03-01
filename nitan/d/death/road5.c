#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", HIR "【鬼門大道】" NOR);
       set("long", HIR @LONG

                    鬼     門     大     道

    你走在一條陰森森的路上，濃濃的霧環繞在你的四周，好像永遠都
不會散去似的，整條路前後只看到零星的幾盞燈籠……


LONG NOR );
        set("exits", ([
                "north" : "/d/death/road6",
                "south" : "/d/death/road4",
        ]));

        set("no_fight", 1);
        set("no_sleep_room", 1);

        setup();
}

int valid_leave(object me, string dir)
{
        int i;
        if (dir == "north") {
                i=query_temp("long_road", me);
                i = i + 1;
                if (i == 35) {
                delete_temp("long_road", me);
                return 1;
                }
                else {
                        set_temp("long_road", i, me);
                        return notify_fail( HIB "\n你走著走著……發現四周景色居然都沒有變……\n" NOR);
                }
        }
        else {
        if (dir == "south") {
                delete_temp("long_road", me);
                return 1;
                }
        return 1;
        }
}
