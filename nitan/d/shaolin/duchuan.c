inherit ROOM;

void create()
{
        set("short", "渡船");
        set("long", @LONG
一葉小舟，最多也就能載七、八個人。一名六十多歲的老艄公手
持長竹篙，正在船尾吃力地撐著船。
LONG );
        set("no_clean_up", 0);
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
