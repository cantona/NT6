inherit ROOM;

void create()
{
        set("short", "雪山山路");
        set("long", @LONG
大雪山北麓的地勢不是甚高，周圍還有一些小山丘。西面有一座
寺院依山而建。顯得異常高大。寺院呈平頂梯型，多由大石砌成，牆
體厚實，窗口窄小。
LONG );
        set("exits", ([
                "north"   : __DIR__"nroad3",
                "westup"  : "/d/xueshan/shanmen",
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}
