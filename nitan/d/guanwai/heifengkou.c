inherit ROOM;

void create()
{
        set("short", "黑風口");
        set("long", @LONG
這裡是密林中的險惡之境周圍是為茂密的鬆林，不見天光。
林中傳來野獸饑餓之極的嘶吼。四處有不知名草菰和野果，可
你一點也不敢嘗嘗。林木幽暗深邃，似乎暗藏殺機。你到了此
處，心膽俱裂，只想快點離開。
LONG );
        set("exits", ([
                "east"     : __DIR__"xiaotianchi",
                "westdown" : __DIR__"milin3",
        ]));
        set("objects", ([
                "/clone/quarry/xiong" : 1,
        ]));
        setup();
        replace_program(ROOM);
}