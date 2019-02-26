// Room: /binghuo/inhole1.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "外洞");
        set("long", @LONG
山洞極是寬敞，有八九丈縱深，中間透入一線天光，宛似天窗一
般。洞裏陶盆、瓷碗、石凳、木桌、竹帚，自有一番情趣。石洞中套
洞，裏頭還有一個裏洞。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "out"   : __DIR__"shanlu1",
                "enter" : __DIR__"inhole2",
        ]));
        setup();
}

void init()
{
        object ob;
        int i = random(2);
        if( i == 0) return;

        ob = this_player();

        message_vision(HIR "\n$N一不小心，掉進了的陷阱！
$N只覺得腳下一陣巨痛，原來是踩上了......\n\n" NOR, ob);
        ob->move(__DIR__"xianjing");
}