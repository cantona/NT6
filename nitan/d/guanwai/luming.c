inherit ROOM;

void create()
{
        set("short", "鹿鳴峰");
        set("long", @LONG
龍門峰西側是鹿鳴峰。鹿鳴峰又稱芝盤峰，因峰上有一草
甸子，形圓如蓋，有熱氣從地下冒出，每到嚴冬，其它峰均積
雪甚厚，唯鹿鳴峰依然植物茂盛，且盛產芝草，鹿多居之。常
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