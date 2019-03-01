#include <ansi.h>

inherit ROOM;

void close_passage();
string look_bei();

void create()
{
    set("short", HIR "無名峰" NOR);
        set("long", @LONG
跨過路上的荊棘和荒草，你終于登上了五指山無名峰的峰頂。由于這裡
地處五峰之中，四周有其它山峰阻擋，因此風勢很小，常年籠罩在一片雲霧
之中。峰頂長滿了齊腰的荒草，怪石嶙峋，一片荒涼景色。在山峰頂部的正
中赫然矗立著一座巖石砌就的墳墓，墳墓的前面立著一塊一人多高的花崗巖
的墓碑(bei)。
LONG    );
        set("exits", ([
                "southdown" : __DIR__"hclu-4",
        ]));

        set("item_desc",([
                "bei" : (: look_bei :),
        ]));

        set("no_clean_up", 0);
        set("outdoors", "tiezhang");
        setup();
}

void init()
{
        add_action("do_move", "move");
}

int do_move(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg != "bei") 
                return notify_fail("你要推什麼？\n");

        if ((int)me->query_str() < 30)
                return notify_fail("你將吃奶的勁都用上了，可還是無法把石碑推開。\n");

        if ((int)me->query_skill("force", 1) < 100 )
                return notify_fail("你推了半天，發現石碑還是紋絲不動。\n");

        write(HIY "你紮下馬步，深深的吸了口氣，將墓碑緩緩的向旁推開，下面露出"
              "一個黑洞洞的入口。\n" NOR);
        message("vision", HIR + me->name() + HIR "雙膀用力，將墓碑向旁緩緩推"
                          "開，下面露出一個黑洞洞的入口。\n" NOR , environment(me), ({me}) );
        set("exits/enter", __DIR__"shijie-1");
        remove_call_out("close_passage");
        call_out("close_passage", 10);
        return 1;
}

void close_passage()
{
        object room;

        if (! query("exits/enter"))
                return;
        message("vision", HIR "墓碑發出隆隆的聲音，緩緩移回原處。\n" NOR, this_object() );
        delete("exits/enter");
}

string look_bei()
{
    return
    "\n"
 WHT "\n\n    ###################\n"
         "    ##               ##\n"
         "    ##           鐵  ##\n"
         "    ##           掌  ##\n"
         "    ##           幫  ##\n"
         "    ##" NOR + HIR "       上" NOR + WHT "  第  ##\n"
         "    ##           十  ##\n"
         "    ##" NOR + HIR "       官" NOR + WHT "  三  ##\n"
         "    ##           代  ##\n"
         "    ##" NOR + HIR "       劍" NOR + WHT "  幫  ##\n"
         "    ##           主  ##\n"
         "    ##   不" NOR + HIR "  南" NOR + WHT "      ##\n"
         "    ##   肖          ##\n"
         "    ##   弟          ##\n"
         "    ##   子  之      ##\n"
         "    ##   裘  墓      ##\n"
         "    ##   千          ##\n"
         "    ##   仞          ##\n"
         "    ##   謹          ##\n"
         "    ##   立          ##\n"
         "    ##               ##\n"
         "    ###################\n\n" NOR;
    "\n";
}