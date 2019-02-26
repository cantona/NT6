// Room: /d/lingzhou/zhaiyuan.c

inherit ROOM;

void create()
{
        set("short", "內宅院");
        set("long", @LONG
這是個極大的院子，一色青磚鋪地，兩邊是東西廂房，住着丫鬟和
婆子，西南面有座三層的小樓，丫鬟們進進出出很是忙碌。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/yahuan" : 2,
        ]));
        set("cost", 1);
        set("outdoors", "lingzhou");
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"jjdayuan",
        ]));

        set("coor/x", -6255);
        set("coor/y", 2905);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}