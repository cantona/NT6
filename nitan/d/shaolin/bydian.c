// Room: /d/shaolin/bydian.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "白衣殿");
        set("long", @LONG
這是白衣殿，供奉白衣觀音大士。大士高居須彌座上，手托凈瓶，
眉含微愁，唇綻淺笑，仿佛對人間疾苦既存憂心，又覺釋懷。殿中放
了紅木大香案，香案上供品齊備，香火十分旺盛。
LONG );
        set("exits", ([
                "west" : __DIR__"guangchang5",
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
