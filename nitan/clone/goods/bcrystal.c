// Written by Lonely@chinamud.cn
// crystal.c 水晶

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("黑水晶", ({ "black crystal", "crystal" }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIC "一塊黑色的水晶，可以抽取(extract)動態裝備的屬性，用來鑲嵌或強化自造裝備。\n" NOR);
                set("value", 50000);
                set("can_extract", 1);
                set("unit", "塊");
                set("autoload", 1);
        }
        setup();
}

int do_extract(object obj)
{
        object ob;
        mapping prop;
        string *ks, key, type;
        int value;

        ob = this_object();

        if( !obj ) return notify_fail("沒有這個物品。\n");

        if( query("enchase", ob) )
                return notify_fail("黑色水晶已經抽取過一個屬性了。\n");

        if( !query("enchase", obj) || !(prop=query("enchase/apply_prop", obj)) )
                return notify_fail("這個物品上面沒有可用來抽取的屬性。\n");

        if( obj->is_item_make() )
                return notify_fail("黑色水晶只可抽取動態裝備的屬性。\n");

        if( this_player()->query_skill("enchanting", 1) < 200 &&
            !present("enchant scroll", this_player()) )
                return notify_fail("你的附魔技藝不夠，也沒有附魔卷軸，不敢貿然下手。\n");

        if( random(100) < 50 )
                return notify_fail("抽取失敗。\n");

        ks = keys(prop);
        key = ks[random(sizeof(ks))];
        value = prop[key];

        delete("enchase/apply_prop/"+key, obj);
        if( sizeof(query("enchase/apply_prop", obj))<1 )
                delete("enchase/apply_prop", obj);

        if( query("skill_type", obj))type=query("skill_type", obj);
        else type=query("armor_type", obj);

        set("enchase/apply_prop/"+key, value, ob);
        set("enchase/type", type, ob);
        set("enchase/level",query("require/level",  obj), ob);

        set("set_data", 1, ob);
        if( this_player()->can_improve_skill("enchanting") )
                this_player()->improve_skill("enchanting", random(10) + 1);
        return 1;
}

string extra_long()
{
        int i, t;
        string *apply, str, msg, type;
        int value;

        str =  sprintf( YEL "\n物品屬性 : 鑲嵌物<水晶>，重量%d克，下線%s丟失\n" NOR,
                        this_object()->query_weight(),
                        (this_object()->query_autoload() || query("autoload")) ? "不" : "" );

        if( query("bindowner") )
                msg = sprintf( "已經綁定使用者(%s)", query("bindowner") );
        else
                msg = "暫未綁定使用者";

        if( intp(t = query("bindable")) && t > 0 ) {
                if( t == 1 )      msg += "<裝備綁定>";
                else if( t == 2 ) msg += "<拾取幫定>";
                else if( t == 3 ) msg += "<直接綁定>";
        }

        str += sprintf( YEL "綁定狀態 : %s\n\n" NOR, msg);

        if( query("enchase/apply_prop") ) {
                apply = keys(query("enchase/apply_prop"));
                for (i = 0; i<sizeof(apply); i++) {
                        value = query("enchase/apply_prop")[apply[i]];
                        str += HIK "擁有屬性" NOR " : ";
                        str += EQUIPMENT_D->chinese(apply[i], value) + "\n";
                }
                type = query("enchase/type");
                str += sprintf(HIK "可鑲裝備 : %s(%s)\n" NOR, to_chinese(type), type);
                str += sprintf(HIK "可鑲等級 : %d\n" NOR, query("enchase/level"));
        }

        return str;
}

string query_name() { return "黑水"; }