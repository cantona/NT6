#include <ansi.h>
inherit ROOM;

void create()
{
    	set("short", "木房");
    	set("long", @LONG
一進屋，你就被巨大的轟鳴聲吵住了，這裡堆了好多長的
木頭，準備要做柴火用的，但是在送去柴房前先得把長木頭鋸
短成一截截的。你看見幾個人在費力的鋸著。
LONG);
        set("no_fight", 1);
        set("exits", ([
             	"west" : __DIR__"guofu_houyuan2",
        ]) );
        set("objects", ([
           	__DIR__"npc/guanjia2" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_pi", "ju");
}

int do_pi(string arg)
{ 
        object me, weapon;
        int costj, costq;

        me = this_player();

        if( query_temp("mark/鋸完了", me) )
            	return notify_fail(CYN "木房管事嚷嚷道：喂喂喂，讓你去覆命，還留"
                                   "在這裡幹嘛？\n" NOR);

        if( query_temp("job_name", me) != "鋸木頭" )
            	return notify_fail(CYN "木房管事對你喝道：沒事你瞎折騰什麼？\n" NOR);

        if (me->is_busy())
		return notify_fail("你現在正忙著呢。\n");

        if (me->is_fighting())
		return notify_fail("你正在戰鬥中，無法專心幹活！\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("id", weapon) != "ju zi" )
                return notify_fail(CYN "木房管事譏笑道：你想用什麼來鋸木頭，用手"
                                   "掰嗎？\n" NOR);

        if (! arg || arg != "mutou")
		return notify_fail("你要鋸什麼？\n");

        costj=random(query("con", me)/3)+1;
        costq=random(query("str", me)/3)+1;

        if( query("jing", me)<costj
	 || query("qi", me)<costq )
	{
        	message_vision(HIR "\n突然間木頭竟然斷了，彈起的半截木頭正砸在$N"
                               HIR "頭上。\n", me);
                me->unconcious();
                return 1;
        }

        me->receive_damage("jing", costj);
        me->receive_damage("qi", costq);
        me->start_busy(1 + random(2));

        if (! (int)me->query_condition("wuguan_job")
            && query_temp("mark/鋸", me)>10+random(10 )
           && present("mufang guanshi", environment(me)))
	{
                set_temp("mark/鋸完了", 1, me);
                message_vision(CYN "\n木房管事對$N" CYN "說：幹的不錯，好了，你可"
                               "以去向耶律大爺覆命(" HIY "fuming" NOR + CYN ")了"
                               "。\n" NOR, me);
                return 1;
        }

        message_vision(HIM "$N" HIM "擺正一根木頭，慢慢鋸了起來。\n" NOR, me);
        addn_temp("mark/鋸", 1, me);

        if ((int)me->query_skill("hand", 1) < 50
           && (int)me->query_skill("sword", 1) < 50
           && me->can_improve_skill("hand")
           && me->can_improve_skill("sword"))
	{
                write(HIC "你在鋸木頭的推拉中對手法及劍法有些體會。\n" NOR);
                me->improve_skill("hand",(query("int", me)/6));
                me->improve_skill("sword",(query("int", me)/6));
        }
        return 1;
}
