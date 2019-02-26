inherit ROOM;

void create()
{
        set("short", "鹿鳴峯");
        set("long", @LONG
龍門峯西側是鹿鳴峯。鹿鳴峯又稱芝盤峯，因峯上有一草
甸子，形圓如蓋，有熱氣從地下冒出，每到嚴冬，其它峯均積
雪甚厚，唯鹿鳴峯依然植物茂盛，且盛產芝草，鹿多居之。常
有鶴、雀、雕、燕飛落其上，有鹿鳴翠谷，雕飛芝蓋之稱。
LONG );
        set("exits", ([
                "south"   : __DIR__"baiyun",
                "east"    : __DIR__"longmen",
                "northdown" : __DIR__"famu",
        ]));
        set("objects", ([
                "/clone/quarry/lu" : 2,
                "/clone/quarry/diao" : 1,
        ]));
        set("outdoors", "changbai");
        setup();
        replace_program(ROOM);
}