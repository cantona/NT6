inherit ROOM;
#include <ansi.h>

void create()
{
    set("short", "馬房");
    set("long", @LONG
這裡是郭府內的馬房，馬房裡面臭烘烘的，還養了幾十匹
馬。你看過去，馬身上都很臟了，早該洗洗了，馬房的旁邊有
個水池，裡面有些清水。
LONG);
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"guofu_houyuan2",
        ]));
        set("objects", ([
           	__DIR__"npc/guanjia3" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_sao", "sao");        
}

int do_sao(string arg)
{     
        object me, weapon;
        int costj, costq;

        me = this_player();

        if( query_temp("mark/掃完了", me) )
            	return notify_fail(CYN "馬房管事嚷嚷道：喂喂喂，讓你去覆命，還留"
                                   "在這裡幹嘛？\n" NOR);

        if( query_temp("job_name", me) != "打掃馬房" )
            	return notify_fail(CYN "馬房管事對你喝道：沒事你瞎折騰什麼？\n" NOR);

        if (me->is_busy())
		return notify_fail("你現在正忙著呢！\n");

        if (me->is_fighting())
		return notify_fail("你正在戰鬥中，無法專心幹活！\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("id", weapon) != "sao zhou" )
                return notify_fail(CYN "馬房管事譏笑道：你是想用什麼來打掃呀，用"
                                   "手嗎？\n" NOR);

        if (! arg || arg != "mafang")
		return notify_fail("你要打掃什麼？\n");

        costj=random(query("con", me)/3)+1;
        costq=random(query("str", me)/3)+1;

        if( query("jing", me)<costj
	 || query("qi", me)<costq )
	{
             	message_vision(HIR "\n$N" HIR "腳一滑，結果不小心滑倒在糞堆裡，吃"
                               "了一大口馬糞。\n" NOR, me);
             addn("food", 100, 	me);
             	me->unconcious();
             	return 1;
        }
        
        me->receive_damage("jing", costj);
        me->receive_damage("qi", costq);       
        me->start_busy(1 + random(2));

        if (! (int)me->query_condition("wuguan_job")
            && query_temp("mark/掃", me)>10+random(10 )
           && present("mafang guanshi", environment(me)))
	{
              set_temp("mark/掃完了", 1, 	me);
              	message_vision(CYN "\n馬房管事對$N" CYN "說：幹的不錯，好了，你可"
                               "以去向耶律大爺覆命(" HIY "fuming" NOR + CYN ")了"
                               "。\n" NOR, me);
              	return 1;
        }

        message_vision(HIM "$N" HIM "開始打掃馬房，臭味使你不由閉緊了呼吸。\n" NOR, me);
        addn_temp("mark/掃", 1, me);

        if ((int)me->query_skill("claw", 1) < 50
           && (int)me->query_skill("club", 1) < 50
           && me->can_improve_skill("claw")
           && me->can_improve_skill("club"))
	{
                write(HIC "你在掃地過程中對爪法及棍法有些體會。\n" NOR);
                me->improve_skill("claw",(query("int", me)/6));
                me->improve_skill("club",(query("int", me)/6));
        }
        return 1;
}
