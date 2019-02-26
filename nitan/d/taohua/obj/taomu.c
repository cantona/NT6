//Cracked by Kafei
// taomu.c

#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name(YEL"桃木"NOR,({ "taomu"}) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("value", 0);
                set("material", "wood");
                set("long", "這是一根三尺來長，剛砍下的桃木，略加雕琢(cut)既可做成一把桃木劍。\n");
                set("wield_msg", "$N拿出一跟$n，握在手中。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
        }
        init_sword(2);
        setup();
}

void init()
{
        add_action("do_cut", "cut");
}

int do_cut(string arg)
{
        object ob1, ob2, me;

        me = this_player();

        if (me->is_busy()
         || query_temp("pending/exercising", me )
         || query_temp("exit_blocked", me) )
                return notify_fail("你現在正忙着呢。\n");

        if (!arg || arg != "taomu")
                return notify_fail("你要雕刻什麼？\n");

        if( !objectp(ob1=query_temp("weapon", me) )
         || query("name", ob1) != "小鐵斧" )
                return notify_fail("你沒有工具如何雕刻？！\n"); 

        message_vision(CYN"$N拿起小鐵斧在桃木上細心的劈削着......\n"NOR, me);

        if (random(2) == 1) {
        message_vision(CYN"$N忙了半天，終於雕出一把粗糙的桃木劍，並在劍柄上刻上名字。\n"NOR, me);
        ob2 = new(__DIR__"taomujian");
        ob2->set("long","這是一柄三尺來長，手工製成的桃木劍，似乎不是一件好兵器。\n"
                         "劍柄上刻着“"+me->name()+"”幾個字。\n");
        set("owner",query("id",  me), ob2);
        ob2->move(me);
        destruct(this_object());
        } else {
        message_vision(CYN"$N一個不小心，“埃呀！喀嚓！”，桃木斷掉了！\n"NOR,me);
        destruct(this_object());
        }

        return 1;
}