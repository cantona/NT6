#include <ansi.h>
inherit ROOM;

string look_gate();

void create()
{
        set("short", "報國寺山門");
        set("long", @LONG
報國寺為峨嵋出入之門户。山門(gate)上有一塊大匾。寺外蒼楠
環衞，翠柏掩映。由此一路向西上開始登峨嵋山，北面下山是一條彎
彎的石階路。
LONG );
        set("outdoors", "emei");
        set("item_desc", ([
                "gate" : (: look_gate :),
        ]));
        set("objects", ([
                __DIR__"npc/guest": 1,
        ]));
        set("exits", ([
                "northdown" : __DIR__"qsjie2",
                "south"     : __DIR__"bgs",
        ]));
        set("coor/x", -370);
        set("coor/y", -210);
        set("coor/z", 10);
        setup();
}

string look_gate()
{
      return
RED "\n\n　　　　≌≌≌≌≌≌≌≌≌≌≌≌≌≌≌≌≌\n"
"　　　　≌≌　　　　　　　　　　　　　≌≌\n"
"　　　　≌≌" WHT "　　　報　　國　　寺" RED "　　　≌≌\n"
"　　　　≌≌　　　　　　　　　　　　　≌≌\n"
"　　　　≌≌≌≌≌≌≌≌≌≌≌≌≌≌≌≌≌\n\n\n";
}