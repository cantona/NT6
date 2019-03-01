// skysword.c 倚天劍 
// Last Modified by winder on Sep. 7 2001

#include <ansi.h>;
#include <weapon.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(CYN"倚天劍"NOR,({"sky sword", "sword", "jian"}));
        set_weight(30000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "此劍由郭靖黃蓉夫婦打造，是天下神兵。\n");
                set("material", "steel");
                set("no_drop", "如此寶貴的武器再世難求啊。\n");
                set("no_get", "送人？虧你想的出來！\n");
                set("no_put", "珍惜它吧。\n");
                set("value",100);
                set("wield_msg", CYN "倚天劍如靈蛇般躍出劍鞘，落在$N手中，放射出
璀璨的毫光，天地為之變色。\n" NOR);
                set("unwield_msg", CYN "$N手中劍光漸漸暗淡，天幕漸漸煥出光芒。\n" NOR);
       }
       init_sword(300);
       setup();
}

void owner_is_killed()
{
       destruct(this_object());
}