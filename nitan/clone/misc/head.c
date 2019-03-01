// head.c 腦袋

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;
inherit F_CUTABLE;
inherit F_SILENTDEST;

void eat_effect();
int is_head() { return 1; }

void create()
{
        set_name(NOR + RED "頭顱" NOR, ({ "head" }));
        set_weight(1500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 1);
                set("no_store", 1);
                set("no_sell", "我的天…這…這你也拿來賣…官…官府呢？");
                set("food_supply", 10);
                set("food_remaining", 4);
                set("long", RED "這是一顆鮮血淋淋的首級，鮮血正緩緩滲出。\n" NOR);
        }
}

int set_from(object owner)
{
        apply_effect((: eat_effect :));
        set("owner_id",query("owner_id", owner));
        set("victim_name",query("victim_name", owner));
        set("is_player",query("is_player", owner));
        set("killed_by",query("killed_by", owner));
        set("defeated_by",query("defeated_by", owner));
        set("defeated_by_who",query("defeated_by_who", owner));
        set("assist",query("assist", owner));
        set("gender",query("gender", owner));

        if( !stringp(query("victim_name", owner)) )
        {
                set("name", "腐爛的人頭");
                set("name", "腐爛的無頭屍體", owner);
        } else
        {
                set("name",query("victim_name", owner)+"的人頭");
                set("name", "無頭屍體", owner);
        }

        if( query_temp("clawed_by_jiuyin", owner) )
        {
                set_temp("clawed_by_jiuyin", 1);
                set("long", query("long") +
                            "上面赫然有五個小洞，伸手一探，剛好可以插入。\n");
        }

        set_name(NOR + RED + query("name") + NOR, ({ "head" }));
        return 1;
}

int do_cut(object me, string part)
{
        if (! query("food_remaining"))
                return 0;

        return ::do_cut(me, part);
}

int finish_eat()
{
        set_name(NOR + WHT "骷髏頭" NOR, ({ "bone" }));
        set_weight(150);
        set("long", WHT "這是一個白森森的骷髏頭。\n" NOR);
        return 1;
}

void eat_effect()
{
        object me;

        me = this_player();
        addn("combat/eatman", 1, me);
        if( query("shen", me)>-1000 )
                set("shen", -1000, me);
}
