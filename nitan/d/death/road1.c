#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", HIR "【鬼門大道】" NOR);
       set("long", HIR @LONG

                    鬼     門     大     道

    你走在一條陰森森的路上，濃濃的霧環繞在你的四周，好像永遠都
不會散去似的。往南看去你勉強可以分辨出一個城樓的模樣，往北隱約
可以看到幾盞燈籠，在濃霧中顯得格外的詭異，路的兩旁各有一棟木造
的建築，門都是半開的，但你看不清楚裏面有什麼。


LONG NOR );
        set("exits", ([
                "north" : "/d/death/road2",
                "south" : "/d/death/gateway",
                "west" : "/d/death/inn1",
                "east" : "/d/death/inn2",
        ]));

        set("no_fight", 1);
        set("no_sleep_room", 1);

        setup();
        replace_program(ROOM);
}