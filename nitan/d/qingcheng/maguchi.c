// Room: /qingcheng/maguchi.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "麻姑池");
        set("long", @LONG
上清殿右是麻姑池，亦稱天池。池深數尺，形如半月，水色清
澈，四季久雨不盈，長旱不涸。
LONG );
        set("outdoors","qingcheng");
        set("resource/water", 1);
        set("exits", ([
                "west"     : __DIR__"shangqing",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8070);
        set("coor/y", -880);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}