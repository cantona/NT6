#include <room.h>
inherit ROOM;

void create()
{
        set("short", "落雁峯");
        set("long", @LONG
南峯又名落雁峯，是華山最高峯。峯頭題刻極多，如『太華峯頭
』、『竣極於天』、『袖拂天星』等，極言華嶽之高。環顧四周，皆
在足下。寇準詩讚曰：只有天在上，更無山與齊；舉頭紅日近，回首
白雲低。傳説五代時候的隱士陳摶就隱居在這裏。宋太祖曾經下詔徵
他出山作官，他便在這裏寫下謝詔表説：『一片野心都被白雲鎖住，
九重寵詔休教丹鳳銜來』，表示不願出山做官。
LONG );
        set("exits", ([
                "northdown" : __DIR__"zhandao",
        ]));
        /*
        if (random(10) > 8)
                set("objects", ([
                         CLASS_D("huashan") + "/feng" : 1,
                ]));
        */
        set("outdoors", "huashan");
        setup();
        replace_program(ROOM);
}