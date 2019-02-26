inherit ROOM;

void create()
{
        set("short", "大雄殿");
        set("long", @LONG
這裏是報國寺大雄殿。報國寺是峨嵋山最大寺院之一。大雄殿內
供着金光燦燦的佛像，氣宇軒昂。
LONG );
        set("objects", ([
                __DIR__"npc/guest" : 2,
        ]));

        set("exits", ([
                "out"   : __DIR__"bgs",
                "west"  : __DIR__"bgschanfang",
                "north" : __DIR__"cangjinglou",
        ]));
        setup();
        replace_program(ROOM);
}