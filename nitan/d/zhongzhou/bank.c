#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "錢莊");
        set("long", @LONG
這是中州城內一家老字號錢莊，據説這裏的信譽很好。幾
個夥計在櫃枱上忙着。櫃枱上還有一塊牌子 (paizi)，因是幹
錢的營生，這裏的保鏢身手不凡，讓你打不到什麼壞主意。
LONG);
        set("no_fight", 1);
        set("no_steal", 1);
        set("no_beg",1);
        set("exits", ([
                "east" : __DIR__"wendingnan1",
                 
        ]));
        set("item_desc", ([
                "paizi" : WHT "\n\n        ※※※※※※※※※※※\n"
                              "        ※                  ※\n"
                              "        ※     公平交易     ※\n"
                              "        ※                  ※\n"
                              "        ※  " NOR + HIW "存錢" NOR + WHT "： " NOR + HIY "deposit" NOR + WHT "  ※\n"
                              "        ※                  ※\n"
                              "        ※  " NOR + HIW "取錢" NOR + WHT "： " NOR + HIY "withdraw" NOR + WHT " ※\n"
                              "        ※                  ※\n"
                              "        ※  " NOR + HIW "兑換" NOR + WHT "： " NOR + HIY "convert" NOR + WHT "  ※\n"
                              "        ※                  ※\n"
                              "        ※  " NOR + HIW "查帳" NOR + WHT "： " NOR + HIY "check" NOR + WHT "    ※\n"
                              "        ※                  ※\n"
                              "        ※                  ※\n"
                              "        ※※※※※※※※※※※\n\n\n" NOR,
        ]));

        set("objects" , ([
                __DIR__"npc/yaodezhong":1,
        ]));

        set("coor/x", -9050);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}