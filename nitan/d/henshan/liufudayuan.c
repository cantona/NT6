inherit ROOM;

int do_knock(string arg);

void create()
{
        set("short", "劉府大院");
        set("long", @LONG
劉府大院裡現在擠著很多江湖豪客，原來今天是劉正風金盆洗手
的好日子。劉老爺子在衡陽人緣很好，來捧場的自然不少，大院裡已
擺了很多張桌子，杯筷往來，很是熱鬧。但見他們一個個都神情異常，
今天這裡像是出了什麼事情。
LONG );
        set("exits", ([
               "north"  : __DIR__"liufudating",
               "out"    : __DIR__"liufugate",
        ]));

        set("objects", ([
                __DIR__"npc/dao-ke"  : 2,
                __DIR__"npc/jian-ke" : 4,
                __DIR__"npc/haoke"   : 2,
        ]));

        setup();
        replace_program(ROOM);
}