// Room: /d/gaibang/underwd.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "土匪窩邊");
        set("long", @LONG
這是武當山下土匪窩邊上的小山洞。裡面破破爛爛的，丟滿了各種
雜物，還有丐幫弟子收集的破銅爛鐵等。從這裡通往丐幫的秘密通道。
LONG );
        set("exits", ([
                "out"       : "/d/wudang/tufeiwo1",
                "northeast" : __DIR__"wdandao2",
        ]));
        set("objects",([
                CLASS_D("gaibang") + "/li-sh" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -2000);
        set("coor/y", -810);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}