inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short",HIY"承德殿內"NOR);
        set("long", @LONG
這裡是承德殿內，也是大宋皇帝和文武百官議事的地方，殿內金
碧輝煌，煞是雄偉壯觀，大殿的正中央的龍椅上端坐的是宋徽宗，兩
面分立著眾宮女太監，文武百官依品次排列左右。
LONG );

        set("indoors", "city2");
        set("no_fly",1);
        set("no_fight",1);
        set("have_quest",1);

        set("exits", ([
                "out"    : __DIR__"cddian",
        ]));

        set("objects", ([
           __DIR__"song/liu" : 1,
           __DIR__"npc/taijian"     : 2, 
        ]));
        setup();
        replace_program(ROOM);
}
