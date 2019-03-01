// This program is a part of NT MudLIB
// moon.c 月魄

#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(WHT "月魄" NOR, ({ "moon soul", "moon" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", WHT "太陰真火凝聚而成，月白色，能攝心定神，百邪不侵。。\n" NOR);
                set("value", 50000);
                set("unit", "塊");
                set("can_enchant", "armor");
                set("auto_load", 1);
        }
        setup();
}

int do_extract(object obj)
{
        mapping enchase_prop;
        mapping applied_prop;
        mapping *ins;
        string *apply;
        string type;
        object ob;
        mixed res;
        int i;

        ob = this_object();

        if( !obj ) return notify_fail("沒有這個物品。\n");

        if( query("enchase", ob) )
                return notify_fail("月魄已經附魔過屬性了。\n");

        if( !query("enchase", obj) || !(applied_prop=query("enchase/apply_prop", obj)) )
                return notify_fail("這個物品上面沒有可用來附魔的屬性。\n");

        if( obj->is_item_make() || !(ins=query("enchase/inset", obj)) )
                return notify_fail("這個物品無法用來附魔的屬性。\n");

        if( query("skill_type", obj) || query("armor_type", obj) != "hands" || query("armor_type", obj) != "finger" )
                return notify_fail("日魂只能用來附魔防具類物品的屬性。\n");

        if( random(100) < 20 )
                return notify_fail("附魔失敗。\n");

        res = ins[random(sizeof(ins))];
        ins -= ({ res });

        enchase_prop = res["enchase_prop"];
        if( !mapp(enchase_prop) )
                return notify_fail("附魔失敗。\n");

        set("enchase/inset", ins, obj);
        apply = keys(enchase_prop);
        for( i=0; i<sizeof(apply); i++ )
        {
                if( undefinedp(applied_prop[apply[i]]) )
                        continue;
                else
                {
                        applied_prop[apply[i]] -= enchase_prop[apply[i]];
                        if( applied_prop[apply[i]] < 1 )
                                map_delete(applied_prop, apply[i]);
                }
        }

        if( !sizeof(applied_prop) )
                delete("enchase/apply_prop", obj);
        else
                set("enchase/apply_prop", applied_prop, obj);

        type=query("armor_type", obj);

        set("enchase/apply_prop", enchase_prop, ob);
        set("enchase/type", type, ob);
        set("enchase/SN", 1+random(9), ob);
        set("enchase/level",query("require/level",  obj), ob);
        set("enchant", 1, ob);
        set("set_data", 1, ob);


        return 1;
}
