#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","深谷");
        set("long",@LONG
深谷中四處碧樹叢生，怪石嶙峋，好一副優美的自然景緻。
深谷之中，有一個大山洞出現在面前，不知道是什麼前輩高人住
在裏面。
LONG
        );
        set("exits",([
                "south":__DIR__"shangu",
                "north":__DIR__"donghou",
                "enter":__DIR__"shandong1",
        ]));
        set("objects",([
                __DIR__"npc/shendiao":1,
                CLASS_D("gumu")+"/yang":1,
        ]));
        set("outdoors", "jianzhong");
        set("coor/x", -400);
        set("coor/y", -440);
        set("coor/z", 0);
        setup();
}
        
