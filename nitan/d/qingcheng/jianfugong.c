// Room: /qingcheng/jianfugong.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "建福宮");
        set("long", @LONG
建福宮舊稱丈人觀，以其座落丈人峰下故也。相傳五岳丈人寧
封子修道于此。院內樹木假山，相互掩映；周圍林木蒼翠，濃蔭蔽
日，炎夏來此，十分涼爽。這裡也是上山的起點。
LONG );
        set("exits", ([
                "south"     : __DIR__"xiaoqiao",
                "northwest" : __DIR__"path1",
        ]));
        set("objects", ([
                __DIR__"npc/ji" : 1,
                __DIR__"npc/shen" : 1,
                "/clone/npc/walker" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -8060);
        set("coor/y", -920);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}