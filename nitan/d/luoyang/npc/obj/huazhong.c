#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(YEL "花種" NOR, ({"hua zhong", "hua", "zhong"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一枚無法確定品種的花種。\n");
                set("unit", "只");
                set("value", 1);
                set("food_remaining", 1);
                set("food_supply", 10);
        }
}

void init()
{
        add_action("do_zhonghua", "zhonghua");
}

int do_zhonghua()
{
        object me, ob, where;
 
        me = this_player();
        ob = this_object();
        where = environment(me);

        if( query("short", where) != "苗園" )
                return notify_fail("這裡似乎不適合種花吧？\n");

        if( query("combat_exp", me)<8000 )
        {
                tell_object(me, "你的經驗尚淺，還是先到處多走動走動吧。\n");
                return 1;
        }

        if( query("combat_exp", me)>30000 )
        {
                tell_object(me, "以你的身份大概不適合種花了吧。\n");
                return 1;
        }

        if( query_temp("zhonghua", me) == 1 )
        {
                tell_object(me, "種子已經撥下了，現在該培育"
                                HIY "(peiyu)" NOR "花種了。"
                                "\n");
                return 1;
        }

        message_vision(HIC "$N" HIC "用手在地上挖了一個小"
                       "坑，把花種放了進去。\n" NOR, me);
        tell_object(me, "種子已經撥下了，現在該培育" HIY
                        "(peiyu)" NOR "花種了。\n");
        addn_temp("zhonghua", 1, me);
        destruct(ob);
        addn("jing", -50, me);
        return 1;
}