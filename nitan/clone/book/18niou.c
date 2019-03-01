#include <ansi.h>
inherit BOOK;

#define MUOU    "/clone/lonely/book/18muou"

void create()
{
        set_name("十八泥偶", ({ "18 niou", "18", "niou" }));
        set_weight(600);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "盒");
                set("long", NOR + WHT "
這是一個小木盒，盒中墊著棉花，並列著三排泥制玩偶，每排
六個，共是一十八個。玩偶制作得非常精巧，每個都是裸體的
男人，皮膚上塗了白堊，畫滿了條條紅線，更有無數黑點，都
是脈絡和穴道的方位。似乎都是和內功心法有關。\n" NOR);
                set("value", 5000);
                set("no_sell", "你家的孩子死了？玩具也拿來賣錢。");
                set("material", "wood");
                set("skill", ([
                        "name"         : "force",
                        "exp_required" : 1000,
                        "jing_cost"    : 30,
                        "difficulty"   : 30,
                        "max_skill"    : 99,
                        "min_skill"    : 20
                ]));
        }
}

void init()
{
        add_action("do_nie", "nie");
}

int do_nie(string arg)
{
        object me, ob;
        object where;

        me = this_player();

        if (! arg || ! id(arg))
                return 0;

        /*
        ob = find_object(MUOU);
        if (! ob) ob = load_object(MUOU);
        */
        ob = new(MUOU);

        if (! environment(ob))
        {
                ob->move(me, 1);
                message_sort(HIW "\n只見$N輕輕一捏手中的泥偶，聽得刷刷刷"
                             "幾聲，裹在泥人外面的粉飾、油彩和泥底紛紛掉"
                             "落。$N心感可惜，卻見泥粉褪落處裡面又有一層"
                             "油漆的木面。索性再將泥粉剝落一些，裡面依稀"
                             "現出人形，當下再將泥人身上的泥粉盡數剝去，"
                             "竟露出一個裸體的木偶來。木偶身上油著層桐油"
                             "，繪滿黑線，卻無穴道位置。木偶刻工精巧，面"
                             "目栩栩如生，雙手捧腹張嘴作笑狀，神態滑稽之"
                             "極，相貌和本來的泥人截然不同。\n\n" NOR, me);
        } else
        {
                message_sort(HIR "\n$N輕輕一捏手中的泥偶，聽得刷刷幾聲，"
                             "裹在泥人外面的粉飾油彩和泥底紛紛掉落，整個"
                             "泥偶化作了一塊塊爛泥。$N不禁連連嘆息。原想"
                             "其中可能另藏乾坤，沒想到竟然白白糟蹋了寶物"
                             "。\n\n" NOR, me);
        }
        destruct(this_object());
        return 1;
}
