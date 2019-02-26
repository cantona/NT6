inherit ROOM;

void create()
{
        set("short", "花園");
        set("long", @LONG
這裏是個花園，一年四季都生長着各種奇異的花草，在陽光下發
出七彩妖豔的光輝。花園裏一片沉寂，竟看不到一隻蜜蜂或蝴蝶飛舞。
旁邊有一座小亭子。
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "east" : __DIR__"huating3",
                "south" : __DIR__"huayuan1",
        ]));

        setup();
        replace_program(ROOM);
}