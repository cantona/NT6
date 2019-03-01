// Room: /d/shaolin/wuchang.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這裡是少林寺的練武場。由無數塊巨大的花崗巖石板舖就。上千
年的踩踏已使得這些石板如同鏡子般平整光滑。西邊角上還有兩個大
沙坑，十來個僧人正在練習武藝。東西兩面各有一練武場。
LONG );
        set("exits", ([
                "south" : __DIR__"houdian",
                "east" : __DIR__"wuchang2",
                "west" : __DIR__"wuchang1",
                "north" : __DIR__"fzlou",
        ]));
        set("outdoors", "shaolin");
        set("objects",([
                CLASS_D("shaolin") + "/dao-jue" : 1,
        ]));
        setup();
}