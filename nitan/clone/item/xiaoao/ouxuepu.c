#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "「嘔血譜」" NOR, ({ "ouxue pu", "pu", "ouxue" }));
        set_weight(600);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("no_sell", "嘿，這東西也值錢？\n");

                set("long", HIR @LONG
這是一本殘破的棋局，記載了國手劉仲甫，在驪山
之麓給一個鄉下老媼殺得大敗的棋局。全數一百十
二著，殺得驚心動魄。傳說劉仲甫大敗之際登時嘔
血數升，因此稱之為嘔血譜。
LONG NOR);
                set("value", 1);
                set("material", "paper");
                set("skill", ([
                        "name"         : "chess",
                        "exp_required" : 10000,
                        "jing_cost"    : 60,
                        "difficulty"   : 30,
      "max_skill"    : 599,
                        //"min_skill"    : 100,
                        "need"         : ([ "literate" : 200 ]),
                ]));
        }
}
