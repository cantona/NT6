//ROOM: /d/huashan/changlang.c

inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
你走在長廊上只見紅欄碧瓦，雕樑畫棟，廊外風吹翠竹，細吟陣
陣，看來華山派氣派果然不凡。西面是岳夫人的居室。
LONG );
        set("exits", ([
            "west"  : __DIR__"jushi",
            "north" : __DIR__"songlin1",
            "south" : __DIR__"garden",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}