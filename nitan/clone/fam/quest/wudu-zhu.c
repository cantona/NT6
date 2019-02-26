#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "五毒珠" NOR, ({ "wudu zhu", "wudu", "zhu" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "此乃五毒教練功之神品，乃是從數百種天下奇毒中提煉而成，服用\n"
                                "後可大大增加自身體內毒性。但若無五毒教心法配合，一旦服用立\n"
                                "即暴斃。（服用限制參見 help scborn_sk，此珠下線不丟失)。\n" NOR);
                set("value", 500000);
                set("unit", "顆");             
                set("only_do_effect", 1);
                set("do_effect", 1);
        }
}

int do_effect(object me)
{
        if (environment(this_object()) != me)
                return notify_fail("你身上沒有這樣東西。\n");
                
        if (query("do_effect") < 1)
                return notify_fail("五毒珠已經被服用過了。\n");

        if (me->query("max_neili") < 10000)
                return notify_fail("你內力修為不足，恐怕服用後難以吸收毒性。\n");

        if (me->query("neili") < 10000)
                return notify_fail("你內力不足，服用後恐怕難以運功抵禦劇毒。\n");

        if (me->query("can_perform/qianzhu-wandushou/suck_time") >= 5)
                return notify_fail("你已經吸收了足夠的毒素，不需要再重複吸取了。\n");
        
        if (time() - me->query("last_eating_wudu_zhu") < 3600)
                return notify_fail("你剛吸收過毒素，不宜再吸收！\n");

        message_vision(HIM "$N" HIM "服下一顆五毒珠，毒珠入口即化，片刻，$N" HIM "面色凝重，似乎劇毒正在\n"
                       "周身遊走 ……\n" NOR, me);
                       
        if (me->query_skill("wudu-qishu", 1) < 300 || me->query_skill("wudu-jing", 1) < 200 ||
            me->query_skill("qianzhu-wandushou", 1) < 800 || me->query("family/family_name") != "五毒教" )
        {
                if (! me->query("special_skill/zhuha"))
                {
                        message_vision(HIR "\n$N" HIR "突然痛苦無比，倒地暴斃，模樣十分恐怖！\n" NOR, me);
                        me->set_temp("die_reason", "服用五毒珠後暴斃");
                        me->die();                        
                        destruct(this_object());
                        return 1;
                }
                else
                {
                        tell_object(me, HIW "由於你有朱蛤奇毒附身，五毒珠劇毒已被全部化解。\n" NOR);
                        destruct(this_object());
                        return 1;                        
                }
        }
        
        set("do_effect", 0);

        me->set("last_eating_wudu_zhu", time());
        remove_call_out("start_xishou");
        call_out("start_xishou", 5, me, 0);
        
        //destruct(this_object());
        return 1;
}

void start_xishou(object me, int i)
{
        string* msg = ({
                "你開始運功抵禦五毒珠的劇毒，真氣已由丹田升起，並迅速在全身遊走 ……\n",
                "你感覺五毒珠劇毒兇猛無比，普通真氣竟難以與之抗衡，情急之下忙運起五毒教密門心法 ……\n",
                "漸漸地，五毒珠劇毒開始有規律地運動，並隨着五毒教心法的牽引而遊走 ……\n",
                "你開始施展千蛛萬毒手心法，吸收五毒珠中的毒素 ……\n",
                "一柱香後，毒素開始向你的十指移動，並開始與你體內的真氣融合 ……\n",        
        });
        
        int ran;
        
        if (! objectp(me))
        {
                destruct(this_object());
                return;
        }
        
        if (environment(this_object()) != me)
        {
                tell_object(me, HIG "五毒珠已丟失，吸取失敗！\n" NOR);
                destruct(this_object());
                return;
        }
        
        if (i >= sizeof(msg))
        {
                // zhuha玩家60%機率吸收成功，其他玩家30%吸收成功
                if (me->query("special_skill/zhuha"))
                {
                        ran = 6;        
                }
                else
                {
                        ran = 3;
                }
                
                if (random(10) >= ran) // 吸收失敗
                {
                        tell_object(me, HIG "突然間，你感覺五毒珠中的劇毒消失得無影無蹤，竟未被你體內真氣吸收，實在遺憾。\n" NOR);
                        destruct(this_object());
                        return;
                }
                
                tell_object(me, HIG "頃刻間，你只覺得所有毒素已被你真氣吸收，融合在一起，聚集在體內，為你所用！\n" NOR);
                tell_object(me, HIG "你將真氣運回丹田，感覺舒泰無比！\n" NOR);
                tell_object(me, HIR "恭喜你，成功吸收了五毒珠中的劇毒！\n" NOR);
                me->add("can_perform/qianzhu-wandushou/suck_time", 1);
                if (me->query("can_perform/qianzhu-wandushou/suck_time") >= 5)
                {
                        tell_object(me, HIM "恭喜你，已經練成了舉世無雙的絕學—萬毒穿心手！\n" NOR);
                        me->set("can_perform/qianzhu-wandushou/chuan", 1);
                        me->save();
                }
                destruct(this_object());
                return;        
        }

        tell_object(me, HIW + msg[i] + NOR);
        
        remove_call_out("start_xishou");
        call_out("start_xishou", 5, me, i + 1);
        
}

int query_autoload()
{
                return 1;
}