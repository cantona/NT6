inherit ROOM;
void create()
{
        set("short", "石礫小徑");
        set("long", @LONG
此處地勢與大漠的其余地方截然不同，遍地黃沙中混著粗
大石礫，丘壑處處，亂巖嶙嶙，山峰雖似觸手可及，路竟是十
分的崎嶇難行。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                "east" : __DIR__"lvzhou",
                "north" : __DIR__"bridge1",
        ]));

        setup();
        replace_program(ROOM);
}