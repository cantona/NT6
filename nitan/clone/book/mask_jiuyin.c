// /clone/book/mask_jiuyin.c 九陰假經

#include <ansi.h>

inherit ITEM;
inherit F_UNIQUE;

int do_du(string arg);

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}

void create()
{
        set_name(YEL"九陰假經"NOR, ({ "mask_jiuyin", "jiuyin-jiajing" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_drop", "你好不容易拿到手的寶經，你捨得丟麼？\n");
                set("no_put", "這麼寶貴的東西，不要到處亂放。\n");
                set("long", "這就是武林中人人夢寐以求的“九陰真經”啊，千萬不要丟了哦。:P \n");
        }
}

int do_du(string arg)
{
        if (!arg && arg != "mask_jiuyin" && arg != "jiuyin-jiajing")
                return notify_fail("你要讀什麼？\n");
        if (!present(this_object(), this_player())) return 0;

        return notify_fail("沒有人解釋經義，你自己能看得懂麼？\n");
}
