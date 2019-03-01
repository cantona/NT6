#include <ansi.h> 
inherit ROOM;

int exercise_improve();
        
void create()
{
        set("short", "玄冰室");
        set("long", @LONG
這是昔日天山童姥修練內功的地方。屋子正中有一塊千年玄冰 (
ice)，冰上冒出絲絲寒氣，屋裡因此寒氣逼人，你不由得打了一個寒
顫。
LONG );
        set("exits", ([
                "east" : __DIR__"changl13",
        ]));

        set("item_desc", ([
                "ice" : HIW "\n這是一塊採自天山之巔的千"
                        "年玄冰，奇寒無比。\n\n" NOR,
        ]));

        set("exercise_improve", (: exercise_improve :));

        setup();
}

int exercise_improve()
{
        object me;

        me = this_player();

        if (me->query_skill("bahuang-gong", 1) >= 10)
        {
                if (random(5) == 0)
                        tell_object(me, HIW "\n你運用八荒六合惟我獨尊功"
                                        "抵御寒氣，緩緩行功。\n");
                return me->query_skill("force") / 10;
        }

        tell_object(me, HIW "\n你凍的牙齒直打顫，丹田內息也是一陣陣的混"
                        "亂。\n" NOR);
        return -20;
}