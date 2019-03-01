// zhangfapu.c 昊天掌法譜
// By Lgg,1998.9

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

void create()
{
        set_name(HIY"昊天掌法譜" NOR, ({ "zhangfa pu","pu", }));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本很破舊的書，書裡面好象還有一些小人揮舞拳腳的圖形。\n");
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name":       "haotian-zhang",
                        "exp_required" : 10000,
                        "jing_cost":  30,
                        "difficulty": 20,
                        "max_skill":  80
                ]) );
        }
}