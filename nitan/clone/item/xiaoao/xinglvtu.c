#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + HIG "「溪山行旅圖」" NOR, ({ "xishan xinglvtu",
                 "tu", "xishan", "xinglvtu" }));
        set_weight(600);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "冊");
                set("no_sell", "我的天，你…你知道這是啥麼？也拿來賣？\n");
                set("long", HIG @LONG
這是一幅極為陳舊的圖畫，右上角題着「北宋範中
立溪山行旅圖」十字，一座高山沖天而起，墨韻凝
厚，氣勢雄峻之極，實是精絕之作。但見那山森然
高聳，雖是紙上的圖畫，也令人不由自主的興高山
仰止之感。
LONG NOR);
                set("value", 1);
                set("material", "paper");
                set("skill", ([
                        "name"         : "drawing",
                        "exp_required" : 10000,
                        "jing_cost"    : 60,
                        "difficulty"   : 30,
                        "max_skill"    : 199,
                        //"min_skill"    : 100,
                        "need"         : ([ "literate" : 200 ]),
                ]));
        }
}
