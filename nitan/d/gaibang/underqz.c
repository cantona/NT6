// Room: /d/gaibang/underqz.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "鐵槍廟下");
        set("long", @LONG
這是嘉興鐵槍廟下的小洞。裡面破破爛爛的，丟滿了各種雜物，還
有丐幫弟子收集的破銅爛鐵等。從這裡通往丐幫的秘密通道。
LONG );
        set("exits", ([
                "out"       : "/d/jiaxing/tieqiang",
                "northwest" : __DIR__"qzandao2",
        ]));
        set("objects",([
                CLASS_D("gaibang") + "/ma" : 1,
                CLASS_D("gaibang") + "/wu-changfeng" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1510);
        set("coor/y", -1010);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}
