// Room: /d/gaibang/underhs.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "捨身崖下");
        set("long", @LONG
這是華山捨身崖下的小山洞，裏面破破爛爛的，丟滿了各種雜
物，還有丐幫弟子收集的破銅爛鐵等。從這裏通往丐幫的祕密通道。
LONG );
        set("exits", ([
                "out"       : "/d/huashan/sheshen",
                "southeast" :__DIR__"hsandao2",
        ]));
        set("objects" , ([
                CLASS_D("gaibang") + "/li-futou" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -890);
        set("coor/y", 210);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}