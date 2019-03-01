#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + YEL "「廣陵散曲譜」" NOR, ({ "guangling san",
                 "guangling", "san" }));
        set_weight(300);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("no_sell", "廣陵散？你當我不識貨啊？\n");
                set("long", NOR + YEL @LONG
這是一本頗為殘舊的曲譜，譜上用古隸寫著「廣陵
散」三字。傳說此套琴譜在西晉時便已然消失，但
卻不知為何今日在這裡出現。
LONG NOR);
                set("value", 1);
                set("material", "paper");
                set("skill", ([
                        "name"         : "guangling-san",
                        "exp_required" : 30000,
                        "jing_cost"    : 50,
                        "difficulty"   : 40,
                        "max_skill"    : 199,
                        "min_skill"    : 0,
                        "need"         : ([ "literate" : 200 ]),
                ]));
        }
}
