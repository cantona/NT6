// Room: /d/huangshan/feicui.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "翡翠池");
        set("long", @LONG
在鬆谷溪邊，星羅棋佈着六個池潭。平時潭水清澈平靜，每當微風
吹動，漣漪微蕩，好似龍鱗，所以叫龍潭。依照水色分為赤，青，烏，
白，老，更有一潭，水深形美，所以被稱為翡翠池。四周石桌，石欄，
懸崖題刻，應有盡有，別有風味。據説聞名天下的龍化劍便是依此五潭
悟出，也不知真假。
LONG
        );
        set("exits", ([ 
                "south" : __DIR__"songgu",
        ]));
        set("objects", ([
                __DIR__"obj/pond1" : 1,
                __DIR__"obj/pond2" : 1,
                __DIR__"obj/pond3" : 1,
                __DIR__"obj/pond4" : 1,
                __DIR__"obj/pond5" : 1,
                __DIR__"obj/pond6" : 1,
        ]) );

        set("outdoors", "huangshan");
        set("coor/x", -595);
        set("coor/y", -960);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}