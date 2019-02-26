#include <ansi.h>
inherit ITEM;

string shop_id(){return "fs_shop";}
string shop_name(){return HIW "英雄樓" NOR;}
string shop_string(){return "yingxionglou fangqi";}

void create()
{
        set_name(HIW "「" + shop_name() + HIW "房契」" NOR, ({ shop_string() }));        

        set_weight(1);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "份");
                set("long", HIY "這是一份" + shop_name() + HIY "的房契，請妥善保管。\n"
                            HIM        "使用 deed register 可成為" + shop_name() + HIM "的所有者。\n"
                            HIM "使用 deed hide 可將房契隱藏。\n" NOR);
                set("no_sell", "這個東西如此貴重，我看你還是另找買家吧！\n");
                set("material", "paper");
                set("can_paimai", 1);
        }
}

void init()
{
        add_action("do_deed", "deed");
}

int do_deed(string arg)
{
        object me;

        me = this_player();

        if (! arg)return notify_fail("你要用房契做什麼？\n");

        if (arg == "hide")
        {
                write("你把" + shop_name() + "房契隱藏了起來。\n");
                destruct(this_object());
                
                return 1;
        }        
        else if (arg == "register")
        {
                if (SHOP_D->is_shop_owner(shop_id(), me->query("id")))
                        return notify_fail("你不已經是" + shop_name() + "的主人了嗎？\n");

                write(HIC "你在" + shop_name() + HIC"的房契上籤上了你的大名：" + me->name() + "\n" NOR);
                write(HIG "恭喜你成為" + shop_name() + HIG "的主人。\n" NOR);

                SHOP_D->change_owner(me, shop_id(), me->query("id"));
                log_file("shop", me->query("id") + " at " + ctime(time()) + " 成為"+ shop_id() + "的主人。\n");

                return 1;
        }
        
        else
                return notify_fail("你要用房契做什麼？\n");

}




