// Room: /d/mobei/mobei.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create ()
{
        set ("short", "漠北");
        set ("long", @LONG
漠北苦寒之地，風刀霜劍，就在這片貧瘠的土地上，蒙古新一代的
霸主鐵木真正在崛起，向北過去就是蒙古的草原，東南方向是中原的所
在。
LONG);
        set("outdoors","mobei");
        set("exits", ([ /* sizeof() == 2 */
                "southeast" : __DIR__"damo",
                "north"     : __DIR__"caoyuan3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -220);
        set("coor/y", 5140);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}