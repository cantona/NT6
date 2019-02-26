#include <ansi.h> 
inherit ROOM;
int do_cai(string arg);

void create()
{
        set("short", "城西后林");
        set("long", @LONG
這是一片茂密的樹林。很多棵幾十丈高的大樹聚在一塊，象一把
把瓊天大傘，連日月都被遮蔽得黯然無光。樹林中還不時可以聽到大
自然發出的聲響。
LONG );
        set("exits", ([
                "south" : "/d/beijing/ximenwai",
                "north" : "/d/beijing/liandan_lin3",
                "east" : "/d/beijing/liandan_lin5",
                "west" : "/d/beijing/liandan_lin4",
        ]));

        set("no_clean_up", 0); 
	set("coor/x", -2860);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();       
}

#include "liandan_lin.h"