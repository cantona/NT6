inherit ROOM;

void create()
{
        set("short", "花園");
        set("long", @LONG
這裡是個花園，一年四季都生長著各種奇異的花草，在陽光下發
出七彩妖艷的光輝。花園裡一片沉寂，竟看不到一只蜜蜂或蝴蝶飛舞。
有一條石子小路通向前面一座花廳。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "east" : __DIR__"huating1",
                "south" : __DIR__"huayuan2",
                "west" : __DIR__"dating",
                "north" : __DIR__"huayuan3",
        ]));
        set("objects", ([
                 __DIR__"npc/tongzi": 4,
        ]));

        setup();
        replace_program(ROOM);
}
