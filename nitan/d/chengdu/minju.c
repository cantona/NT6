inherit ROOM;

void create()
{
        set("short", "廢棄的民居");
        set("long", @LONG
這裡是一幢破爛的民居，看樣子已經被廢棄很常一段日子
了，大院內四處殘戈斷壁，雜草叢生。院子的一個陰暗角落裡
還立著一個已快腐爛的書架。
LONG );
        set("exits", ([
                "out"      : __DIR__"eastroad3",
        ]));

        set("objects", ([
                __DIR__"obj/shelf" : 1,
        ]));

        set("no_clean_up", 0);
        setup();

        replace_program(ROOM);
}
