#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "yaowang_poison"; }

string chinese_name() { return HIW "藥王谷獨門毒藥" NOR; }

string update_msg_others()
{
       return HIW "$N臉色發紫，全身不住的顫抖，牙關格格作響。\n" NOR;
}

string update_msg_self()
{
        return HIW "你的藥王谷獨門之毒發作了！\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] / 3;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"]/ 2;
}

int dispel(object me, object ob, mapping cnd)
{

        if (me == ob)
        {
                if ((me->query_skill("shennong-xinjing", 1) > 180 && 
                        me->query_skill_mapped("force") == "shennong-xinjing") ||
                        (me->query_skill("yaogu-xinfa", 1) > 250 &&
                        me->query_skill_mapped("force") == "yaogu-xinfa")||
                        (me->query_skill("yaowang-shenxin", 1) > 180 &&
                        me->query_skill_mapped("poison") == "yaowang-shenxin"))
                {                                           
                        return ::dispel(me, ob, cnd);
                }
                                        
                tell_object(me, "你試圖運功化解藥王谷之毒，突然一感到"
                                "陣撕心裂肺的疼痛，幾乎暈厥。\n");
                return -1;
        }
        else
        {
                if ((me->query_skill("shennong-xinjing", 1) > 180 && 
                        me->query_skill_mapped("force") == "shennong-xinjing") ||
                        (me->query_skill("yaogu-xinfa", 1) > 250 &&
                        me->query_skill_mapped("force") == "yaogu-xinfa")||
                        (me->query_skill("yaowang-shenxin", 1) > 180 &&
                        me->query_skill_mapped("poison") == "yaowang-shenxin"))
                {                                           
               addn_temp("apply/dispel-poison", -50, me);
               set_temp("add_dispel", 1, me);
               call_out("clear_dispel", 2, me);
                return ::dispel(me, ob, cnd);
                }


        tell_object(me, "你將真氣輸入" + ob->name() + "體中，卻覺得"
                        "真氣運轉異常怪異，難以理解，\n突然見" + ob->name() +
                        "汗如雨下，連忙住手。\n");
        tell_object(ob, "你覺得" + me->name() + "將內力緩緩輸入你的"
                        "經脈，忽然一陣撕心裂肺的劇痛，\n猶勝藥王谷獨門之"
                        "毒發作的時候，令你幾乎暈厥。\n");
        return -1;
        }
        
}

void clear_dispel(object me)
{
       if( query_temp("apply/dispel-poison", me) && 
           query_temp("add_dispel", me) )
       {
                delete_temp("add_dispel", me);
                addn_temp("apply/dispel-poison", 50, me);
                return;
       }
               
}