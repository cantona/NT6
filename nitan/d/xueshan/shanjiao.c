inherit ROOM;

void create()
{
        set("short", "雪山山腳");
        set("long", @LONG
這裏是山腳下的一片平地，山上不遠處，皚皚白雪映照下的一大
片紅牆金瓦處，就是遠近聞名的雪山寺。
LONG );
        set("outdoors", "xuedao");
        set("exits", ([
                "westup" : "/d/xuedao/nroad7",
                "south"  : __DIR__"hubian4",
        ]));
        setup();
        replace_program(ROOM);
}