// /d/changan/apanggong.c

inherit  ROOM;

void  create  ()
{
        set  ("short",  "阿房宮");
        set  ("long",  @LONG
這裡便是阿房宮，四下便是黃土、亂石，哪裡看得出有什麼宮殿？
不遠處立著塊石碑(bei)。
LONG);
        set("exits",  ([  //sizeof()  ==  4
                "east" :  __DIR__"road7",
        ]));
        set("item_desc",  ([
                "bei" :  "

            始皇三十五年，使奴七十萬眾建造此宮
                 不念暴政苛刻，義師逐鹿。
               霸王入關，千裡宮闕付之一炬。

                暴者必亡      仁者無敵
\n",
        ]));
        set("outdoors",  "changan");
        set("no_clean_up",  0);
        set("coor/x", -10790);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}