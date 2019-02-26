//zsh_szzb.c
#include <ansi.h>

inherit ROOM;

#define PLACE "sz"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", MAG"紫衫閣"NOR);
        set("long", @LONG
這是一間看上去有些古怪的房間，桌椅門窗盡呈紫色，給人一種
神祕莫測的感覺。廳中端坐一位壯年男子，看上去像一個飽讀詩書的
文士。房間的牆壁上有一塊牌子(paizi)。紫衫會成員可以在這裏選擇
任務去完成。
LONG );

        set("objects", ([ 
                __DIR__"npc/boss-song"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([ 
                "south" : __DIR__"zsh_szdamen",
        ]));

	set("coor/x", 1090);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>