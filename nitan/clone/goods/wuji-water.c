// 玄兵聖水用于開孔兵器

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "無極聖水" NOR, ({ "wuji water", "water" }) );
        set_weight(30);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一瓶瑩剔透聖水，散射出絢目的光彩。\n"
                            "他可以用來直接擴展(kuokong)兵器或防具最大孔數。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "瓶");
        }

        setup();
}

void init()
{
        add_action("do_kuokong", "kuokong");
}

int do_kuokong(string arg)
{
        object me;
        object ob;

        if (! arg)
                return notify_fail("你要往什麼道具上使用無極聖水？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你身上和附近沒有這樣道具啊。\n");
        
        if (ob == this_object() || ob->is_character())
                return notify_fail("你想要幹什麼?\n");
        
        if (! ob->is_item_make())
                return notify_fail(ob->name() + "無法用無極聖水來擴展凹槽。\n");
        
        if( !query("enchase/flute", ob) )
                return notify_fail("你還是先去開孔後再考慮擴展凹槽吧。\n");
                
        set("ultimate/37", 1, ob);
        set("ultimate/39", 1, ob);
        
        if( query("skill_type", ob )
        ||  ob->is_unarmed_weapon())
                set("enchase/flute", 9, ob);
        else
                set("enchase/flute", 7, ob);
        
        ob->save();
        tell_object(me, "你把一瓶" + name() + "洒在" + ob->name() + "上，"
                        "只見" + ob->name() + "通體紅光一閃即滅，豁然已經多出幾個凹槽！\n");

        destruct(this_object());
        return 1;
}
