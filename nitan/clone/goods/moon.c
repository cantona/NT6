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
        mapping ins;
        string *apply, *key;
        string type, enc;
        object ob;
        mixed res;
        int i;

        ob = this_object();

        if( !obj ) return notify_fail("沒有這個物品。\n");

        if( query("enchase", ob) )
                return notify_fail("月魄已經附魔過屬性了。\n");

        if( !query("enchase", obj) || !(applied_prop=query("enchase/apply_prop", obj)) )
                return notify_fail("這個物品上面沒有可用來附魔的屬性。\n");

        if( obj->is_item_make() || !(ins=copy(query("insert", obj))) )
                return notify_fail("這個物品無法用來附魔的屬性。\n");

        if( query("skill_type", obj) || query("armor_type", obj) == "hands" || query("armor_type", obj) == "finger" )
                return notify_fail("日魂只能用來附魔防具類物品的屬性。\n");

        if( random(100) < 20 )
                return notify_fail("附魔失敗。\n");

        key = keys(ins);
        enc = key[random(sizeof(key))];
        res = copy(ins[enc]);
        map_delete(ins, enc);

        enchase_prop = res["apply_prop"];
        if( !mapp(enchase_prop) )
                return notify_fail("附魔失敗。\n");

        set("insert", ins, obj);
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
        
        if( type == "rings" || type == "neck" || type == "charm" )
                set("enchase/rings_prop", enchase_prop, ob);
        else
                set("enchase/armor_prop", enchase_prop, ob);
        set("enchase/type", type, ob);
        set("enchase/SN", 1+random(9), ob);
        set("enchase/level",query("require/level",  obj), ob);
        set("enchant", 1, ob);
        set("set_data", 1, ob);


        return 1;
}
