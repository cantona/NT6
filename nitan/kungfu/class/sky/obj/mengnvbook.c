#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW "字條" NOR, ({ "zi tiao", "zi", "tiao" }));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", HIC "這是一張字條，上書：\n\n" HIW
                                 "   世間萬物皆為幻，吾本亦為幻，君既已決定背棄今生，切勿再被\n"
                                 "今生幻想所困！縱有萬語，君夢將醒，方盡矣！來生多珍重！！！\n\n"
                                 "                                                      ---- 夢﹒無名\n\n" NOR);
                set("value", 300);
                set("material", "paper");
        }
}

