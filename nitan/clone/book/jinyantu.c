// jinyantu.c 金雁圖譜
// By Lgg,1998.9

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

void create()
{
        set_name(HIC"金雁圖譜" NOR, ({ "jinyan tu","tu", }));
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long",
                "這是本很普通的書，書裡面好象有一些小人飛舞的圖形。\n",
                );
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name":       "jinyan-gong",
            			"family_name" : "全真派",
                        "exp_required" : 10000,
                        "jing_cost":  25,
                        "difficulty": 18,
                        "max_skill":  60
                ]) );
        }
}