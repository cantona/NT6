#include <ansi.h>
inherit ROOM;

string look_ta();

void create()
{
        set("short", "報國寺");
        set("long", @LONG
報國寺是峨眉山最的大寺院之一。寺廟倚山建造，彌勒殿大雄殿、
七佛殿逐級升高，規模宏大。殿內佛像金光閃閃氣宇軒昂。寺內芳草
迷徑，花開不絕。這裏有座華嚴塔(ta)。這裏向西，約二里可達伏虎
寺。
LONG );
        set("outdoors", "emei");
        set("item_desc", ([
                "ta" : (: look_ta :),
        ]));
        set("objects", ([
                __DIR__"npc/guest": 1,
        ]));
        set("exits", ([
                "west"  : __DIR__"bgsxq",
                "enter" : __DIR__"dxdian",
                "north" : __DIR__"bgsgate",
                "south" : __DIR__"milin1",
        ]));
        set("coor/x", -370);
        set("coor/y", -220);
        set("coor/z", 10);
        setup();
}

string look_ta()
{
        return YEL "\n這是一座十五層的紫銅鑄華嚴塔。塔高七"
               "米，塔身周匝共有小\n佛四千七百尊之多，並鑄"
               "有「華嚴經」全文兩萬多字，其冶煉\n工藝與雕"
               "工技巧，已造至極至美之境。\n\n" NOR;
}