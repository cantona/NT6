// baiyunwan.c 白雲熊膽丸

inherit ITEM;

void create()
{
        set_name("白雲熊膽丸", ({"baiyunxiudan wan", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆武林人士夢寐以求的療傷聖藥。\n");
                set("value", 50000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        me->receive_curing("qi", 800);
        me->receive_curing("jing", 400);
        message_vision("$N吃下一顆白雲熊膽丸，只覺精氣上升，氣色大好。\n", me);
        destruct(this_object());
        return 1;
}