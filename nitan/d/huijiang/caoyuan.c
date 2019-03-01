// Room: /d/huijiang/caoyuan.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "草原");
        set("long", @LONG
美麗的草原就在你的面前，成群的牛羊圍繞在你身邊，遠處天地交
際處不時有大片的煙塵湧起，剎那間就塞滿了天地，那是戈壁中時而出
現的龍卷風。
LONG
        );
        set("outdoors", "huijiang");
        set("exits", ([ /* sizeof() == 4 */
                "southup" : __DIR__"xiepo",
                "north" : __DIR__"caoyuan1",
                "west" : __DIR__"caoyuan2",
                "east" : __DIR__"caoyuan3",
        ]));
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/huizhushaonv" : 1,
        ]));
        set("coor/x", -50050);
        set("coor/y", 9080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}