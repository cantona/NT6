// Room: /d/huashan/jzroad3.c

inherit ROOM;
void create()
{
        set("short", "中條山腳");
        set("long", @LONG
你來到中條山腳。仰望天空，山勢壓頂，天邊的紅霞映透了整個
山林，呼嘯的穿山風刮個不停。你不禁有些懼意。向東有一條上山小
路。
LONG );
        set("exits", ([
                "west"   : __DIR__"jzroad2",
                "eastup" : __DIR__"jzroad4",
        ]));
        set("outdoors", "huashan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}

