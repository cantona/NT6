#include <ansi.h>
inherit ROOM;

void create()
{
    	set("short", "菜地");
    	set("long", @LONG
這裏是塊菜地，由於長期得不到良好的照顧，菜地裏雜草
叢生，種的菜都長勢不好，蔫蔫的，地都荒了。
LONG);
        set("no_fight", 1);
        set("exits", ([
             	"west" : __DIR__"guofu_houyuan3",
        ]));
        set("objects", ([
           	__DIR__"npc/guanjia5" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_chu", "chu");
}

int do_chu(string arg)
{
        object me, weapon;
        int costj, costq;

        me = this_player();

        if( query_temp("mark/鋤完了", me) )
            	return notify_fail(CYN "菜園管事嚷嚷道：喂喂喂，讓你去覆命，還留"
                                   "在這裏幹嘛？\n" NOR);

        if( query_temp("job_name", me) != "鋤草" )
            	return notify_fail(CYN "菜園管事對你喝道：沒事你瞎折騰什麼？\n" NOR);

        if (me->is_busy())
		return notify_fail("你現在正忙着呢！\n");

        if (me->is_fighting())
		return notify_fail("你正在戰鬥中，無法專心幹活！\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("id", weapon) != "chu tou" )
                return notify_fail(CYN "菜園管事譏笑道：你是想用什麼來鋤草呀，用"
                                   "手嗎？\n" NOR);

        if (! arg || arg != "cao" )
		return notify_fail("你要鋤什麼？\n");

        costj=random(query("con", me)/3)+1;
        costq=random(query("str", me)/3)+1;

        if( query("jing", me)<costj
	 || query("qi", me)<costq )
	{
        	message_vision(HIR "\n$N" HIR "鋤着鋤着，結果不小心手一滑，鋤在"
                               "了自己的腳上。\n" NOR, me);
                me->unconcious();
                return 1;
        }

        me->receive_damage("jing", costj);
        me->receive_damage("qi", costq);       
        me->start_busy(1 + random(2));

        if (! (int)me->query_condition("wuguan_job")
            && query_temp("mark/鋤", me)>10+(random(10) )
           && present("caiyuan guanshi", environment(me)))
	{
                set_temp("mark/鋤完了", 1, me);
                message_vision(CYN "\n菜園管事對$N" CYN "説：乾的不錯，好了，你可"
                               "以去向耶律大爺覆命(" HIY "fuming" NOR + CYN ")了"
                               "。\n" NOR, me);
                return 1;
        }

        message_vision(HIY "$N" HIY "揮起鋤頭，對着地上的雜草鋤了起來。\n" NOR, me);
        addn_temp("mark/鋤", 1, me);

        if ((int)me->query_skill("staff", 1) < 50
           && (int)me->query_skill("cuff", 1) < 50
           && me->can_improve_skill("staff")
           && me->can_improve_skill("cuff"))
	{  
                write(HIC "你在鋤草過程中對於杖法及拳法有些體會。\n" NOR);
                me->improve_skill("staff",(query("int", me)/6));
                me->improve_skill("cuff",(query("int", me)/6));
        }
        return 1;
}
