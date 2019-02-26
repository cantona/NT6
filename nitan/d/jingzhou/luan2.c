#include <ansi.h>

inherit ROOM;
string look_bei();

void create()
{
        set("short", "亂墳崗");
        set("long", @LONG
這裏是一處亂墳崗，到處長滿了過人高的長草，聽説這裏經常鬧
鬼，所以沒人敢來。一陣冷風颳來，嚇的你根根體毛豎起。前方好像
有一座新墳，墳上立有一塊碑(bei)。
LONG );

        set("exits", ([
                "west" : __DIR__"luan",
        ]));

        set("item_desc", ([
                "bei" : (: look_bei :),
        ]));

        set("coor/x", -7100);
	set("coor/y", -2010);
	set("coor/z", 0);
	setup();
}

string look_bei()
{
    return
    "\n"
 WHT "\n\n    ###################\n"
         "    ##               ##\n"
         "    ##           愛  ##\n"
         "    ##           女  ##\n"
         "    ##               ##\n"
         "    ##       " NOR + HIR "凌" NOR + WHT "      ##\n"
         "    ##       " NOR + HIR "霜" NOR + WHT "      ##\n"
         "    ##       " NOR + HIR "華" NOR + WHT "      ##\n"
         "    ##               ##\n"
         "    ##       之      ##\n"
         "    ##       墓      ##\n"
         "    ##               ##\n"
         "    ##   凌          ##\n"
         "    ##   思          ##\n"
         "    ##   退          ##\n"
         "    ##   立          ##\n"
         "    ##               ##\n"
         "    ###################\n\n" NOR;
    "\n";
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
        set("exits/enter", __DIR__"tomb");
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