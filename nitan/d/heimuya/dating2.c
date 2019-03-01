//ROM dating
inherit ROOM;
void create()
{
        set("short", "白虎堂");
        set("long", @LONG
這是『日月神教』下第二大堂：白虎堂的大廳，四目望去，一地
都是鮮血，顯然不久前這裡有一場大戰。堂樑上有一塊舊木匾(bian)。
堂上北壁上有幾個血字(zi)。
LONG );
        set("exits", ([
            "west" : __DIR__"baistep1",
            "east" : __DIR__"linjxd6",
        ]));
        set("item_desc", ([
            "bian": "上面寫到：長河落日，白虎在天；
                     千秋萬載，一統江湖 。\n",
            "zi" : "上面寫到：華山弟子，勢殺邪教。\n" 
        ]) );
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}