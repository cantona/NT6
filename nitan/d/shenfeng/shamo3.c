#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "大漠風沙");
        set("long", @LONG
你處在酷熱如烘爐的沙漠中，熱的令人連氣都透不出。除
了滿耳呼呼的風聲什麼也聽不見。除了滿眼滾滾的飛沙什麼也
看不見；天地間彷彿只剩下你一個人。你腳下緩緩而動的流沙
給你如履薄冰的感覺。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                "east" : __DIR__"shamo2",
                "west" : __DIR__"lvzhou",
        ]));
        setup();        
}

void init()
{
        object me = this_player();

        if (userp(me))
                call_out("kill_user", 1, me);
}

int kill_user(object me)
{
        object ob;

        if (! me || environment(me) != this_object())
                return 1;

        if (! present("tu ying", this_object()))
        {
                    message("vision", HIR "\n突然間，只見一個黑影從天"
                                  "而降。\n" NOR, this_object());

                ob = new("clone/quarry/ying");
                ob->move(this_object());
                ob->kill_ob(me);
        }
}

int valid_leave(object me, string dir)
{
        int current_water;
        current_water=query("water", me);

        if (userp(me) && current_water == 0)
        {
                write(HIY "你已經感到快不行了，冥冥中覺得有人把你"
                      "抬到龍門客棧。\n" NOR);
                me->unconcious();
                me->move(__DIR__"longmen");
        } else

        if (current_water > 0 && current_water < 20)
        {
               write(HIR "你過度缺水，渴得眼冒金星。\n" NOR);
               set("water", 0, me);
        }

        if (current_water >= 20)
               addn("water", -20, me);

        return 1;
}