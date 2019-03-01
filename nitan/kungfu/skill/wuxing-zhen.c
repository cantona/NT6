// zhenwu-qijiezhen.c

#include <ansi.h>

inherit SKILL;

string *action_msg = 
({
        HIR"\n$n見$N等人此去彼來，你擋我擊，就如數十人般源源而上，不由得大吃一驚，\n"
            +"當下抱元守一，見招拆招，不敢再行進攻。\n\n"NOR,
        HIG"\n只見數條人影往來飛舞，有時$n突出包圍，但$N等人如影隨形，立即裹上。\n\n"NOR,
        HIY"\n$n見敵手越打越急，如穿花蝴蝶般亂轉，有時一人作勢欲踢，豈知突然往旁讓\n"
            +"開，他身後一人猛然發拳打到。\n\n"NOR,
        HIB"\n$n見前面一人雙手合抱，意欲肉搏，他往後面退避，後心有腳剛好踢到，湊得\n"
            "再合拍也沒有。\n\n"NOR,
        HIM"\n$N一打手勢，一人向右跨步，一人向左轉身，陣勢布開，頃刻間已將$n圍在垓心。\n\n"NOR,
        HIC"\n$n一入敵圍，不論如何硬闖巧閃，敵人必能以厲害招術反擊，一人出手，其他四人\n"
            + "立即綿綿而上，不到敵人或死或擒，永無休止。\n\n"NOR,
        HIW"\n$n纏鬥良久，不論強攻巧誘，始終脫不出包圍，但對方穿梭來去，攻勢凌厲，\n"
            "只得奮力抵御，毫無絲毫余暇去推敲陣法，\n\n"NOR,
});


string query_action()
{
        return action_msg[random(sizeof(action_msg))];
}

int query_limit()
{
        return 5;
}

void create()
{ 
        seteuid(getuid()); 
}

string type() 
{ 
        return "array"; 
}

int valid_learn(object me) 
{
        if( me->query_skill("force",1) < 160)
                return notify_fail("你的基本內功級別不夠，無法學習五行陣。\n");
        if( me->query("combat_exp") < 800000)
                return notify_fail("你的經驗，恐怕無法領悟五行陣的精髓。\n");
        return 1;
}

int practice_skill(object me)
{       
        return notify_fail("你無法通過練習來提高五行陣的修為。\n");
}

