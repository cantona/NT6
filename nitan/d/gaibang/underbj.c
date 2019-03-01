// Room: /d/gaibang/underbj.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "街邊狗洞");
        set("long", @LONG
這是北京城一條偏僻街邊的狗洞裡。四周丟滿了各種雜物，
還有丐幫弟子收集的破銅爛鐵等。從這裡通往丐幫的秘密通道。
LONG );
        set("exits", ([
                "out"   : "/d/beijing/caroad_e1",
                "south" : __DIR__"bjandao2",
        ]));
        set("objects",([
                //CLASS_D("gaibang") + "/quan-gq" : 1,
                "/clone/npc/mu-ren" : 3,
        ]));
//      set("no_clean_up", 0);
        set("coor/x", -190);
        set("coor/y", 4050);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}