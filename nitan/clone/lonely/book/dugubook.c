#include <ansi.h>; 
inherit ITEM;
// 獨孤九劍之無招解迷物件
// Edit by Rcwiz for Hero

void create()
{
        set_name(HIW "「獨孤九劍殘本」" NOR, ({ "dugu canben", "dugu", "canben" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", 1);
                set("long", HIW "\n這是一本用薄紙寫成的書，封皮上寫有「獨孤九劍\n"
                                  "殘本」六字。書皮泛黃，看來已經保存很久了。書\n"
                                  "中記載了劍魔獨孤求敗所創獨孤九劍之精髓。\n"
                                  "你試圖翻閱裡面記載的內容，但是你只覺得深奧無\n"
                                  "比，如無獨孤求敗本人講解，是永遠無法參透的。\n");
        }
}
