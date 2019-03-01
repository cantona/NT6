// Room: /qingcheng/sandaoshi.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "三島石");
        set("long", @LONG
三島石上刻“降魔”二字，相傳為張天師當年降魔，因巨石當
道，揮劍力劈，石裂為三，成為三塊相連的島石。石裂處自然生成
石梯。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "west"     : __DIR__"tianshidong",
                "eastdown" : __DIR__"tingquanting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8090);
        set("coor/y", -910);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}