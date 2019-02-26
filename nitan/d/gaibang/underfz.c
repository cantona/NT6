// Room: /d/gaibang/underfz.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "大榕樹下");
        set("long", @LONG
這是福州大榕樹下的小洞。裏面破破爛爛的，丟滿了各種雜物，還
有丐幫弟子收集的破銅爛鐵等。從這裏通往丐幫的祕密通道。
LONG );
        set("exits", ([
                "out"       : "/d/fuzhou/nanmendou",
                "northwest" : __DIR__"fzandao2",
        ]));
        set("objects",([
//                CLASS_D("gaibang") + "/li-sh" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1840);
        set("coor/y", -6320);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}