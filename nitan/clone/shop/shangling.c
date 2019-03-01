// clone/shop/shang-ling.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + WHT "商令" NOR, ({ "shang ling", "shang", "ling" }));
        set_weight(1);
  if( clonep() )
      set_default_object(__FILE__);
  else 
  {
                set("long", NOR + WHT "這是一張紅底金邊的通商令，由闖王軍頒發。\n" NOR);
                set("unit", "張");
                set("value", 5);
                set("material", "paper");
                set("no_sell", "這年頭，你把吃飯的家伙也拿來賣錢？");
                set("no_drop",1);
        }
        setup();
}

void init()
{
        add_action("do_stock", "stock");
        add_action("do_unstock", "unstock");
}

int do_stock(string arg)
{
        object obj, me, goods;
        int amount, value,i,prize;
        mapping all_goods;
        string beishu, *args;

        me = this_player();

        if( !query("is_vendor", me) )
                return notify_fail("只有從事商業的人才能擺攤。\n");
        if (! present("shang ling", me))
                return notify_fail("你未帶商令！如今世道亂，小心為妙。\n");
        if( !query_temp("on_baitan", me) )
                return notify_fail("你必須先擺個攤位(baitan)才能兜售貨物。\n");
        if (! arg) return notify_fail("指令格式：stock <貨物> <原值倍數>\n");

        i = sizeof(args = explode(arg, " "));

        i--;
        if (! sscanf(args[i], "%d", amount)) amount = 0;
        else arg = replace_string(arg, " " + amount, "");

        if (! (goods = present(arg, me)) || ! objectp(goods))
                return notify_fail("你身上並沒有這個貨物。\n");

        if (goods->is_character()) return notify_fail("你不能販賣活物。\n");
        if( query("money_id", goods) )
                return notify_fail("你打算把錢也拿來出售？\n");
        if( query("id", goods) == "shangling" )
                return notify_fail("把這東西賣了，你靠什麼來吃飯？\n");
//        if (goods->is_item_make())
        if( query("ownmake", goods) )
                return notify_fail("這東西是定了名的，相信沒人願去買。\n");
        if( sizeof(query("vendor_goods", me)) >= 10 && !wizardp(me) )
                return notify_fail("你一次只能擺十種貨物，先收起別的吧。\n");
        if (amount > 100)
        {
                if (!wizardp(this_player()) && amount > 10000000)
                        return notify_fail("物品出售價格不能高過1000兩黃金和原價的一百倍。\n");
                prize = amount;
        }
        if (!prize)
        {
                value=query("base_value", goods);

                if( !value)value=query("value", goods);
                if (amount)
                { 
                        value = amount * value;
                        beishu = chinese_number((string)amount) + "倍價";
                }
                else
                {
                        value = value/2;
                        beishu = "半價";
                }
        }
        else 
        {
                value = prize;
                beishu = MONEY_D->price_str(value);
        }

        if (! value) return notify_fail("這東西不值錢，沒人會去買的。\n");
        all_goods=query("vendor_goods", me);
        if (! all_goods) all_goods = ([ ]);

        all_goods[file_name(goods)] = value;
        set("vendor_goods", all_goods, me);
        message_vision(HIW "$N" HIW "將"+ goods->name(1) + HIW "定為" + beishu + HIW "擺上攤子開始出售。\n" NOR, me);
        return 1;
}

int do_unstock(string arg)
{
        object obj, goods, me = this_player();
        int i, amount, value, have_it = 0;
        mapping all_goods;
        string *goods_key, beishu;

        if( !query("is_vendor", me) )
                return notify_fail("只有從事商業的人才能擺攤。\n");
        if( !query_temp("on_baitan", me) )
                return notify_fail("你目前並沒有擺攤。\n");
        if (! arg) return notify_fail("unstock <貨物>\n");
        if (! (goods = present(arg, me)))
                return notify_fail("你並沒有兜售這個貨物。\n");
        all_goods=query("vendor_goods", me);
        if (! all_goods) return notify_fail("你現在並沒有兜售任何貨物。\n");

        goods_key = keys(all_goods);

        for (i = 0; i < sizeof(goods_key); i++)
        {
                if (file_name(goods) == goods_key[i]) have_it = 1;
        }

        if (have_it) 
        {
                map_delete(all_goods, file_name(goods));
                message_vision(HIW "$N" HIW "將" + goods->name(1) + HIW"從攤子上收起不賣了。\n"NOR, me);
        }
        else return notify_fail("你並沒有兜售這個貨物。\n");

        set("vendor_goods", all_goods, me);
        return 1;
}

int query_autoload()
{
        return 1;
} 