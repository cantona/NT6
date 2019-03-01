inherit SKILL;

mixed hit_ob(object me, object victim, int damage_bonus)
{
   if (random(me->query_skill("cuff"))>150) { 
        victim->apply_condition("cuff_power", 1 +me->query_condition("cuff_power")+query("jiali",me));
    }
}

//be_hit_ob(object me, object victim, int damage_bonus) 
//當被打中時調用受害者的parry上功夫的被打中效果,
//damage_bonus 是內力造成的總的傷害值,如果沒有兵
//器就差不多是最後傷害值
 
