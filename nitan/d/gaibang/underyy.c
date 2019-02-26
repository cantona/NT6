// Room: /d/gaibang/underyy.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "井底密道");
        set("long", @LONG
這是岳陽城內丐幫總舵大院內的古井下的洞裏。四周丟滿了各種雜
物，還有丐幫弟子收集的破銅爛鐵等。從這裏通往丐幫的祕密通道。
LONG );
        set("exits", ([
                "out"   : "/d/yueyang/gaibangyuan",
                "north" : __DIR__"yyandao2",
        ]));
        set("objects",([
                CLASS_D("gaibang") + "/bangzhong" : 1,
        ]));
        set("coor/x", -1420);
        set("coor/y", -2250);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}