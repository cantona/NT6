#include <room.h>
inherit ROOM;

void create()
{
        set("short", "落雁峰");
        set("long", @LONG
南峰又名落雁峰，是華山最高峰。峰頭題刻極多，如『太華峰頭
』、『竣極于天』、『袖拂天星』等，極言華岳之高。環顧四周，皆
在足下。寇準詩讚曰：只有天在上，更無山與齊；舉頭紅日近，回首
白雲低。傳說五代時候的隱士陳摶就隱居在這裡。宋太祖曾經下詘征
他出山作官，他便在這裡寫下謝詘表說：『一片野心都被白雲鎖住，
九重寵詘休教丹鳳銜來』，表示不願出山做官。
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