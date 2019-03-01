#include <ansi.h>
inherit ROOM;

void create()
{

        set("short", "翡翠池");
        set("long", @LONG
這裡是一個四周鑲滿翡翠的圓池，你身在池中，伸下手去
只覺清涼入骨，雙手捧起水來但見池水澄凈清澈，更無纖毫苔
泥，原來圓池四周都是翡翠，池水才映成綠色。潔白的玉峰映
在碧綠的池中，顯得格外的明艷潔凈，幽絕清絕。只見池邊長
滿了翠綠的青籐(rattan)。池底似乎有個洞(hole)。

LONG);
        set("item_desc", ([
                "rattan" : GRN "\n生長在翡翠池岸邊的翠綠青籐，可以由它爬上岸去。\n" NOR,
                "hole"   : WHT "\n潛藏在池底的一個小洞，你似乎可以鑽進去。\n" NOR,
        ]));
        setup();
}

void init()
{
        add_action("do_zuan", "zuan");
        add_action("do_climb", "climb");
}

int do_zuan(string arg)
{
        object me = this_player();

        if (! arg || arg != "hole")
                return notify_fail("你要鑽什麼？\n");

        message("vision", HIC "只見" + me->name() + HIC "緊閉呼吸，一個猛子朝池底"
                          "的洞鑽去。\n" NOR, environment(me), ({me}) );
        write(HIC "\n你朝池底的洞鑽去，哪知突然一道暗流沖來，把你扯入旋渦中。\n\n" NOR);

        me->move(__DIR__"lake3");
        message_vision(HIC "\n$N" HIC "被暗流從瀑布裡拋了出來。\n\n" NOR, me);

        return 1;
}

int do_climb(string arg)
{
            object me = this_player();

            if (! arg || arg != "rattan")
                return notify_fail("你要爬什麼？\n");

        message("vision", HIC "只見" + me->name() + HIC "順著青籐爬了上去。\n" NOR,
                          environment(me), ({me}));
        me->move(__DIR__"feicui1");
        message_vision(HIC "\n$N" HIC "順著青籐水淋淋地爬了上來。\n\n" NOR, me);
        return 1;
}
