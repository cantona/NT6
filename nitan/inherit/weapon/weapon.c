// weapon.c
// Last Modified by winder on Feb. 28 2001
// "damage" = sharpness
// "rigidity" according to damage but need consider of weapon type

#include <weapon.h>;
#include <ansi.h>;

#ifdef AS_FEATURE
#include <dbase.h>;
#else
inherit EQUIP;
#endif

// axe.c

varargs void init_axe(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", (int)flag | EDGED | SECONDARY);
//        set("flag", 2);
        set("skill_type", "axe");
        set("rigidity", (int)(damage/2));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "chop", "slash", "slice", "hack" }) );
        }
}

// blade.c

varargs void init_blade(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", (int)flag | EDGED | SECONDARY);
//        set("flag", 2);
        set("skill_type", "blade");
        set("rigidity", (int)(damage/3));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "slash", "slice", "hack" }) );
        }
}

// club.c

varargs void init_club(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", (int)flag | LONG | SECONDARY);
//        set("flag", 1);
        set("skill_type", "club");
        set("rigidity", (int)(damage/5));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "bash", "crush", "slam" }) );
        }
}

// dagger.c

varargs void init_dagger(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", flag | EDGED | SECONDARY );
//        set("flag", 0);
        set("skill_type", "dagger");
        set("rigidity", (int)(damage/4));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "slice", "pierce", "thrust" }) );
        }
}

// fork.c

varargs void init_fork(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", (int)flag | POINTED | SECONDARY);
//        set("flag", 1);
        set("skill_type", "fork");
        set("rigidity", (int)(damage/3));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "impale", "pierce", "thrust" }) );
        }
}

// hammer.c

varargs void init_hammer(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", flag | SECONDARY);
//        set("flag", 2);
        set("skill_type", "hammer");
        set("rigidity", (int)(damage/2));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "bash", "crush", "slam" }) );
        }
}

// hook.c

varargs void init_hook(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", (int)flag | EDGED | SECONDARY);
        set("skill_type", "hook");
        set("rigidity", (int)(damage/4));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "chop", "hack"}) );
        }
}

// spear.c

varargs void init_spear(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", (int)flag | LONG | SECONDARY);
//        set("flag", 1);
        set("skill_type", "spear");
        set("rigidity", (int)(damage/4));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "bash", "thrust", "pierce", "impale", "crush" }) );
        }
}

// staff.c

varargs void init_staff(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", (int)flag | LONG | SECONDARY);
//        set("flag", 1);
        set("skill_type", "staff");
        set("rigidity", (int)(damage/3));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "bash", "crush", "slam" }) );
        }
}

// stick.c

varargs void init_stick(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", (int)flag | LONG | SECONDARY);
//        set("flag", 1);
        set("skill_type", "stick");
        set("rigidity", (int)(damage/4));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "bash", "crush", "slam" }) );
        }
}

// sword.c

varargs void init_sword(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", (int)flag | EDGED | SECONDARY);
//        set("flag", 2);
        set("skill_type", "sword");
        set("rigidity", (int)(damage/4));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "slash", "slice", "thrust" }) );
        }
}

// throwing.c

varargs void init_throwing(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", (int)flag | SECONDARY);
//        set("flag", 8);
        set("skill_type", "throwing");
        set("rigidity", (int)(damage/6));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "throw" }) );
        }
}

// whip.c

varargs void init_whip(int damage, int flag)
{
        set("weapon_prop/damage", damage);
        set("flag", flag );
//        set("flag", 2);
        set("skill_type", "whip");
        set("rigidity", (int)(damage/3));
        if( !query("actions") ) {
                set("actions", (: call_other, WEAPON_D, "query_action" :) );
                set("verbs", ({ "whip" }) );
        }
}

int set_desc(int w_lv,string w_or,string w_name)
{
        object weapon,me;
        string w_liang,player_name,make_time;
        string result1,result2,result3,result4,result;

        weapon = this_object();
        me = this_player();
        w_liang = weapon->query("unit");
        player_name=me->query("name");
        make_time=me->query("weapon/time");

        result1="這是一"+w_liang+"用"+w_or+"打造而成的"+w_name+"。\n";
        switch(w_or)
        {
                case "千年神木":
                        result2=RED"看起來黑中透紅，似乎十分堅硬。\n"NOR;
                        break;
                case "海底金母":
                        result2=HIM"看起來紫澄澄的，似乎十分沉重。\n"NOR;
                        break;
                case "寒絲羽竹":
                        result2=HIG"看起來晶瑩碧綠，透著絲絲的寒意。\n"NOR;
                        break;
                case "隕星鐵石":
                        result2=BLK"看起來焦黑一片，看來是堅硬之極。\n"NOR;
                        break;
                default:
                        break;
        }
        switch(w_lv)
        {
                case 1:
                case 2:
                case 3:
                        result3= "但似乎威力還沒有開發出來，是習武之人常用的練武兵器。兵刃晃動，恍若"HIC"清波澹澹。\n"NOR;
                        break;
                case 4:
                case 5:
                case 6:
                        result3= "但似乎威力並不很大，象是江湖人常用的護身兵刃。兵刃晃動，恍若"HIC"秋水無痕。\n"NOR;
                        break;
                case 7:
                case 8:
                case 9:
                        result3= "隱隱的散發著一絲令人不安的氣息。兵刃晃動，恍若"HIC"朔風出塞。\n"NOR;
                        break;
                case 10:
                case 11:
                case 12:
                        result3= "散發著一絲令人不安的氣息, 顯然普通兵器已不能和他相比了。兵刃晃動，恍若"HIC"白羽飄零。\n"NOR;
                        break;
                case 13:
                case 14:
                case 15:
                        result3= "向外散發著一絲迷蒙的霧氣，竟有一種霸氣散發了出來。兵刃晃動，恍若"HIC"霜冷長河。\n"NOR;
                        break;
                case 16:
                case 17:
                case 18:
                        result3= "一股霸氣直沖霄漢，直叫神驚鬼泣。兵刃晃動，恍若"HIC"雪落無聲。\n"NOR;
                        break;
                case 19:
                case 20:
                case 21:
                        result3= "霸氣似乎有所收斂，但更多的是有了一股駭人的戾氣。兵刃晃動，恍若"HIC"寒潭驚雁。\n"NOR;
                        break;
                case 22:
                case 23:
                case 24:
                        result3= "沖天的戾氣叫人看了不由心驚膽戰，不願再看第二眼。兵刃晃動，恍若"HIC"九天龍吟。\n"NOR;
                        break;
                case 25:
                case 26:
                case 27:
                        result3= "戾氣似乎削減了不少，一股溫和的王者之氣透了出來。兵刃晃動，恍若"HIC"青虹貫日。\n"NOR;
                        break;
                case 28:
                case 29:
                case 30:
                        result3= "一股溫和的王者之氣悠悠的散發了出來。兵刃晃動，恍若"HIC"冷月斷魂。\n"NOR;
                        break;
                default:
                        result3= "一種莊嚴，溫和，凜然而不可侵犯的氣息讓人不敢有一絲褻瀆之意, 它已經返樸歸真，成為真正的上古神兵。兵刃晃動，直欲"HIC"氣沖鬥牛。\n"NOR;
        }

        result4="上面用小篆刻著一行小字：\n\t"+player_name+"鑄于"+make_time+"\n";
        result=result1+result2+result3+result4;
        weapon->set("long",result);

}
