// Room: /d/mobei/hill1.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "荒山上");
        set("long", @LONG
稀疏的灌木，草叢。坡頂比較平緩，西北風一陣緊，一陣緩，北面
的一片烏雲緩緩移動過來，昏黃的月光下幾點磷火漂移不定。東面的草
叢中似乎有些東西在閃著白光。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/kezhene" : 1,
        ]));
        set("outdoors","mobei");
        set("exits", ([ /* sizeof() == 3 */
                "east"      : __DIR__"caocong",
                "northwest" : __DIR__"caocong1",
                "westdown"  : __DIR__"shulin",
        ]));
        set("coor/x", -210);
        set("coor/y", 5230);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}