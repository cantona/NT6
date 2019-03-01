#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "帳房");
        set("long", @LONG
這裡是武館內的一個帳房，室內一個帳房先生在這裡認真
地做著帳。幾名新弟子正圍著帳房先生，看來是想把積攢下來
的錢物存在這裡。牆上掛有一個牌子(paizi)。
LONG);
        set("no_fight", 1);
        set("exits", ([
                "north" : __DIR__"guofu_shilu-1",
        ]));
        set("objects", ([
                __DIR__"npc/fan" : 1,
        ]) );
        set("item_desc", ([
                "paizi" : WHT "\n\n        ※※※※※※※※※※※\n"
                              "        ※                  ※\n"
                              "        ※     公平交易     ※\n"
                              "        ※                  ※\n"
                              "        ※  " NOR + HIW "存錢" NOR + WHT "： " NOR + HIY "deposit" NOR + WHT "  ※\n"
                              "        ※                  ※\n"
                              "        ※  " NOR + HIW "取錢" NOR + WHT "： " NOR + HIY "withdraw" NOR + WHT " ※\n"
                              "        ※                  ※\n"
                              "        ※  " NOR + HIW "兌換" NOR + WHT "： " NOR + HIY "convert" NOR + WHT "  ※\n"
                              "        ※                  ※\n"
                              "        ※  " NOR + HIW "查帳" NOR + WHT "： " NOR + HIY "check" NOR + WHT "    ※\n"
                              "        ※                  ※\n"
                              "        ※                  ※\n"
                              "        ※※※※※※※※※※※\n\n\n" NOR,
        ]));
        setup();
        replace_program(ROOM);
}