//Cracked by Kafei

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(GRN"桃樹"NOR, ({ "tao shu", "shu", "tree" }) );
        set_weight(300000);
        set_max_encumbrance(5000000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", "這是一株枝葉繁茂的桃樹，比之桃花島上其它桃樹要大上許多。\n"
                            "似乎應該砍下(kan)些枝葉修理修理了。\n");
                set("value", 1000);
                set("material", "wood");
                set("no_get",1);
        }
        setup();
}

void init()
{
        add_action("do_slash", "kan");
}

int do_slash(string arg)
{
        object ob1, ob2, ob3, ob4, me;

        me = this_player();
        ob1 = present("xiao tiefu", me);

        if (me->is_busy()
         || query_temp("pending/exercising", me )
         || query_temp("exit_blocked", me) )
                return notify_fail("你現在正忙着呢。\n");

        if( !objectp(ob1=query_temp("weapon", me) )
         || query("skill_type", ob1) != "axe" )
                return notify_fail("你沒有稱手傢伙如何伐木？！\n");        

        if( query("name", ob1) != "小鐵斧"){
                message_vision(CYN"$N一聲大喝，手持"+query("name", ob1)+"目露兇光，對桃樹惡狠狠的砍了過去！\n"NOR,me);
                message_vision(CYN"只聽得“喀嚓”一聲，桃樹被攔腰砍為兩段！\n"NOR,me);
                destruct(this_object());
                return 1;
//                return notify_fail("你麻煩大了。\n");
        }

        if (!arg || (arg != "shu" && arg !="tree" && arg != "tao shu"))
                return notify_fail("你要砍什麼？！\n");
        if (query("slashed"))
                return notify_fail("這株桃樹已經被修整過了！\n");         

        message_vision(CYN"$N衣袖一捲，抽出一把小鐵斧，“吭喲！吭喲”的劈下一段段的桃枝......\n"NOR, me);

        message_vision(CYN"$N擦了擦汗，拾起幾根桃木枝。\n"NOR, me);
        ob2 = new(__DIR__"taomu");
        ob2->move(me);
        ob3 = new(__DIR__"taomu");
        ob3->move(me);
        ob4 = new(__DIR__"taomu");
        ob4->move(me);
        set("slashed", 1);
        set("long", "這是一株枝葉繁茂的桃樹，比之桃花島上其它桃樹要大上許多。\n"
                    "似乎剛被修整過。\n");

        call_out("renew", 300, me);
        return 1;
}

void renew()
{
        delete("slashed", this_object());
        set("long", "這是一株枝葉繁茂的桃樹，比之桃花島上其它桃樹要大上許多。\n"
                    "似乎應該砍下(kan)些枝葉修理修理了。\n");
}