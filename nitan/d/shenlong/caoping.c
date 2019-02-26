#include <ansi.h>

inherit ROOM;

string flower()
{
        int n;

        n = random(300);
        if (n == 88) return __DIR__"obj/hua4";
        if (n < 50)  return __DIR__"obj/hua";
        if (n < 80)  return __DIR__"obj/hua2";
        return __DIR__"obj/hua3";
}

void create()
{
        set("short", "草坪");
        set("long", @LONG
這裏是一片青青的草坪，四周開滿了各色的鮮花，一陣涼風吹
過，清新的空氣中傳來幾縷淡淡的花香。
LONG );
        set("exits", ([
		"east" : __DIR__"kongdi",
        ]));
        set("objects", ([
		flower() : 1,
		flower() : 1,
		flower() : 1,
        ]));
        set("outdoors", "shenlong");
        setup();
}

void init()
{
        object me = this_player();

	if (objectp(present("duanchang hua", environment(me)))) 
	{
		me->apply_condition("flower_poison", 30 +
                                    (int)me->query_condition("flower_poison"));

                write(HIG "你只覺一股淡香襲來,頓時腦中一陣麻木！\n" NOR);
        }
}

void reset()
{
        set("objects", ([
		flower() : 1,
		flower() : 1,
		flower() : 1,
        ]));
        ::reset();
}
