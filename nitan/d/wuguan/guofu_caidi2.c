#include <ansi.h>
inherit ROOM;

void create()
{
    	set("short", "菜地");
        set("long", @LONG
這裡是塊菜地，菜地旁有幾口大缸，裡面盛滿了水，可是
菜地看起來都幹裂了，幾棵菜蔫蔫的長著，看樣子是因為缺水
太多的緣故吧。
LONG);
        set("no_fight", 1);
        set("exits", ([
            	"east" : __DIR__"guofu_houyuan3",
        ]));
        set("objects", ([
           	__DIR__"npc/guanjia6" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_jiao", "jiao");
}

int do_jiao(string arg)
{      
        object me, weapon;
        int costj, costq;

        me = this_player();

        if( query_temp("mark/澆完了", me) )
            	return notify_fail(CYN "菜園管事嚷嚷道：喂喂喂，讓你去覆命，還留"
                                   "在這裡幹嘛？\n" NOR);

        if( query_temp("job_name", me) != "澆菜地" )
            	return notify_fail(CYN "菜園管事對你喝道：沒事你瞎折騰什麼？\n" NOR);

        if (me->is_busy())
		return notify_fail("你現在正忙著呢！\n");

        if (me->is_fighting())
		return notify_fail("你正在戰鬥中，無法專心幹活！\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("id", weapon) != "shui piao" )
                return notify_fail(CYN "菜園管事譏笑道：你想用什麼來舀水澆呀，用"
                                   "手嗎？\n" NOR);

        if (! arg || arg != "shui" )
		return notify_fail("你要澆什麼？\n");

        costj=random(query("con", me)/3)+1;
        costq=random(query("str", me)/3)+1;

        if( query("jing", me)<costj
	 || query("qi", me)<costq )
	{
              	message_vision(HIR "\n$N" HIR "彎腰到大缸裡舀水，結果一失足栽進了缸"
                               "裡。\n" NOR, me);
              set("water", 600, 	me);
              	me->unconcious();
              	return 1;
        }

        me->receive_damage("jing", costj);
        me->receive_damage("qi", costq);
        me->start_busy(1 + random(2));

        if (! (int)me->query_condition("wuguan_job")
            && query_temp("mark/澆", me)>10+(random(10) )
           && present("caiyuan guanshi", environment(me)))
	{
                set_temp("mark/澆完了", 1, me);
                message_vision(CYN "\n菜園管事對$N" CYN "說：幹的不錯，好了，你可"
                               "以去向耶律大爺覆命(" HIY "fuming" NOR + CYN ")了"
                               "。\n" NOR, me);
                return 1;
        }

        message_vision(HIG "$N" HIG "用瓢從缸裡舀起水，在菜地裡澆起水來。\n" NOR, me);
        addn_temp("mark/澆", 1, me);

        if ((int)me->query_skill("whip", 1) < 50
           && (int)me->query_skill("finger", 1) < 50
           && me->can_improve_skill("whip")
           && me->can_improve_skill("finger"))
	{
                write(HIC "你在澆水過程中對鞭法及指法有些體會。\n" NOR);
                me->improve_skill("whip",(query("int", me)/6));
                me->improve_skill("finger",(query("int", me)/6));
        }
        return 1;
}
