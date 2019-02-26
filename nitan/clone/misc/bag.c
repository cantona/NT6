#include <ansi.h>
inherit ITEM;

#define GIFT_DIR        "/clone/gift/"
#define NORM_DIR        "/d/item/obj/"

// 貴重物品列表
string *VA_LIST = ({ "jiuzhuan", "puti-zi", "tianxiang", });

// 普通物品列表  
string *NORMAL_LIST = ({ "xuantie", "wujins", "butian",
                         "tiancs", });

// 特殊物品列表
string *SM_LIST = ({ "unknowdan", "xiandan", "xisuidan", "shenliwan", });

int is_bag(){ return 1; }

void create()
{
        set_name(WHT "包裹" NOR, ({ "bag", "baoguo", "bao", "guo" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", WHT "這是一個灰布包裹，裏面脹鼓鼓的，不知裝"
                            "了些什麼。\n" NOR);
                set("no_sell", 1);
                set("value", 500);
                set("material", "cloth");
        }
        set("gift_count", 1);
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_open", "open");
                add_action("do_open", "unpack");
                add_action("do_open", "dakai");
        }
}

int do_open(string arg)
{
        object me, gift;
        string un;

        if (! arg || ! id(arg))
                return 0;

        if (query("gift_count") < 1)
        {
                write("包裹裏面什麼也沒有了。\n");
                return 1;
        }

        me = this_player();
        message_vision(WHT "\n$N" WHT "拆開包裹，發現裏面留有張"
                       "字條，寫着「" HIR "師門急事，請火速趕回"
                       NOR + WHT "」。\n除此之外字條下好像還壓"
                       "着什麼東西，被裹得很嚴密，$N" WHT "見狀"
                       "連忙取出。\n" NOR, me);

        if (random(5) <= 3)
                gift = new(GIFT_DIR + VA_LIST[random(sizeof(VA_LIST))]);
        else
        if (random(50) == 1)
                gift = new(GIFT_DIR + SM_LIST[random(sizeof(SM_LIST))]);
        else
                gift = new(NORM_DIR + NORMAL_LIST[random(sizeof(NORMAL_LIST))]);

        if( query("base_unit", gift) )
                un=query("base_unit", gift);
        else
                un=query("unit", gift);

        tell_object(me, HIC "你獲得了一" + un + HIC "「" + gift->name() +
                        HIC "」。\n" NOR);

        gift->move(me, 1);
        addn("gift_count", -1);
        set("long", WHT "這是一個灰布包裹，裏面的東西已經被取出來了。\n" NOR);
        set("value", 0);
        return 1;
}

