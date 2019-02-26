// Code of ShenZhou
#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "泥潭小屋");
        set("long", @LONG
牆裏是個院子，分為兩半，左一半是實土，右一半卻是水塘。內
堂前是個月洞，仍無門扉。只見當前擺了一張長桌，上面放了七盞油
燈，排成天罡北斗之形。地下亂七八糟地擺了一根根的無數竹片，那
些竹片都是長約四寸，闊約二分，似乎是計數用的算子。
LONG );
        set("exits", ([
                "out" : __DIR__"maze2",
        ]));
        set("objects", ([
                CLASS_D("dali") + "/yinggu" : 1,
                ]) );
        set("no_clean_up", 0);
        set("cost", 1);

        set("coor/x", -38000);
        set("coor/y", -72010);
        set("coor/z", 0);
        setup();
}