#include <ansi.h>

inherit ITEM;
#include <ansi.h>
void setup()
{}

void init()
{
        add_action("do_move", "move");
}

void create()
{
       set_name("骸骨", ({"haigu","skeleton"}) );
       set_weight(10000);
       set_max_encumbrance(6000000);
       if( clonep() )
               set_default_object(__FILE__);
       else{
       set("unit", "具");
       set("long", "這副骸骨躺在這裡已經很久了。\n");
       set("value", 0);
       set("material","wood");
       set("no_get",1);
       set("init",0);
       }
       setup();
}

int do_move(string arg)
{
        object book;
        object me = this_player();
        if (!id(arg))
                return 0;
        if( query_temp("wumu_shanshui", this_player())){
                if (!present("wumu yishu",me)){
                message_vision(
HIY"$N輕輕地挪動骸骨，發現下面有一本書，$N急忙揀起揣到懷中。\n"NOR
RED"那骸骨突然迎頭向$N撲將下來，摔在地上，四下散開，嚇了$N一跳！\n"NOR,this_player());
                book = new(__DIR__"wumu-yishu");
                book->move(me);
                destruct(this_object());
                return 1;
                }
                message_vision(
HIM"骸骨急道：書都拿到了還不快滾，沒事把老子挪來挪去的幹什麼？？？\n"NOR, this_player());
                return 1;
                }
                else {
                message_vision(
HIR"$N輕輕地挪動骸骨，突然從骸骨的下面冒出一股毒氣，鑽進$N的鼻子中。\n"NOR, this_player());
                set_temp("last_damage_from", "中毒", me);
                me->die();
                return 1;
        }
}