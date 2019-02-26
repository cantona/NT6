// songyang-zhangpu.c 大嵩陽掌譜
// Last Modified by Winder on Jul. 15 2001

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

void create()
{
        set_name(RED"大嵩陽掌譜" NOR, ({ "songyang zhangpu","zhangpu", }));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit","本");
                set("long","這是一張麻紙小冊，上面好像還有一些小人揮舞拳腳的圖形。\n",
         );
         set("value", 0);
         set("material", "paper");
         set("skill", ([
                        "name"         : "songyang-strike",
			"family_name" : "嵩山派",
                        "exp_required" : 10000,
                        "jing_cost"    : 30,
                        "difficulty"   : 20,
                        "max_skill"    : 80
                ]) );
        }
}