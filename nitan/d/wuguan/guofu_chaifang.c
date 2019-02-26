#include <ansi.h>
inherit ROOM;

void create()
{
    	set("short", "柴房");
    	set("long", @LONG
這間屋裏叮叮哐哐的，你進屋內仔細一看，幾個人在劈柴
火，屋子特別大，屋子一邊堆滿了已經鋸短的木頭，但另一邊
劈好的柴火卻沒有多少。
LONG);
        set("no_fight", 1);
        set("exits", ([
              	"west" : __DIR__"guofu_houyuan",
        ]));
        set("objects", ([
           	__DIR__"npc/guanjia1" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_pi", "pi");

}

int do_pi(string arg)
{

        object me, weapon;
        int costj, costq;

        me = this_player();

        if( query_temp("mark/劈完了", me) )
            	return notify_fail(CYN "柴房管事嚷嚷道：喂喂喂，讓你去覆命，還留"
                                   "在這裏幹嘛？\n" NOR);

        if( query_temp("job_name", me) != "劈柴" )
            	return notify_fail(CYN "柴房管事對你喝道：沒事你瞎折騰什麼？\n" NOR);

        if (me->is_busy())
		return notify_fail("你現在正忙着呢！\n");

        if (me->is_fighting())
		return notify_fail("你正在戰鬥中，無法專心幹活！\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("id", weapon) != "chai dao" )
                return notify_fail(CYN "柴房管事譏笑道：你準備用什麼來劈柴呀，用"
                                   "手嗎？\n" NOR);

        if (! arg || arg != "chai" )
		return notify_fail("你要劈什麼？\n");

        costj=random(query("con", me)/3)+1;
        costq=random(query("str", me)/3)+1;

        if( query("jing", me)<costj
	 || query("qi", me)<costq )
	{
                message_vision(HIR "\n$N" HIR "手一歪，一不小心柴刀竟然劈在自己"
                               "的腿上。\n" NOR, me);
                me->unconcious();
                return 1;
        }
        
        me->receive_damage("jing", costj);
        me->receive_damage("qi", costq);       
        me->start_busy(1 + random(2));

        if (! (int)me->query_condition("wuguan_job")
            && query_temp("mark/劈", me)>10+random(10 )
           && present("chaifang guanshi", environment(me)))
	{
                set_temp("mark/劈完了", 1, me);
                message_vision(CYN "\n柴房管事對$N" CYN "説：乾的不錯，好了，你可"
                               "以去向耶律大爺覆命(" HIY "fuming" NOR + CYN ")了"
                               "。\n" NOR, me);
                return 1;
        }

        message_vision(HIW "$N" HIW "擺正一塊木頭，一刀劈去，將木頭劈為兩片。\n" NOR, me);
        addn_temp("mark/劈", 1, me);

        if ((int)me->query_skill("blade", 1) < 50
           && (int)me->query_skill("strike", 1) < 50
           && me->can_improve_skill("blade")
           && me->can_improve_skill("strike"))
	{  
                write(HIC "你在劈柴過程中對於刀法及掌法有些體會。\n" NOR);
                me->improve_skill("blade",(query("int", me)/6));
                me->improve_skill("strike",(query("int", me)/6));
        }
        return 1;
}
