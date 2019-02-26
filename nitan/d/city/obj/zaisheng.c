// lianzi.c 白蓮子

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("再生丸", ({"bailian zi", "zi"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆潔白如玉的再生丸。\n");
                set("value", 2000);
        }
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
        return notify_fail("你要吃什麼藥？\n");

        if( (query("potential", this_player())-100) >= 
             (int)query("learned_points",this_player()) ) 
                return notify_fail("你現在不需要用再生丸。\n");
        else {
                addn("potential", 1, this_player());
                message_vision("$N吃下一顆再生丸，感到身體裏產生了一種微妙的變化 !\n", this_player());
                destruct(this_object());
                return 1;
        }
}