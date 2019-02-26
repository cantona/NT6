#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
    return 1;
}

void skill_improved(object me) 
{ 
        int lvl;
                
        lvl = me->query_skill("array-cognize", 1); 
        
        if (lvl > 100  
         && !query("array/yulin", me) )
        { 
                set("array/yulin", 1, me);
                tell_object(me, HIC "你從通曉了「" HIW "陣法" HIC "」中「" HIW "魚鱗陣" HIC "」的奧祕。\n" NOR); 
        }
                
        if (lvl > 140  
         && !query("array/fengshi", me) )
        { 
                set("array/fengshi", 1, me);
                tell_object(me, HIC "你從通曉了「" HIW "陣法" HIC "」中「" HIW "鋒矢陣" HIC "」的奧祕。\n" NOR); 
        }  

        if (lvl > 180  
         && !query("array/heyi", me) )
        { 
                set("array/heyi", 1, me);
                tell_object(me, HIC "你從通曉了「" HIW "陣法" HIC "」中「" HIW "鶴翼陣" HIC "」的奧祕。\n" NOR); 
        }  

        if (lvl > 220  
         && !query("array/yanyue", me) )
        { 
                set("array/yanyue", 1, me);
                tell_object(me, HIC "你從通曉了「" HIW "陣法" HIC "」中「" HIW "偃月陣" HIC "」的奧祕。\n" NOR); 
        }                      

        if (lvl > 260  
         && !query("array/fangyuan", me) )
        { 
                set("array/fangyuan", 1, me);
                tell_object(me, HIC "你從通曉了「" HIW "陣法" HIC "」中「" HIW "方圓陣" HIC "」的奧祕。\n" NOR); 
        }

        if (lvl > 300  
         && !query("array/yanxing", me) )
        { 
                set("array/yanxing", 1, me);
                tell_object(me, HIC "你從通曉了「" HIW "陣法" HIC "」中「" HIW "雁行陣" HIC "」的奧祕。\n" NOR); 
        }

        if (lvl > 340  
         && !query("array/changshe", me) )
        { 
                set("array/changshe", 1, me);
                tell_object(me, HIC "你從通曉了「" HIW "陣法" HIC "」中「" HIW "長蛇陣" HIC "」的奧祕。\n" NOR); 
        }
        
        if (lvl > 380  
         && !query("array/yunlong", me) )
        { 
                set("array/yunlong", 1, me);
                tell_object(me, HIC "你從通曉了「" HIW "陣法" HIC "」中「" HIW "雲龍陣" HIC "」的奧祕。\n" NOR); 
        }
} 