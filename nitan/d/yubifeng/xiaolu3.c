// /yubifeng/xiaolu3.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這是一條在丘巒起伏的小小山脈下的小路，兩邊是稀疏的松樹，夾
雜着班駁的積雪。偶爾狂風大作，松果和雪團交加而下。雪地上有不少
腳印，看來似乎是剛有野獸走過。再望北，便是一座不太高的圓峯。
LONG );
        set("exits", ([
                "east"  : __DIR__"xiaolu2",
                "south" : __DIR__"yuanfeng",
        ]));
        set("objects", ([
                __DIR__"npc/ping" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yubifeng");
        set("coor/x", 6100);
        set("coor/y", 5140);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}