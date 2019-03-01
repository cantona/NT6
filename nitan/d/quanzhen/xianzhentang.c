// xianzhentang.c 顯真堂
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "顯真堂");
        set("long", @LONG
這裡是大堂旁邊的一個側廳，也是接待重要客人的地方。廳不大，
只擺放著一張桌子和幾把椅子。桌上擺放著一盆高山流水的盆景，牆
壁上掛著一些字畫。西面有一間藥劑室，是配藥的地方。
LONG
        );

        set("exits", ([
                "east" : __DIR__"piandian",
                "west" : __DIR__"yaojishi",
                "north" : __DIR__"datang1",
                "south" : __DIR__"rongwutang",
        ]));
        set("no_clean_up", 0);
        set("objects",([
                CLASS_D("quanzhen")+"/zhang" : 1,
        ]));

        set("coor/x", -2800);
        set("coor/y", 100);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}