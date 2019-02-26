#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_QIN;

void create()
{
        set_name(HIY "蕉葉古琴·明朝" NOR, ({ "jiaoye qin", "jiaoye", "qin" }));
        set_weight(700);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                              
                set("long", HIY "此琴乃弘治嘉靖年間著名斫琴家祝海鶴所制\n"
                                "琴形旖旎秀逸，蕉葉卷邊工雅生動，音色潤\n"
                                "勻透靜，為琴器中難得一見的珍品。\n" NOR);
                set("value", 800000);
                set("material", "wood");
             }
        setup();
}

void init()
{
        add_action("play_qin", "play");
}