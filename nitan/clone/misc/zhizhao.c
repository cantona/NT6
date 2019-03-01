// vendor_pass.c 商業執照

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("商業執照", ({ "shangye zhizhao", "zhizhao" }) );
        set_weight(1);
        if( clonep() )
        set("long", "一張紅底金邊帖子，上面寫著四個金燦燦的大字：商業執照，左下角是黃真的親筆簽名。\n");
        set("unit", "份");
        set("value", 0);
        set("material", "paper");
        set("no_get",1);
        set("no_give",1);
        set("no_sell",1);
        setup();
}

void init()
{
       add_action("do_bantan", "baitan");
       add_action("do_shoutan","shoutan");
       add_action("do_stock","stock");
       add_action("do_unstock","unstock");
}

int do_bantan()
{
        object obj,me;
        obj = this_object();
        me = this_player();

        if( !query("is_vendor", me))return notify_fail("你又不是商人，瞎折騰什麼啊！\n");
        if (!present("shangye zhizhao",me)) return notify_fail("你的商業執照不在身上，難道想無証搬攤？\n");
        if( query_temp("on_bantan", me))return notify_fail("你已經佔了一個攤位，還想怎的？\n");

        message_vision(HIW "$N找了一塊空地，一屁股坐了下來，隨後掏出一塊布攤開在地。\n" +NOR,me);
        tell_object(me,HIW "現在你可以擺上(stock)貨物了，你也可以收起(unstock)某種貨物。\n");
        set_temp("on_bantan", 1, me);
        delete("vendor_goods", me);
        return 1;
}

int do_shoutan()
{
        object obj,me;
        obj = this_object();
        me = this_player();

        if( !query("is_vendor", me))return notify_fail("你又不是商人，瞎折騰什麼啊！\n");
        if (!present("shangye zhizhao",me)) return notify_fail("你的商業執照不在身上，請退線後重新連線並申請一個新的。\n");
        if( !query_temp("on_bantan", me))return notify_fail("你並沒有擺攤，哪裡來的攤子給你收啊？\n");

        message_vision(HIW "$N提起攤布的四個角，把貨物一股腦的收了起來，站起身來。\n" +NOR,me);
        delete_temp("on_bantan", me);
        delete("vendor_goods", me);
        return 1;
}

int do_stock(string arg)
{
        object obj,me,goods;
        int amount,value,i;
        mapping all_goods;
        string beishu,*args;
        
        me = this_player();
        if( !query("is_vendor", me))return notify_fail("你又不是商人，瞎折騰什麼啊！\n");
        if (!present("shangye zhizhao",me)) return notify_fail("你的商業執照不在身上，請退線後重新連線並申請一個新的。\n");
        if( !query_temp("on_bantan", me))return notify_fail("你必須首先擺一個攤位(baitan)才能放貨物！\n");
        if (!arg) return notify_fail("stock <貨物> n (其中n可以是1、2、3、4、5，表示該貨物原價值的n倍，缺省的話表示半價)\n");

        i = sizeof(args = explode(arg, " "));

        i--;
        if (!sscanf(args[i], "%d", amount)) 
                amount = 0;
        else arg = replace_string(arg," "+amount,"");

        if (!(goods = present(arg,me)) || !objectp(goods)) return notify_fail("你身上並沒有這個貨物啊！\n");
        if (goods->is_character()) return notify_fail("你不能販賣人口！\n");
        if( query("money_id", goods))return notify_fail("你瘋了？錢也拿來出售？\n");

        if( sizeof(query("vendor_goods", me)) >= 18)return notify_fail("你一次只能擺上十八種貨物，請首先收起幾種貨物再擺上這種貨物。\n");
        if (amount>5) return notify_fail("你最多以原價五倍出售，不要太心黑啦！\n");

        value=query("base_value", goods);
        if( !value)value=query("value", goods);
        if (amount)
        { 
                value = amount * value;
                beishu = (string)amount + "倍價";
        }
        else
        {
                value = value/2;
                beishu = "半價";
        }
        if (!value) return notify_fail("這種不值錢的爛貨你也想擺上？太沒有商業道德啦！\n");

        all_goods=query("vendor_goods", me);
        if (!all_goods) all_goods = ([ ]);
        all_goods[base_name(goods)] = value;
        set("vendor_goods", all_goods, me);
        message_vision(HIW "$N將"+ NOR + goods->name(1) + HIW +"標上" + HIY + beishu + HIW"擺上攤子開始出售。\n"NOR,me);
        return 1;
}

int do_unstock(string arg)
{
        object obj,me,goods;
        int i,amount,value,have_it = 0;
        mapping all_goods;
        string *goods_key,beishu;
        
        me = this_player();
        if( !query("is_vendor", me))return notify_fail("你又不是商人，瞎折騰什麼啊！\n");
        if (!present("shangye zhizhao",me)) return notify_fail("你的商業執照不在身上，請退線後重新連線並申請一個新的。\n");
        if( !query_temp("on_bantan", me))return notify_fail("你連攤子都沒有搬，還想收起貨物？\n");
        if (!arg) return notify_fail("unstock <貨物>\n");

        if (!(goods = present(arg,me))) return notify_fail("你現在並沒有這個貨物！\n");
        all_goods=query("vendor_goods", me);
        if (!all_goods) return notify_fail("你現在還沒有擺上任何貨物！\n");

        goods_key = keys(all_goods);
        for (i = 0;i < sizeof(goods_key);i++)
        {
                if (base_name(goods) == goods_key[i]) have_it = 1;
        }

        if (have_it) 
        {
                map_delete(all_goods,base_name(goods));
                message_vision(HIW "$N將" + NOR + goods->name(1) + HIW + "從攤子上收起不賣了。\n",me);
        } else return notify_fail("你沒有把這樣貨物擺上攤子出售啊。\n");

        set("vendor_goods", all_goods, me);
        return 1;
}

int query_autoload() { return 1; } 