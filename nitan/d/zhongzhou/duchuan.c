inherit ROOM;

void create()
{
        set("short", "渡船");
        set("long", @LONG
一葉小舟，最多也就能載七、八個人。一名六十多歲的老
艄公手持長竹篙，正在船尾吃力地撐着船。
LONG);
        set("no_clean_up", 0);
        set("outdoors", "zhongzhou");
        setup();
        replace_program(ROOM);
}