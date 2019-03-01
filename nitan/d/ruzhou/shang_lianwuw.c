#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這是商家堡的練武場，空闊的場地上舖滿了細細的黃土，正
好適合演武。四面有幾個商家堡的弟子正在練武。場地邊上掛著
幾個大沙袋(shadai)，不知有什麼用處。
LONG);
        set("item_desc", ([
                "shadai" : WHT "幾個沉重的沙袋，可以試著打打(jida)看。\n" NOR,
        ]));

        set("exits", ([
                "east"  : __DIR__"shang_qgc",
        ]));
	set("coor/x", -6760);
	set("coor/y", 1850);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_jida", "jida");
}

int do_jida(string arg)
{
        object me;
        object weapon;
        me = this_player();

        if (! living(me) || arg != "shadai")
                return notify_fail("你要擊打什麼？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙著。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(WHT "你操起手中兵器向沙袋砍去，“哧”的一聲沙袋應"
                                   "聲而破，裡面的沙流了一地。\n" NOR);

        if ((int)me->query_skill("cuff", 1) < 30
           || (int)me->query_skill("strike", 1) < 30)
                return notify_fail("你擊打半天，手都打出繭了，可還是什麼都沒學到，可"
                                   "能是拳掌等級太低的緣故。\n");

        if ((int)me->query_skill("cuff", 1) >= 120
           && (int)me->query_skill("strike", 1) >= 120)
                return notify_fail("你對著沙袋擊打了一會兒，發現這裡已經不能再提高什"
                                   "麼了。\n");

        if( query("qi", me)<40 )
                return notify_fail("你現在累得胳膊都抬不起來了，先休息一會兒吧。\n");

        me->receive_damage("qi", 30);

        if (me->can_improve_skill("cuff")
           && (int)me->query_skill("cuff", 1) < 120)
                me->improve_skill("cuff",query("con", me)*2);

        if (me->can_improve_skill("strike")
           && (int)me->query_skill("strike", 1) < 120)
                me->improve_skill("strike",query("con", me)*2);

        me->start_busy(random(2));
        message_vision(WHT "\n$N" WHT "站穩馬步，一掌一拳對著沙袋打了起來。\n" NOR, me);
        write(HIC "你在擊打過程中領悟了不少「基本拳法」及「基本掌法」的竅門。\n" NOR);
        return 1;
}