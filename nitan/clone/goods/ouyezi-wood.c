#include <ansi.h>
inherit ITEM;

int query_autoload() { return 1; }
void create()
{
        set_name(HIM "歐冶子木符" NOR, ({ "ouyezi wood", "symbol" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "歐冶子木符可以將普通自造防具升級(upd)為準開孔狀態，擁有木屬性。\n" NOR);
                set("unit", "張");
                set("value", 500000);
        }
        setup();
}

void init()
{
        add_action("do_integrate", "upd");
}

int do_integrate(string arg)
{
        object me;
        object ob;
        string ownerid;

        if (! arg)
                return notify_fail("你要往什麼道具上使用該聖符？\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("你身上和附近沒有這樣道具啊。\n");

        if( query("magic/imbue_ok", ob) )
                return notify_fail(name() + "已經是準10LVL以上兵器，沒有這個必要吧。\n");

        if (ob->is_weapon() || ob->is_unarmed_weapon())
                return notify_fail("你只能在防具上使用該聖符。\n");
                
        ownerid = ob->item_owner();
        
        set("magic/imbue_ok", 1, ob);
        set("magic/type", "wood", ob);
        ob->save();
  
        tell_object(me, "你把" + name() + "蓋在" + ob->name() + "上，然後口中唸唸有詞，\n"
                        "只見聖符化作一道紅光飛入" + ob->name() + "體內！\n");

        tell_object(me, HIC "你感受" + ob->name() + HIC"發生了不可言喻的變化。\n" NOR);

        destruct(this_object());
        return 1;
}