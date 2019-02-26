//ROM dating
inherit ROOM;
void create()
{
        set("short", "天香堂");
        set("long", @LONG
這是『日月神教』下第四大堂：天香堂的大廳，遠遠望去鬱郁渺
渺，好似不食人間煙火。堂樑上有一塊匾(bian)。
LONG );
        set("exits", ([
                "west" : __DIR__"road1",
                "east" : __DIR__"chlang3",
                "southup" : __DIR__"tian1",
        ]));
        set("item_desc", ([
            "bian": "上面寫到：天香堂---日月神教聖姑住地。\n",
               ]) );
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}