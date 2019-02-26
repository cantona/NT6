// Room: /d/wuyi/tongxianjing.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "通仙井");
        set("long", @LONG
通仙井位於御茶園內，又名呼來泉。井水清冽甘甜，為製茶的上等
好水，號稱武夷山第一井。詩曰：“石乳沾餘潤，雲根石髓流。玉甌浮
動處，神人洞天遊。”
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"yuchayuan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1390);
        set("coor/y", -5020);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
