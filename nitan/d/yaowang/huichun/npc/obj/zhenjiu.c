// 針灸盒 藥王莊醫療施毒的道具。

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( CYN "針灸盒" NOR , ({"zhenjiu he", "zhenjiu", "box"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", CYN"這是一個針灸盒，是藥王谷弟子醫療和施毒的工具。\n"
                                "       xiadu   下毒\n"
                                "       heal    療傷\n"
                                "       jiedu   解毒\n"NOR);
                set("unit", "個");
//              set("no_get", 1);
//              set("no_sell", 1);
//              set("no_drop", 1);
//              set("no_give", 1);
                set("value", 0);
                set("weight", 100);
        }
}

void init()
{
        add_action("do_xiadu", "xiadu"); //下毒
        add_action("do_heal", "heal"); //療傷
        add_action("do_jiedu", "jiedu"); //解毒
}

int do_heal(string arg)
{
        object me, ob;
        int i;
        me=this_player();
        i=( 100 - (int)me->query_skill("medical",1) );

        if( query("family/family_name", me) != "藥王谷" )
                return notify_fail("你不能使用這個針灸盒！\n");

        if( query("shen", me)<0 )
                return notify_fail("你不會使用這項技能！\n");

        if( !arg )
                return notify_fail("指令格式：heal <ID> \n");

        if(!objectp(ob = present(arg, environment(me))))
                return notify_fail("這裡沒有這個人！\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙著呢！\n");

        if( ob->is_fighting() || ob->is_busy() )
                return notify_fail("他正忙著呢！\n");

        if( i<5 ) i=5;
        if( i>80 ) i=80;
        if( query("jing", me) <= i )
                return notify_fail("你太累了，先休息一下吧！\n");

        if( query("max_qi", ob) >= (query("eff_qi", ob)+(i*2))){
                set("max_qi", (query("eff_qi", ob)+(i*2)), ob);
        } else { set("eff_qi",(query("max_qi",ob)),ob); } 

        message_vision(CYN"$N從針灸盒中拿出一根銀針在$n穴位上紮了幾下。\n"NOR, me, ob);
        message_vision(WHT"$N吐出一口淤血，臉色看起來好多了。\n"NOR, ob);
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
        addn("jing", -i, me);
        me->start_busy(3);
        return 1;
}

int do_xiadu(string arg)
{
        object me, ob;
        int i;
        me=this_player();
        i=( 100 - (int)me->query_skill("medical",1) );

        if( query("family/family_name", me) != "藥王谷" )
                return notify_fail("你不能使用這個針灸盒！\n");

        if( query("shen", me)>0 )
                return notify_fail("你不會使用著項技能！\n");

        if( (query("no_fight", environment(me))) )
                return notify_fail("這裡禁止戰鬥！\n");

        if( !arg )
                return notify_fail("指令格式：xiadu <ID> \n");

        if(!objectp(ob = present(arg, environment(me))))
                return notify_fail("這裡沒有這個人！\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙著呢！\n");

        if( i<5 ) i=5;
        if( i>80 ) i=80;
        if( query("jing", me) <= i )
                return notify_fail("你太累了，先休息一下吧！\n");

        message_vision(HIR"$N輕輕按了一下針灸盒。突然從盒中射出幾支"
                HIW"銀針"HIR"盡數打在$n身上。\n"NOR, me, ob);
        ob->receive_damage("qi",(int)me->query_skill("medical",1));
        if(random(10)<5)
        {
        ob->apply_condition("ill_dongshang", ((int)me->query_condition("ill_dongshang")+i));
        } 
        else if(random(10)<5) 
        {
        ob->apply_condition("ill_fashao", ((int)me->query_condition("ill_fashao")+(i*10)));
        }
        else if(random(10)<5) 
        {
        ob->apply_condition("ill_kesou", ((int)me->query_condition("ill_kesou")+(i*10)));
        }
        else if(random(10)<5) 
        {
        ob->apply_condition("ill_shanghan", ((int)me->query_condition("ill_shanghan")+(i*10)));
        }
        else
        {
        ob->apply_condition("ill_zhongshu", ((int)me->query_condition("ill_zhongshu")+(i*10)));
        }
        
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
        me->improve_skill("poison", ((int)me->query_skill("poison",1)));
        addn("jing", -i, me);
        me->start_busy(3);
                if(random(me->query_skill("medical",1))<50) {
                        ob->kill_ob(me); }
        return 1;
}

