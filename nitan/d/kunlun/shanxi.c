// Room: /d/kunlun/shanxi.c
// Last Modified by winder on Jun. 29 2001

inherit ROOM;

void create()
{
        set("short", "山溪邊");
        set("long", @LONG
這裏是一條小溪。崑崙山終年積雪，在烈日照射下，部分冰雪融化
成水，而匯成小溪，溪水向下而流，不知其流向何方。往西而上是一個
大叢林。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
                "westup" : __DIR__"xschongling",
                "eastup" : __DIR__"hmszhuang",
        ]));
        set("objects", ([ /* sizeof() == 2 */
                __DIR__"npc/wu" : 1,
                __DIR__"npc/weibi" : 1,
        ]));
        set("outdoors", "hongmei");
        set("coor/x", -90040);
        set("coor/y", 10010);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}