//ROM dating
inherit ROOM;
void create()
{
        set("short", "青龍堂");
        set("long", @LONG
這是『日月神教』下第三大堂：青龍堂的大廳，十分氣派，又或
有一條青龍時隱時現。堂樑上有一塊匾(bian)。
LONG );
        set("exits", ([
            "south"      : __DIR__"chlang1",
            "northdown" : __DIR__"guang",
        ]));
        set("item_desc", ([
            "bian": "上面寫到：長虹貫日，青龍飛天。千秋萬載，一統江湖 。\n",
        ]) );
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}