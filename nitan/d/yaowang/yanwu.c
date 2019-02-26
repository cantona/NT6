inherit ROOM;

void create()
{
        set("short", "演武廳");
        set("long", @LONG
這裏是一處寬大的空場，空場中央立着的一塊大木牌上寫着
一個大大的“武”字。不少年輕人在這裏練鍼灸、品藥草，
一位一身黑衣的年輕人揹着手四處巡視指點。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"fyuan",
]));

        set("objects", ([
                __DIR__"npc/buwawa" : 1,
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
