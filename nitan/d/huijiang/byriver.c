// Room: /d/huijiang/byriver.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set ("short", "湖邊");
        set ("long", @LONG
草原西端一座高山參天而起，聳入雲霄。從山腰起全是皚皚白雪，
山腰以下卻生滿蒼翠樹木。樹上小鳥鳴啾，湖中冰塊撞擊與瀑布聲交織
成一片樂音。
LONG);
        set("outdoors", "huijiang");
        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"byriver1",
                "south" : __DIR__"xiaoxi2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50030);
        set("coor/y", 9020);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}