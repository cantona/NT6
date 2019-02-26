inherit ROOM;

void create()
{
        set("short", "戈壁");
        set("long", @LONG
此處地勢與大漠的其餘地方截然不同，遍地黃沙中混着粗
大石礫，丘壑處處，亂巖嶙嶙，路十分的崎嶇難行。
LONG);
        set("outdoors", "xiyu");
        set("exits", ([
                  "west" : __DIR__"caoyuan5",
                  "east" : __DIR__"caoyuan3",
        ]));

        setup();
        replace_program(ROOM);
}