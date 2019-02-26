// Room: /d/qilian/qitianfeng.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "齊天峯");
        set("long", @LONG
北祈連山區第一高峯，直聳入雲，無路可尋。只見山前豎着一塊大
石 (stone)，據聞山中土人曾見時有黑衣神祕人出入此山，有膽大好奇
者入山探之，從未生還。
LONG );
        set("outdoors", "qilian");
        set("exits", ([
                "eastdown" : __DIR__"zibaipo",
                "westdown" : __DIR__"tanglangling",
        ]));
        set("objects", ([
                "/d/xingxiu/npc/trader" : 1,
        ]));
        set("coor/x", -15000);
        set("coor/y", 3000);
        set("coor/z", 200);
        setup();
        replace_program(ROOM);
}