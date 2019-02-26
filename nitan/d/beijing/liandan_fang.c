#include <ansi.h>
inherit ROOM;

#define DAN_DIR         "/d/beijing/npc/dan/"

int do_liandan(string arg);

void create()
{       set("short", HIY "煉丹房" NOR);
        set("long", @LONG
這是姚春的煉丹房，四周堆放着煉丹的藥材，一個漆黑的煉丹爐
(lu)聳立在中央，房中的藥味經久不散，並且總有一股散不盡的淡青
色煙霧，長時間的丹藥煉製已經讓這個房間充滿了神祕的色彩。
LONG );
        set("no_fight", 1);
        set("item_desc", ([
                "lu" : YEL "一個深黑色的大鐵丹爐，頂部不停地升起絲絲青煙。\n" NOR,
        ]));

        set("exits", ([
                "south" : __DIR__"liandan_yaoshi",
        ]));

	set("coor/x", -2800);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_liandan", "liandan"); 
}

int do_liandan(string arg)
{
        int time;

        object me = this_player();
        time = 5 + random(5);

        if (me->is_busy())
                return notify_fail("等你有空了再説吧。\n");

        if( query_temp("liandan", me)<1 )
                return notify_fail("煉丹之地，切勿滋擾。\n");

        if( query_temp("liandan", me)<2 )
                return notify_fail("原料都沒有，煉什麼啊？\n");

        if( query_temp("liandan", me) == 3 )
                return notify_fail("丹藥煉製中，請勿分心。\n");

        if( query_temp("liandan", me) == 4 )
                return notify_fail("煉製成功，快去覆命吧。\n");

        if( query("jing", me)<80 || 
            query("qi", me)<80 )
                return notify_fail("你現在的精神狀況無法煉製丹藥。\n");

        message_vision(HIY "$N" HIY "將原料藥材一一放進爐中，盤"
                       "腿坐下，閉目靜待。\n" NOR, me); 
        set_temp("liandan", 3, me);
        me->start_call_out((: call_other, __FILE__, "liandan", me :), time);
        me->start_busy(time);
        return 1;
}

// 特殊丹列表
string *SM_LIST = ({ "danS_1", "danS_2", "danS_3", "danS_4", "danS_5",
                     "danM_3", "danM_4", "danM_5", "danM_7", "danM_8",
                     "danM_9", "danB_6", "danC_5", "danD_6", });

// 普通丹列表
string *NORMAL_LIST = ({ "danM_1", "danM_2", "danM_6",
                         "danA_1", "danA_2", "danA_3", "danA_4", "danA_5",
                         "danB_1", "danB_2", "danB_3", "danB_4", "danB_5",
                         "danC_1", "danC_2", "danC_3", "danC_4",
                         "danD_1", "danD_2", "danD_3", "danD_4", "danD_5", });

void liandan(object me)
{
        object ob;
        int skill;

        skill = (int)me->query_skill("liandan-shu", 1);

        if (environment(me) != this_object())
                return;

        me->receive_damage("jing", 50 + random(30));
        me->receive_damage("qi", 50 + random(30));
        if (random(skill) < 60 && random(3) == 1) 
        {
                set_temp("liandan", 1, me);
                message_vision(HIR "正當$N" HIR "昏昏然的時候，一陣刺鼻"
                               "的氣味從爐中衝出，$N" HIR "急忙開爐取藥，"
                               "結果被弄得個灰頭土臉。\n"NOR,me);
        } else
        if (random(skill) > 60 && random(10) == 1)
        {
                message_vision(HIY "爐頂青煙漸漸轉淡，驀然一道金光閃過，$N"
                               HIY "不禁吃了一驚，此時丹藥氣味漸濃，$N"
                               HIY "趕緊把煉製而成的丹丸取出。\n" NOR, me);
                set_temp("liandan", 4, me);
                ob = new(DAN_DIR + SM_LIST[random(sizeof(SM_LIST))]);
                tell_object(me, HIC "你煉成了珍品「" + NOR + ob->name() + NOR + HIC "」。\n" NOR);
                ob->move(me, 1);
                
/*
                if( stringp(query("family/family_name", me)) )
                {                        
                        addn("family/gongji", 10+random(12), me);
                        tell_object(me, HIC "由於你成功的煉出珍品丹藥，你在師門的功績提高了！\n" NOR);
                }
*/
                
                if (me->can_improve_skill("liandan-shu") && skill < 300)
                {
                        me->improve_skill("liandan-shu",query("int", me)+10);
                        tell_object(me, HIC "在煉丹過程中你的「煉丹術」提高了！\n" NOR);
                }
        } else
        {
                message_vision(HIC "爐頂青煙漸漸轉淡，丹藥氣味漸濃，$N"
                               HIC "高興地把煉製而成的丹丸取出。\n" NOR, me);
                set_temp("liandan", 4, me);
                ob = new(DAN_DIR + NORMAL_LIST[random(sizeof(NORMAL_LIST))]);
                tell_object(me, HIC "你煉成了「" + NOR + ob->name() + NOR + HIC "」。\n" NOR);
                ob->move(me, 1);

/*
                if( stringp(query("family/family_name", me)) )
                {                        
                        addn("family/gongji", 5+random(6), me);
                        tell_object(me, HIC "由於你成功的煉出丹藥，你在師門的功績提高了！\n" NOR);
                }
*/
                
                if (me->can_improve_skill("liandan-shu") && skill < 300)
                {
                        me->improve_skill("liandan-shu",query("int", me)/4+1);
                        tell_object(me, HIC "在煉丹過程中你的「煉丹術」提高了！\n" NOR);
                }
        }
}
