// guangning.c 廣寧居
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "廣寧居");
        set("long", @LONG
這裏是全真七子之六郝大通的卧室，卧室很小，除了一張小牀，
一張小茶几而外沒有什麼別的擺設。茶几晶瑩透明，仔細一看，原來
幾面是用整塊的玉琢磨成的。茶几上擺放着幾本先天課術的書，還有
一些卜卦用的金錢。
LONG
        );
        set("exits", ([
                "north" : __DIR__"piandian",
        ]));

        set("objects", ([
                CLASS_D("quanzhen")+"/hao" : 1,
        ]));
        set("coor/x", -2790);
        set("coor/y", 90);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}