int do_jiedu(string arg)
{
        object me, ob;
        int i;
        me=this_player();
        i=( 100 - (int)me->query_skill("medical",1) );

        if( query("family/family_name", me) != "藥王谷" )
                return notify_fail("你不能使用這個針灸盒！\n");

        if( query("shen", me)>0 )
                return notify_fail("你不會使用著項技能！\n");

        if( !arg )
                return notify_fail("指令格式：jiedu <ID> \n");

        if(!objectp(ob = present(arg, environment(me))))
                return notify_fail("這裡沒有這個人！\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙著呢！\n");

        if( ob->is_fighting() || ob->is_busy() )
                return notify_fail("他正忙著呢！\n");

        if( i<5 ) i=5;
        if( i>80 ) i=80;
        if( query("jing", me) <= i )
                return notify_fail("你太累了，先休息一下吧！\n");

        message_vision(CYN"$N從針灸盒中拿出一根銀針在$n穴位上紮了幾下。\n"NOR, me, ob);

//解 凍傷
        if( (int)ob->query_condition("ill_dongshang")>=1 ) 
        {
                if ((int)ob->query_condition("ill_dongshang") <= 10 ) 
                {
                        ob->apply_condition("ill_dongshang", 0);
        message_vision(YEL"$n身上的"HIB"不良症狀"NOR+YEL"盡退，臉色看上去好多了。\n"NOR, me, ob); 
                } 
                else 
                {
                message_vision(YEL"$n身上的"HIB"不良症狀"NOR+YEL"清去一些，臉色漸漸紅潤起來。\n"NOR, me, ob);
                ob->apply_condition("ill_dongshang", (int)ob->query_condition("ill_dongshang") -10);
                }
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
                addn("jing", -i, me);
                me->start_busy(3);
                return 1;
        }
//解 發燒
        if( (int)ob->query_condition("ill_fashao")>=1 ) 
        {
                if ((int)ob->query_condition("ill_fashao") <= 10 ) 
                {
                        ob->apply_condition("ill_fashao", 0);
        message_vision(YEL"$n身上的"HIB"不良症狀"NOR+YEL"盡退，臉色看上去好多了。\n"NOR, me, ob); 
                } 
                else 
                {
                message_vision(YEL"$n身上的"HIB"不良症狀"NOR+YEL"清去一些，臉色漸漸紅潤起來。\n"NOR, me, ob);
                ob->apply_condition("ill_fashao", (int)ob->query_condition("ill_fashao") -10);
                }
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
                addn("jing", -i, me);
                me->start_busy(3);
                return 1;
        }
//解 咳嗽
        if( (int)ob->query_condition("ill_kesou")>=1 ) 
        {
                if ((int)ob->query_condition("ill_ill_kesou") <= 10 ) 
                {
                        ob->apply_condition("ill_ill_kesou", 0);
        message_vision(YEL"$n身上的"HIB"不良症狀"NOR+YEL"盡退，臉色看上去好多了。\n"NOR, me, ob); 
                } 
                else 
                {
                message_vision(YEL"$n身上的"HIB"不良症狀"NOR+YEL"清去一些，臉色漸漸紅潤起來。\n"NOR, me, ob);
                ob->apply_condition("ill_ill_kesou", (int)ob->query_condition("ill_ill_kesou") -10);
                }
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
                addn("jing", -i, me);
                me->start_busy(3);
                return 1;
        }
//解 傷寒
        if( (int)ob->query_condition("ill_shanghan")>=1 ) 
        {
                if ((int)ob->query_condition("ill_shanghan") <= 10 ) 
                {
                        ob->apply_condition("ill_shanghan", 0);
        message_vision(YEL"$n身上的"HIB"不良症狀"NOR+YEL"盡退，臉色看上去好多了。\n"NOR, me, ob); 
                } 
                else 
                {
                message_vision(YEL"$n身上的"HIB"不良症狀"NOR+YEL"清去一些，臉色漸漸紅潤起來。\n"NOR, me, ob);
                ob->apply_condition("ill_shanghan", (int)ob->query_condition("ill_shanghan") -10);
                }
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
                addn("jing", -i, me);
                me->start_busy(3);
                return 1;
        }
//解 中暑
        if( (int)ob->query_condition("ill_zhongshu")>=1 ) 
        {
                if ((int)ob->query_condition("ill_zhongshu") <= 10 ) 
                {
                        ob->apply_condition("ill_zhongshu", 0);
        message_vision(YEL"$n身上的"HIB"不良症狀"NOR+YEL"盡退，臉色看上去好多了。\n"NOR, me, ob); 
                } 
                else 
                {
                message_vision(YEL"$n身上的"HIB"不良症狀"NOR+YEL"清去一些，臉色漸漸紅潤起來。\n"NOR, me, ob);
                ob->apply_condition("ill_zhongshu", (int)ob->query_condition("ill_zhongshu") -10);
                }
        me->improve_skill("medical", ((int)me->query_skill("medical",1)));
                addn("jing", -i, me);
                me->start_busy(3);
                return 1;
        }

        else {
                message_vision(CYN"可是$n並沒有中毒啊！\n"NOR, me, ob);
                addn("jing", -i, me);
                me->start_busy(3);
                return 1;
        }
}
