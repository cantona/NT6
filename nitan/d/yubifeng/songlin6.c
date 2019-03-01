// /yubifeng/songlin6.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "大鬆林");
        set("long", @long
這座鬆林好長，走了半個時辰方始過完，一出鬆林，即到一座山峰腳下。山
峰雖非奇高，但宛如一根筆管般豎立在群山之中，陡削異常，莫說是人，即
令猿猴也是不易上去。        
long );
        set("exits", ([
                "east" : __DIR__"fengdi",
                "west" : __DIR__"songlin5",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yubifeng");
        set("coor/x", 6100);
        set("coor/y", 5170);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}