// Room: /d/nanyang/duchuan.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;

void create()
{
        set("short", "渡船");
        set("long", @LONG
一葉小舟，最多也就能載七、八個人。一名六十多歲的老艄公手持
長竹篙，正在船尾吃力地撐着船。
LONG );
        set("no_clean_up", 0);
        set("outdoors", "nanyang");
        set("coor/x", 10);
        set("coor/y", 350);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}