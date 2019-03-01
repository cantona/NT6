// 上古十大神器之 伏羲琴
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + MAG "伏羲琴" NOR, ({ "fuxi qin", "fuxi", "qin" }) );
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "把");
                set("long", NOR + MAG "這是一把看似普通的古琴，傳說乃上古伏羲氏\n"
                                      "所用。\n"
                                      "彈奏(tan)後可恢復所有精、氣、內力和異常狀態。\n" 
                                      "需要彈琴技法一百級，tan ? 查看使用次數。\n" NOR);

        }
        setup();
}

void init()
{
        add_action("do_tan", "tan"); 
}

int do_tan(string arg)
{
        object me;
        mapping my;
        
        me = this_player();
        
        if(! objectp(present("fuxi qin", me)))return 0;

        if (arg == "?")
        {
                 write(HIG "使用次數 " + this_object()->query("count") + "/3\n" NOR);
                 return 1;
        }
                
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");

        message_sort(NOR + MAG + "\n$N" NOR + MAG "盤膝而坐，輕輕地撥弄著伏羲琴，"
                                 "伴隨著令人心醉的琴聲，$N" NOR + MAG "只覺得周身"
                                 "舒泰之極。\n" NOR, me);

        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"];
        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
        my["qi"]     = my["eff_qi"]     = my["max_qi"];
        my["neili"]  = my["max_neili"];
        my["food"]   = me->max_food_capacity();
        my["water"]  = me->max_water_capacity();
        me->clear_condition();
        me->save();
        
        me->start_busy(2);
        this_object()->add("count", 1);
        if (this_object()->query("count") >= 3)
        {
                write(HIW "只聽得一陣脆響，伏羲琴已損壞了。\n" NOR);
                destruct(this_object());        
        }

        return 1;
}
